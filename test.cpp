#include <bits/stdc++.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <mutex>

using namespace std;

pthread_mutex_t mutexsum;

typedef struct {
    int thread_id;
    int start;
    int end;
    stringstream s;
    vector < vector<int> > d;
} perthread;


void *convert(void *infor )
{
    perthread *data = (perthread *) infor;
    int thread_id = data->thread_id;
    int start = data->start;
    int end = data->end;
    stringstream s = data->s;
    vector<vector<int> > d= data->d;

    for (int k = start; k < end; k++) {
        // cout<<k<<endl;
        s << "\t"
          << "{" << endl;
        for (int j = 0; j < 20; j++) {
           s << "\t\t"
              << "\""
              << "col_" << j + 1 << "\""
              << ":" << d[k][j];
            j == 19 ? s << endl : s << "," << endl;
        }
        s << "\t"
          << "}" << endl;
    }
    s.str("");
    pthread_exit((void *) 0);
}

int main(int argc, char *argv[])
{
    double start, end;
    double start_1, end_1;
    struct timeval wall_s, wall_e;
    struct timeval wall_s1, wall_e1;

    // for setting pthread
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    ifstream inFile("input.csv", ios::in);
    if (!inFile) {
        cout << "開啟檔案失敗！" << endl;
        exit(1);
    }
    ofstream os;
    os.open("ouput.json");
    start = clock();
    gettimeofday(&wall_s, NULL);

    int num, i = 0;
    int n = atoi(argv[1]);
    int size = atoi(argv[2]);
    int count = 0;
    int order = 0;
    vector<vector<int> > data;

    // read input.csv
    string line;
    while (getline(inFile, line)) {
        istringstream sin(line);  //切割字串
        vector<int> buff;
        string pred;
        while (getline(sin, pred, '|')) {
            buff.push_back(atoi(pred.c_str()));
        }
        data.push_back(buff);
        buff.clear();
    }
    inFile.close();

    stringstream ss;
    cout << "how many threads? : ";
    cin >> num;
    pthread_t Thd[num];  // create  pthread
    perthread per[num];
    int del = 0;
    int num_perthread = (data.size() / num) + (data.size() % num != 0);
    if (data.size() % num != 0) {
        del = (num_perthread * num) - (data.size());
    }

    start_1 = clock();
    gettimeofday(&wall_s1, NULL);

    ss << "{";
    ss << "\n";

    for (i = 0; i < num; i++) {
        per[i].thread_id = i;
        per[i].start = num * i;
        per[i].end = i * num + num;
        per[i].d=data;
        //per[i].s=n.str("");
        if (i == num - 1) {
            per[i].end -= del;
        }
        pthread_create(&Thd[i], &attr, convert, (void *) &per[i]);
    }
    pthread_attr_destroy(&attr);

    void *status;
    for (int i = 0; i < num; i++) {
        pthread_join(Thd[i], &status); 
        ss << per[i].s.str();
        per[i].s.str("");
    }

    pthread_exit(NULL);

    end_1 = clock();
    gettimeofday(&wall_e1, NULL);

    cout << "thread wall time : " << wall_e1.tv_sec - wall_s1.tv_sec << endl;
    cout << "thread CPU time : " << (end_1 - start_1) / CLOCKS_PER_SEC << endl;

    ss << "}";
    os << ss.str();
    os.close();
    data.clear();
    ss.str("");
    gettimeofday(&wall_e, NULL);
    end = clock();
    cout << "total time (walltime) : " << wall_e.tv_sec - wall_s.tv_sec << endl;
    cout << "total time (CPU) : " << (end - start) / CLOCKS_PER_SEC << endl;

    return 0;
}

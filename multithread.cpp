#include<bits/stdc++.h>
#include<pthread.h>
#include<mutex>
#include<unistd.h>
#include <sys/time.h>

using namespace std;

mutex gMutex;

void convert(vector<vector<int>  > &d,int &i, int c,int num, stringstream &s,int del, int &g){
    lock_guard<mutex>mLock(gMutex);
    int start=(i*c);
    int end=(i*c)+c;
    if(i==num-1){
        end-=del;
    }
    //cout<<"i="<<i<<endl;
    // while(g!=i){
    //     // if(g==i);
    //     //     break;
    // }
    for(int k=start ; k<end ; k++){
      // cout<<k<<endl;
        s<<"\t"<<"{"<<endl;
        for(int j=0 ;  j<20 ; j++){
            s<<"\t\t"<<"\""<<"col_"<<j+1<<"\""<<":"<<d[k][j]<<endl;
        }
        s<<"\t"<<"}"<<endl;
    }
    i++;  
}
int main(){
    double start, end;
    double start_1, end_1;

    struct timeval  wall_s , wall_e;
    struct timeval  wall_s1 , wall_e1;
    

    ifstream inFile("input.csv", ios::in);
    if (!inFile)
    {
        cout << "開啟檔案失敗！" << endl;
        exit(1);
    }   
    
    int num,i=0;
    int n=20;
    int size=5000000;
    int count=0;
    vector<vector<int> > a;
    stringstream ss;
    ofstream os;
    os.open("ouput.json");
    start=clock();
    gettimeofday(&wall_s, NULL);
    string line;
    int g=0;
    while (getline(inFile, line)){
        istringstream sin(line);                //切割字串
        vector<int> buff;
        string pred;
        while (getline(sin, pred, '|')){
            buff.push_back(atoi(pred.c_str()));
    }
        a.push_back(buff);
        buff.clear();
    }
    inFile.close();
    //cout<<a.size()<<endl;
    //cout<<a[0].size()<<endl;

    cout<<"how many threads? :";
    cin>>num;
    vector<thread>multi;
    int del=0 ;;
    int c=(a.size()/num)+(a.size()%num!=0);
    if(a.size()%num!=0){
        del=(c*num)-(a.size());
    }
    cout<<c<<endl;
    //cout<<del<<endl;
    ss<<"{";
    ss<<"\n";
    start_1=clock();
    gettimeofday(&wall_s1, NULL);
    for(i=0;i<num;i++){
        multi.push_back(thread(convert,ref(a),ref(g), c,num,ref(ss),del,ref(g)));
    }
    for(int i = 0; i < multi.size(); i++){
        multi[i].join();
    }
    end_1=clock();
    gettimeofday(&wall_e1,NULL);
    cout<<"thread walltime: "<<wall_e1.tv_sec-wall_s1.tv_sec<<endl;

    cout <<"thread時間"<<(end_1 - start_1) / CLOCKS_PER_SEC << endl;
    ss<<"}";
    //cout<<ss.str();
    os<<ss.str();
    os.close();
    a.clear();
    gettimeofday(&wall_e,NULL);
    end=clock();
    cout<<"walltime: "<<wall_e.tv_sec-wall_s.tv_sec<<endl;
     cout << "程式總時間"<<(end -start) / CLOCKS_PER_SEC << endl;
    return 0;
}


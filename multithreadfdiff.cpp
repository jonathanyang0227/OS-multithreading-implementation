#include<bits/stdc++.h>
#include <json/json.h>
#include<pthread.h>

using namespace std;

void convert(vector<vector<int>  > a, int i, int num){
    int j=0;
    ofstream os;
    os.open("ouput.json");
    Json:: Value root;
    Json::StyledWriter sw;

    for(j=(j+num*i) ; j<((i+1)*num-1); j++){
        root["col_01"]=(a[j][0]);
        root["col_02"]=(a[j][1]);
        root["col_03"]=(a[j][2]);
       root["col_04"]=(a[j][3]);
        root["col_05"]=(a[j][4]);
        root["col_06"]=(a[j][5]);
        root["col_07"]=(a[j][6]);
        root["col_08"]=(a[j][7]);
        root["col_09"]=(a[j][8]);
        root["col_10"]=(a[j][9]);
        root["col_11"]=(a[j][10]);
        root["col_12"]=(a[j][11]);
        root["col_13"]=(a[j][12]);
        root["col_14"]=(a[j][13]);
        root["col_15"]=(a[j][14]);
        root["col_16"]=(a[j][15]);
        root["col_17"]=(a[j][16]);
        root["col_18"]=(a[j][17]);
        root["col_19"]=(a[j][18]);
        root["col_20"]=(a[j][19]);
   
        cout << sw.write(root) << endl << endl;
        os << sw.write(root);
    }
    os.close();
}

int main(){
    ifstream inFile("input.csv", ios::in);
    if (!inFile)
    {
        cout << "開啟檔案失敗！" << endl;
        exit(1);
    }   

    int num,i=0;
    int n=20;
    int size=5000000;
    vector<vector<int> > a;

    string line;
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
    cout<<a.size()<<endl;
    cout<<a[0].size()<<endl;

    cout<<"howmany threads? :"<<endl;
    cin>>num;
    vector<thread>multi;
    int c=(a.size()/num)+(a.size()%num!=0);
    cout<<c<<endl;

    for(i=0;i<num;i++){
        multi.push_back(thread(convert, ref(a), i, c));
    }
    for(int i = 0; i < multi.size(); i++){
        multi[i].join();
    }
    return 0;
}


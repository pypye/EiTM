#ifndef DATA_H
#define DATA_H
#include <iostream>
#include <map>
#include <fstream>
#include <deque>
#include "login.h"
using namespace std;
struct Log{
    long long Time;
    string from;
    string change;
    int balance;
    string to;
    Log(long long _time, string _from, string _change, int _balance, string _to){
        Time = _time;
        from = _from;
        change = _change;
        balance = _balance;
        to = _to;
    }
};
class data
{

public:
    static data& getInstance(){static data instance; return instance;}
    map<string, pair<string, int>> userdata; ///pair first=password second=balance
    deque <Log> history;
    map<int, int> balancedata;
    void initData();
    void getBalance();
    void getReport();
    void saveData();
    data();
    virtual ~data();
};

#endif // DATA_H

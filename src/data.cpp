#include "data.h"

data::data()
{
    //ctor
}

data::~data()
{
    //dtor
}
void data::initData()
{
    ifstream userinput("data\\user.txt");
    string username;
    while(userinput >> username){
        string password;
        int balance;
        userinput >> password >> balance;
        userdata[username] = {password, balance};
    }
    ifstream loginput("data\\log.txt");
    long long Time;
    while(loginput >> Time){
        string from, change, to;
        int balance;
        loginput >> from >> change >> balance >> to;
        history.push_back(Log(Time, from, change, balance, to));
    }

    ifstream balanceinput("data\\balance.txt");
    int type;
    while(balanceinput >> type){
        int amount;
        balanceinput >> amount;
        balancedata[type] = amount;
    }
}
void data::saveData(){
    ofstream useroutput("data\\user.txt");
    map<string, pair<string, int>>::iterator itu;
    for (itu = data::getInstance().userdata.begin(); itu != data::getInstance().userdata.end(); itu++)
    {
        useroutput << itu->first << " " << itu->second.first << " " << itu->second.second << '\n';
    }
    ofstream logoutput("data\\log.txt");
    for(auto v : history){
        logoutput << v.Time << " ";
        logoutput << v.from << " ";
        logoutput << v.change << " ";
        logoutput << v.balance << " ";
        logoutput << v.to << '\n';
    }
    ofstream balanceoutput("data\\balance.txt");
    map<int, int>::iterator itb;
    for (itb = data::getInstance().balancedata.begin(); itb != data::getInstance().balancedata.end(); itb++)
    {
        balanceoutput << itb->first << " " << itb->second << '\n';
    }
}

void data::getBalance()
{
    if(login::getInstance().username != ""){
        cout << "User: " << login::getInstance().username << '\n';
        cout << "Balance: " << userdata[login::getInstance().username].second << '\n';
    }
    else{
        cout << "You have to login first.\n";
    }
}
void data::getReport()
{
    cout << "Last 10 activities:\n";
    for(auto v : history){
        cout << v.Time << ", ";
        if(v.change == "-") cout << v.from << " withdraw " << v.balance << '\n';
        else{
            cout << v.to << " was deposited " << v.balance << " by " << v.from << '\n';
        }
    }
}

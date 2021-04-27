#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include "login.h"
#include "data.h"
#include "balance.h"

using namespace std;
string command[] = {"balance", "-clear", "-deposit", "-exit", "-help", "-login", "-logout", "-report", "-withdraw"};
string shortcommand[] = { "-b", "-c", "-d", "-e", "-h", "-li", "-lo", "-r", "-w"};
void printHelp(){
    cout << "\n";
    cout << "List of commands:\n";
    cout << "-clear (-c)\n";
    cout << "-deposit [user] [amount] [value] [amount]... (-d)\n";
    cout << "-exit (-e)\n";
    cout << "-help (-h)\n";
    cout << "-login [username] (-li)\n";
    cout << "-logout (-lo)\n";
    cout << "-report (-r)\n";
    cout << "-withdraw [balance] (-w)\n";
    cout << "\n";
}
bool interpretInput(){
    string s;
    getline(cin, s);
    if(s == "") return 1;
    stringstream ss(s);
    vector <string> argv;
    string text;
    while(ss >> text) argv.push_back(text);
    if(argv[0] == "-clear"  || argv[0] == "-c")  return system("CLS"), 1;
    if(argv[0] == "-exit"   || argv[0] == "-e")  return 0;
    if(argv[0] == "-help"   || argv[0] == "-h")  return printHelp(), 1;
    if(argv[0] == "-login"  || argv[0] == "-li") return login::getInstance().doLogin(argv), 1;
    if(argv[0] == "-logout" || argv[0] == "-lo") return login::getInstance().doLogout(), 1;

    if(argv[0] == "-report"  || argv[0] == "-r") return data::getInstance().getReport(), 1;
    if(argv[0] == "-balance" || argv[0] == "-b") return data::getInstance().getBalance(), 1;

    if(argv[0] == "-deposit"  || argv[0] == "-d"){
        balance::getInstance().Deposit(argv);
        data::getInstance().saveData();
        return 1;
    }
    if(argv[0] == "-withdraw" || argv[0] == "-w"){
        balance::getInstance().Withdraw(argv);
        data::getInstance().saveData();
        return 1;
    }

    cout << "????????????\n";
    return 1;
}
int main(int argc, char** argv)
{
    data::getInstance().initData();
    cout << "Welcome to EiTM, type -h or -help to show list of commands.\n";
    while(interpretInput());
}

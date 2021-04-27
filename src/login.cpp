#include "login.h"

login::login(){}

login::~login(){}

void login::doLogin(vector<string> argv){
    if(login::username != ""){
        cout << "Account " << login::username << "has already logged in.\n";
        return;
    }
    if(argv.size() < 2){
        cout << "Type your username: ";
        string _username;
        cin >> _username;
        argv.push_back(_username);
    }

    if(trytime == 0){
        cout << "ATM was disabled.\n";
        return;
    }
    ///check username match
    if(data::getInstance().userdata.find(argv[1]) != data::getInstance().userdata.end()){
        ///type password not show character in console;
        HANDLE input = GetStdHandle(STD_INPUT_HANDLE);
        DWORD mode = 0;
        GetConsoleMode(input, &mode);
        SetConsoleMode(input, mode & (~ENABLE_ECHO_INPUT));

        cout << "Welcome " << argv[1] << ", Type your password: ";
        string password; cin >> password;
        SetConsoleMode(input, mode);
        cout << "\n";
        ///check password match
        if(data::getInstance().userdata[argv[1]].first == password){
            login::username = argv[1];
            cout << argv[1] << " logged in.\n";
            trytime = 5;
        }
        else{
            trytime--;
            cout << "Password does not match. You have " << trytime << " time(s) left.\n";

        }
    }
    else{
        trytime--;
        cout << "No username match. You have " << trytime << " time(s) left\n";

    }


}

void login::doLogout()
{
    if(login::username != ""){
        cout << login::username << " logged out.\n";
        login::username = "";
    }
    else{
        cout << "No account to log out.\n";
    }
}

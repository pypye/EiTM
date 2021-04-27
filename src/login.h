#ifndef LOGIN_H
#define LOGIN_H

#include <iostream>
#include <vector>
#include <windows.h>
#include "data.h"

using namespace std;
class login
{
public:
    static login& getInstance(){static login instance; return instance;}
    bool loggedIn = 0;
    int trytime = 5;
    string username = "";
    void doLogin(vector<string> argv);
    void doLogout();
    login();
    virtual ~login();
};

#endif // LOGIN_H

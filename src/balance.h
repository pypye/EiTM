#ifndef BALANCE_H
#define BALANCE_H
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "data.h"
using namespace std;
class balance
{
public:
    static balance& getInstance(){static balance instance; return instance;}

    balance();
    virtual ~balance();

    void Deposit(vector <string> argv);
    void Withdraw(vector <string> argv);
};

#endif // BALANCE_H

#include "balance.h"

balance::balance()
{
    //ctor
}

balance::~balance()
{
    //dtor
}
bool isNumber(string s)
{
    for (int i = 0; i < s.length(); i++)
        if (isdigit(s[i]) == false)
            return false;
    return true;
}
void balance::Deposit(vector<string>argv)
{
    if(login::getInstance().username == ""){
        cout << "You have to login first.\n";
        return;
    }
    if(argv.size() % 2 != 0 || argv.size() < 4){
        cout << "Cannot interpret input? Use this syntax: -deposit [user] [value] [amount]... for deposit.\n";
        return;
    }
    if(data::getInstance().userdata.find(argv[1]) == data::getInstance().userdata.end()){
        cout << "Cannot find that user?\n";
        return;
    }
    int _balance = data::getInstance().userdata[argv[1]].second;
    for(int i = 2; i < argv.size(); i += 2){
        if(data::getInstance().balancedata.find(stoi(argv[i])) == data::getInstance().balancedata.end()){
            cout << "Cannot interpret money value ??? Try 1 2 5 10 20 50 100 200 500\n";
            return;
        }
        if(!isNumber(argv[i+1])){
            cout << "Cannot interpret money amount ??? Try integer number\n";
            return;
        }
    }
    for(int i = 2; i < argv.size(); i += 2){
        data::getInstance().balancedata[stoi(argv[i])] += stoi(argv[i+1]);
        _balance += stoi(argv[i+1]) * stoi(argv[i]) ;
    }
    ///output
    cout << login::getInstance().username << " successfully deposit for: " << argv[1] << '\n';
    cout << "Old Balance: " << data::getInstance().userdata[argv[1]].second << '\n';
    cout << "New Balance: " << _balance << '\n';
    cout << "Money Input: \n";
    for(int i = 2; i < argv.size(); i += 2){
        cout << argv[i+1] << "x " << argv[i] << '\n';
    }
    cout << '\n';
    ///save data
    if(data::getInstance().history.size() == 10) data::getInstance().history.pop_front();
    data::getInstance().history.push_back(Log(1, login::getInstance().username, "+", _balance - data::getInstance().userdata[argv[1]].second, argv[1]));

    data::getInstance().userdata[argv[1]].second = _balance;
}

vector <pair<int, int>> getBalanceData(){
    map<int, int>::iterator it;
    vector <pair <int, int>> temp;
    temp.push_back({0, 0});
    for (it = data::getInstance().balancedata.begin(); it != data::getInstance().balancedata.end(); it++)
    {
        temp.push_back({it->first, it->second});
    }
    return temp;
}

void balance::Withdraw(vector<string>argv)
{
    if(login::getInstance().username == ""){
        cout << "You have to login first.\n";
        return;
    }
    string user = login::getInstance().username;
    if(data::getInstance().userdata[user].second < stoi(argv[1])){
        cout << "Insufficient money!!! Your balance: " << data::getInstance().userdata[user].second << '\n';
        return;
    }
    ///dp[i][j] go to money type i, use amount j, dp[i][j] = minimum number of sheet
    ///dp[i][j] = min(dp[i-1][j - a[i]*h] + h);  h is number of sheet
    ///tr[i][j] trace back
    ///complexity o(n*amount*amount/n) = o(amount^2);
    vector <pair<int, int>> a = getBalanceData();
    int amount = stoi(argv[1]), n = 9;
    int dp[n+1][amount+1];
    pair <int, int> tr[n+1][amount+1];
    for(int i = 0; i <= n;i++)
        for(int j = 0; j <= amount; j++) dp[i][j] = 1e9, tr[i][j] = {0, 0};
    ///base case
    for(int j = 0; j <= a[1].second; j++)
        dp[1][j] = j; /// j/a[1].first (a[1].first always = 1)
    for(int i = 2; i <= n; ++i)
        for(int j = 0; j <= amount; j++)
            for(int h = 0; h <= j/a[i].first; h++){
                if(h <= a[i].second){
                    if(dp[i][j] > dp[i-1][j-a[i].first*h] + h){
                        dp[i][j] = dp[i-1][j-a[i].first*h] + h;
                        tr[i][j] = {i-1, j-a[i].first*h};
                    }
                }
            }

    vector <int> ans;
    int x = n;
    if(dp[x][amount] != 1e9){
        ///trace back
        while(tr[x][amount] != make_pair(0, 0)){
            pair <int, int> u = tr[x][amount];
            ans.push_back((amount - u.second) / a[x].first);
            x = u.first;
            amount = u.second;
        }
        ans.push_back(amount / a[x].first); ///case sheet type 1
        reverse(ans.begin(), ans.end());

        ///output
        int _balance = data::getInstance().userdata[user].second - stoi(argv[1]);
        cout << login::getInstance().username << " successfully withdraw\n";
        cout << "Old Balance: " << data::getInstance().userdata[user].second << '\n';
        cout << "New Balance: " << _balance << '\n';
        cout << "Money Output: \n";
        for(int i = 1; i <= n; ++i){
            if(ans[i-1] != 0){
                data::getInstance().balancedata[a[i].first] -= ans[i-1];
                cout << ans[i-1] << "x " << a[i].first << '\n';
            }
        }
        ///save data
        data::getInstance().userdata[user].second = _balance;
        if(data::getInstance().history.size() == 10) data::getInstance().history.pop_front();
        data::getInstance().history.push_back(Log(1, user, "-", stoi(argv[1]), user));

        cout << '\n';
    }
    else{
        cout << "Cannot withdraw money.\n";
        return;
    }
}

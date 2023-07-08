#include <iostream>
#include <vector>
#include <utility>

using namespace std;

#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account
{
protected:
    vector<UserInfo> list;
    bool isLogin;
    UserInfo info;

public:
    Account();
    void addToList(UserInfo info);
    void addAccountToList(string fullname, string email, string phoneNumber, string username, string password, string type, bool isDisable, bool isChangePassword);
    void removeToList(string username);
    void setIsLogin(bool status);
    bool getIsLogin();
    void setInfo(UserInfo info);
    UserInfo getInfo();
    void setList(vector<UserInfo> list);
    vector<UserInfo> getList();
    bool checkInfo(string username);
    bool checkVerifyCode(string username, string code);
    void updateInfo(string username, string fullName, string email, string phoneNumber);
    void readFileAccount();
    void writeFileAccount();
    void printList();
    void printInfo();
    int checkInfo(string username, string password);
    int changePassword(string oldPassword, string newPassword, string reNewPassword);
    void writeActLog(string username, string actName);
    int forgotPassword(string type, string username);
    int forgotPassword(string username, string nCode, string newPassword, string reNewPassword);
    void activityLog(vector<pair<string, string>> &data, string username = "");
};

#endif
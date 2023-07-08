#include <iostream>
#include <string>
#include <vector>
using namespace std;
using namespace std;

#ifndef STRUCT_H
#define STRUCT_H

struct UserInfo
{
    string fullName;
    string email;
    string phoneNumber;
    string username;
    string password;
    string typeAccount;
    bool isDisable;
    bool changePassword;
};

struct Permission
{
    vector<string> viewers;
    vector<string> editors;
    vector<string> deleters;
    vector<string> renamers;
};

struct FileInfo
{
    string fileName;
    string fileSize;
    string authorName;
    string createdDate;
    vector<string> content;
};

#endif
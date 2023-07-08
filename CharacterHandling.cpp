#include <iostream>
#include <fstream>
#include <time.h>
#include "CharacterHandling.h"
using namespace std;

bool hasUppercase(const string &str)
{
    for (char c : str)
    {
        if (isupper(c))
        {
            return true;
        }
    }
    return false;
}

bool hasLowercase(const string &str)
{
    for (char c : str)
    {
        if (islower(c))
        {
            return true;
        }
    }
    return false;
}

bool hasDigit(const string &str)
{
    for (char c : str)
    {
        if (isdigit(c))
        {
            return true;
        }
    }
    return false;
}

void randomDigit(string username)
{
    fstream fout;
    fout.open("VerifyCode.txt", ios::app);
    int r;
    string code;
    srand(time(NULL));
    for (int i = 0; i < 8; i++)
    {
        r = rand() % 26;
        code += (rand() % 2 == 0) ? 'a' + r : 'A' + r;
    }
    fout << username << "|" << code << endl;
    fout.close();
}
#include <iostream>
#include <cstring>
#include <windows.h>
#include <sys/stat.h>  // create folder
#include <unistd.h>
#include <conio.h> // Include the conio.h header for _getch() function
#include "Draw.h"
#include "Draw.cpp"
#include "CharacterHandling.h"
#include "CharacterHandling.cpp"
#include "Struct.h"
#include "Account.h"
#include "Account.cpp"
#include "FileManager.h"
#include "FileManager.cpp"


using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

Account account;
FileManager file;
FileInfo fileInfo;
Permission fileAccess;
int width, height;
vector<string> previousPage;

void back();
void home();
void login();
void changePassword();
void accountInformation();
void updateAccount(string username);
void forgotPassword();
void verifyForgotPassword(string username);
void activityLog();
void activityLog(string username);
void createAccount();
void listUser();
void fileManager();
void createFile();
void PrintFiles();
void writeInfoFile(string dirName, string fileName);
void getInfoFile(string dirName, string fileName);
void moveFile(string dirName, string fileName,FileInfo fileInfo, Permission fileAccess);
void renameFile(string dirName, string fileName,FileInfo fileInfo, Permission fileAccess);
void copyFile(string dirName, string fileName,FileInfo fileInfo, Permission fileAccess);
void deleteFile(string dirName, string fileName,FileInfo fileInfo, Permission fileAccess);
void permissionsFile(string dirName, string fileName,FileInfo fileInfo, Permission fileAccess);


int main()
{
    // Ẩn hiện con trỏ nhấp nháy
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 50;
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);

    // Lấy kích thước của cửa sổ console
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(consoleHandle, &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    // Thiết lập kích thước cho vùng cửa sổ cuộn
    SMALL_RECT scrollRect;
    scrollRect.Left = 0;
    scrollRect.Top = 0;
    scrollRect.Right = width - 1;
    scrollRect.Bottom = height - 1;

    // Thiết lập kích thước bộ đệm cho vùng cửa sổ cuộn
    COORD scrollBufferSize;
    scrollBufferSize.X = width;
    scrollBufferSize.Y = height;

    // Thiết lập vùng cửa sổ cuộn
    SetConsoleWindowInfo(consoleHandle, TRUE, &scrollRect);
    SetConsoleScreenBufferSize(consoleHandle, scrollBufferSize);

    // load page default
    login();
    // createAccount();
    // listUser();
    return 0;
}

/**
 * @brief back to previous page
 * Home
 * AccountInfo
 * ChangePassword
 * UpdateAccount
 * ActivityLog
 */
void back()
{
    string previousName = previousPage[previousPage.size() - 1];
    if (previousName == "Home")
    {
        home();
    }

    if (previousName == "AccountInfo")
    {
        accountInformation();
    }
}

void home()
{
    system("cls");
    previousPage.push_back("Home");

    // Tạo một cửa sổ con để hiển thị giao diện đăng nhập
    int homeWinHeight = 13;
    int homeWinWidth = 40;
    int homeWinY = (height - homeWinHeight) / 2;
    int homeWinX = (width - homeWinWidth) / 2;

    drawBox(homeWinX, homeWinY, homeWinWidth, homeWinHeight);
    gotoxy(homeWinX + 2, homeWinY + 2);
    cout << "\t\tMenu";
    int selectedOption = 1;      // Store the currently selected option
    bool optionSelected = false; // Flag to indicate if an option is selected

    while (!optionSelected)
    {
        // Print the menu options
        gotoxy(homeWinX + 2, homeWinY + 4);
        if (selectedOption == 1)
            cout << "-> 1. Account info.";
        else
            cout << "   1. Account info.";

        gotoxy(homeWinX + 2, homeWinY + 5);
        if (selectedOption == 2) // display with admin
            cout << "-> 2. Account list.";
        else
            cout << "   2. Account list.";

        gotoxy(homeWinX + 2, homeWinY + 6);
        if (selectedOption == 3)
            cout << "-> 3. Activity logs.";
        else
            cout << "   3. Activity logs.";

        gotoxy(homeWinX + 2, homeWinY + 7);
        if (selectedOption == 4)
            cout << "-> 4. File manager.";
        else    
            cout << "   4. File manager.";    
            
        gotoxy(homeWinX + 2, homeWinY + 8);
        if (selectedOption == 5)        
            cout << "-> 5. Create user.";
        else
            cout << "   5. Create user.";
        
        gotoxy(homeWinX + 2, homeWinY + 9);
        if (selectedOption == 6)        
            cout << "-> 6. Logout";
        else
            cout << "   6. Logout";

        // Get the user input
        char key = _getch();

        // Process the user input
        switch (key)
        {
        case 72: // Up arrow key
            if (selectedOption > 1)
                selectedOption--;
            break;
        case 80: // Down arrow key
            if (selectedOption < 6)
                selectedOption++;
            break;
        case 13: // Enter key
            optionSelected = true;
            break;
        default:
            break;
        }
    }

    // Process the selected option
    switch (selectedOption)
    {
    case 1:
        accountInformation();
        break;
    case 2:
        // Handle Account list option
        listUser();
        break;
    case 3:
        // Handle Activity logs option
        activityLog();
        break;
    case 4:
        // Handle Logout option
        fileManager();
        break;
    case 5:
        createAccount();
        break;
    case 6:
        break;    
    default:
        break;
    }
}

void login()
{
    system("cls");

    // Tạo một cửa sổ con để hiển thị giao diện đăng nhập
    int loginWinHeight = 10;
    int loginWinWidth = 40;
    int loginWinY = (height - loginWinHeight) / 2;
    int loginWinX = (width - loginWinWidth) / 2;

    drawBox(loginWinX, loginWinY, loginWinWidth, loginWinHeight);

    gotoxy(loginWinX + 2, loginWinY + 2);
    cout << "\tLogin";

    int selectedOption = 1;      // Store the currently selected option
    bool optionSelected = false; // Flag to indicate if an option is selected

    while (!optionSelected)
    {
        // Print the menu options
        gotoxy(loginWinX + 10, loginWinY + 7);
        if (selectedOption == 1)
            cout << "[ Submit ]";
        else
            cout << "  Submit  ";

        gotoxy(loginWinX + 10, loginWinY + 8);
        if (selectedOption == 2)
            cout << "[ Forgot password? ]";
        else
            cout << "  Forgot password?  ";

        // Get the user input
        char key = _getch();

        // Process the user input
        switch (key)
        {
        case 72: // Up arrow key
            if (selectedOption > 1)
                selectedOption--;
            break;
        case 80: // Down arrow key
            if (selectedOption < 3)
                selectedOption++;
            break;
        case 13: // Enter key
            optionSelected = true;
            break;
        default:
            break;
        }
    }

    if (selectedOption == 1)
    {
        gotoxy(loginWinX + 2, loginWinY + 4);
        cout << "Username: ";

        gotoxy(loginWinX + 2, loginWinY + 5);
        cout << "Password: ";

        char username[20];
        char password[20];

        gotoxy(loginWinX + 18, loginWinY + 4);
        cin >> username;

        gotoxy(loginWinX + 18, loginWinY + 5);
        // Vô hiệu hóa hiển thị ký tự trên màn hình
        DWORD mode;
        HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
        GetConsoleMode(handle, &mode);
        SetConsoleMode(handle, mode & ~ENABLE_ECHO_INPUT);
        cin >> password;
        // Bật lại hiển thị ký tự trên màn hình
        SetConsoleMode(handle, mode);

        gotoxy(loginWinX + 2, loginWinY + 3);
        SetConsoleTextAttribute(hConsole, 14);

        int msg = account.checkInfo(username, password);
        if (username == NULL || password == NULL)
        {
            cout << "Fill full the information." << endl;
        }
        else
        {
            if (msg == 1)
            {
                cout << "Login success." << endl;
                account.writeActLog(username, "login success.");
                SetConsoleTextAttribute(hConsole, 15);
                sleep(3);
                home();
            }
            else
            {
                if (msg == -1)
                    cout << "Username not found!" << endl;
                else if (msg == -2)
                    cout << "Incorrect password!" << endl;
                else if (msg == -3)
                {
                    cout << "You need to change password." << endl;
                    sleep(3);
                    changePassword();
                }
                else if (msg == -4)
                    cout << "Your account has been ban." << endl;
                sleep(3);

                // reset text color
                SetConsoleTextAttribute(hConsole, 15);
                // reset form
                login();
            }
        }
    }
    else if (selectedOption == 2)
    {
        forgotPassword();
    }
}

void changePassword()
{
    system("cls");
    previousPage.push_back("ChangePassword");

    // create child window
    int changePasswordWinHeight = 13;
    int changePasswordWinWidth = 50;
    int changePasswordWinY = (height - changePasswordWinHeight) / 2;
    int changePasswordWinX = (width - changePasswordWinWidth) / 2;

    drawBox(changePasswordWinX, changePasswordWinY, changePasswordWinWidth, changePasswordWinHeight);

    gotoxy(changePasswordWinX + 2, changePasswordWinY + 2);
    cout << "\t\tChange Password";

    gotoxy(changePasswordWinX + 2, changePasswordWinY + 4);
    cout << "Old Password: ";

    gotoxy(changePasswordWinX + 2, changePasswordWinY + 5);
    cout << "New Password: ";

    gotoxy(changePasswordWinX + 2, changePasswordWinY + 6);
    cout << "Renew Password : ";

    char oldPassword[20];
    char newPassword[20];
    char reNewPassword[20];

    gotoxy(changePasswordWinX + 25, changePasswordWinY + 4);
    cin >> oldPassword;

    gotoxy(changePasswordWinX + 25, changePasswordWinY + 5);
    cin >> newPassword;

    gotoxy(changePasswordWinX + 25, changePasswordWinY + 6);
    cin >> reNewPassword;

    int selectedOption = 1;      // Store the currently selected option
    bool optionSelected = false; // Flag to indicate if an option is selected

    while (!optionSelected)
    {
        // Print the menu options
        gotoxy(changePasswordWinX + 10, changePasswordWinY + 8);
        if (selectedOption == 1)
            cout << "[ Submit ]";
        else
            cout << "  Submit  ";

        gotoxy(changePasswordWinX + 10, changePasswordWinY + 9);
        if (selectedOption == 2)
            cout << "[ Back ]";
        else
            cout << "  Back  ";

        // Get the user input
        char key = _getch();

        // Process the user input
        switch (key)
        {
        case 72: // Up arrow key
            if (selectedOption > 1)
                selectedOption--;
            break;
        case 80: // Down arrow key
            if (selectedOption < 4)
                selectedOption++;
            break;
        case 13: // Enter key
            optionSelected = true;
            break;
        default:
            break;
        }
    }

    int msg = account.changePassword(oldPassword, newPassword, reNewPassword);
    // Process the selected option
    switch (selectedOption)
    {
    case 1:
        gotoxy(changePasswordWinX + 2, changePasswordWinY + 3);
        if (msg != 1)
        {
            gotoxy(changePasswordWinX + 2, changePasswordWinY + 3);
            if (msg == -1)
                cout << "Old password is incorrect, Check again!" << endl;
            else if (msg == -2)
                cout << "New password aren't same with the new one." << endl;
            else if (msg == -3)
                cout << "Password has to be at least 8 letter." << endl;
            else if (msg == -4)
                cout << "Password have at least 1 number and 1 special letter." << endl;

            sleep(3);
            changePassword();
        }
        else
        {
            system("cls");
            cout << "Change password success!" << endl;
            sleep(2);
            home();
        }
        break;
    case 2:
        previousPage.pop_back();
        back();
        break;
    default:
        break;
    }
}

void accountInformation()
{
    system("cls");
    previousPage.push_back("AccountInfo");

    int accountInfoWinHeight = 15;
    int accountInfoWinWidth = 50;
    int accountInfoWinY = (height - accountInfoWinHeight) / 2;
    int accountInfoWinX = (width - accountInfoWinWidth) / 2;

    drawBox(accountInfoWinX, accountInfoWinY, accountInfoWinWidth, accountInfoWinHeight);

    gotoxy(accountInfoWinX + 2, accountInfoWinY + 2);
    cout << "\t\tAccount information";

    gotoxy(accountInfoWinX + 5, accountInfoWinY + 4);
    cout << "Fullname: ";
    gotoxy(accountInfoWinX + 5, accountInfoWinY + 5);
    cout << "Email: ";
    gotoxy(accountInfoWinX + 5, accountInfoWinY + 6);
    cout << "Phone number: ";
    gotoxy(accountInfoWinX + 5, accountInfoWinY + 7);
    cout << "Username: ";
    gotoxy(accountInfoWinX + 5, accountInfoWinY + 8);
    cout << "Type account: ";

    gotoxy(accountInfoWinX + 20, accountInfoWinY + 4);
    cout << account.getInfo().fullName;

    gotoxy(accountInfoWinX + 20, accountInfoWinY + 5);
    cout << account.getInfo().email;

    gotoxy(accountInfoWinX + 20, accountInfoWinY + 6);
    cout << account.getInfo().phoneNumber;

    gotoxy(accountInfoWinX + 20, accountInfoWinY + 7);
    cout << account.getInfo().username;

    gotoxy(accountInfoWinX + 20, accountInfoWinY + 8);
    cout << account.getInfo().typeAccount;

    int selectedOption = 1;      // Store the currently selected option
    bool optionSelected = false; // Flag to indicate if an option is selected

    while (!optionSelected)
    {
        // Print the menu options
        gotoxy(accountInfoWinX + 10, accountInfoWinY + 11);
        if (selectedOption == 1)
            cout << "[ Update information ]";
        else
            cout << "  Update information  ";

        gotoxy(accountInfoWinX + 10, accountInfoWinY + 12);
        if (selectedOption == 2)
            cout << "[ Change password ]";
        else
            cout << "  Change password  ";

        gotoxy(accountInfoWinX + 10, accountInfoWinY + 13);
        if (selectedOption == 3)
            cout << "[ Back ]";
        else
            cout << "  Back  ";

        // Get the user input
        char key = _getch();

        // Process the user input
        switch (key)
        {
        case 72: // Up arrow key
            if (selectedOption > 1)
                selectedOption--;
            break;
        case 80: // Down arrow key
            if (selectedOption < 4)
                selectedOption++;
            break;
        case 13: // Enter key
            optionSelected = true;
            break;
        default:
            break;
        }
    }

    // Process the selected option
    switch (selectedOption)
    {
    case 1:
        updateAccount(account.getInfo().username);
        break;
    case 2:
        changePassword();
        break;
    case 3:
        previousPage.pop_back();
        back();
        break;
    default:
        break;
    }
}

void updateAccount(string username)
{
    system("cls");
    previousPage.push_back("UpdateAccount");

    int accountWinHeight = 15;
    int accountWinWidth = 50;
    int accountWinY = (height - accountWinHeight) / 2;
    int accountWinX = (width - accountWinWidth) / 2;

    drawBox(accountWinX, accountWinY, accountWinWidth, accountWinHeight);

    gotoxy(accountWinX + 2, accountWinY + 2);
    cout << "\t\tChange information";

    // Info
    string fullName = account.getInfo().fullName;
    string email = account.getInfo().email;
    string phoneNumber = account.getInfo().phoneNumber;

    gotoxy(accountWinX + 5, accountWinY + 4);
    cout << "Full name: ";
    cout << fullName;

    char ch;
    while ((ch = _getch()) != '\r')
    {
        if (ch == '\b')
        {
            if (!fullName.empty())
            {
                cout << "\b \b";
                fullName.pop_back();
            }
        }
        else
        {
            cout << ch;
            fullName += ch;
        }
    }

    gotoxy(accountWinX + 5, accountWinY + 5);
    cout << "Phone number: ";
    cout << phoneNumber;
    while ((ch = _getch()) != '\r')
    {
        if (ch == '\b')
        {
            if (!phoneNumber.empty())
            {
                cout << "\b \b";
                phoneNumber.pop_back();
            }
        }
        else
        {
            cout << ch;
            phoneNumber += ch;
        }
    }

    gotoxy(accountWinX + 5, accountWinY + 6);
    cout << "Email: ";
    cout << email;
    while ((ch = _getch()) != '\r')
    {
        if (ch == '\b')
        {
            if (!email.empty())
            {
                cout << "\b \b";
                email.pop_back();
            }
        }
        else
        {
            cout << ch;
            email += ch;
        }
    }

    int selectedOption = 1;      // Store the currently selected option
    bool optionSelected = false; // Flag to indicate if an option is selected

    while (!optionSelected)
    {
        // Print the menu options
        gotoxy(accountWinX + 10, accountWinY + 11);
        if (selectedOption == 1)
            cout << "[ Submit ]";
        else
            cout << "  Submit  ";

        gotoxy(accountWinX + 10, accountWinY + 12);
        if (selectedOption == 2)
            cout << "[ Cancel ]";
        else
            cout << "  Cancel  ";

        // Get the user input
        char key = _getch();

        // Process the user input
        switch (key)
        {
        case 72: // Up arrow key
            if (selectedOption > 1)
                selectedOption--;
            break;
        case 80: // Down arrow key
            if (selectedOption < 4)
                selectedOption++;
            break;
        case 13: // Enter key
            optionSelected = true;
            break;
        default:
            break;
        }
    }

    // Process the selected option
    switch (selectedOption)
    {
    case 1:
        account.updateInfo(username, fullName, email, phoneNumber);
        cout << "Update success.";
        previousPage.pop_back();
        back();
        break;
    case 2:
        previousPage.pop_back();
        back();
        break;
    default:
        break;
    }
}

/**
 * @brief If user forgot password, user can visit this page to reset the password.
 * It will ask user to enter the phone number or email and username to check in system
 *
 */
void forgotPassword()
{
    system("cls");
    int forgotPageWinHeight = 15;
    int forgotPageWinWidth = 80;
    int forgotPageWinY = (height - forgotPageWinHeight) / 2;
    int forgotPageWinx = (width - forgotPageWinWidth) / 2;

    drawBox(forgotPageWinx, forgotPageWinY, forgotPageWinWidth, forgotPageWinHeight);

    gotoxy(forgotPageWinx + 2, forgotPageWinY + 2);
    cout << "\t\tForgot Password";

    gotoxy(forgotPageWinx + 2, forgotPageWinY + 4);
    cout << "Email/PhoneNumber: ";

    gotoxy(forgotPageWinx + 2, forgotPageWinY + 5);
    cout << "Username: ";

    char emailPhoneNum[30];
    char username[20];
    gotoxy(forgotPageWinx + 25, forgotPageWinY + 4);
    cin >> emailPhoneNum;

    gotoxy(forgotPageWinx + 25, forgotPageWinY + 5);
    cin >> username;
    int selectedOption = 1;      // Store the currently selected option
    bool optionSelected = false; // Flag to indicate if an option is selected
    while (!optionSelected)
    {
        // Print the menu options
        gotoxy(forgotPageWinx + 10, forgotPageWinY + 8);
        if (selectedOption == 1)
            cout << "[ Submit ]";
        else
            cout << "  Submit  ";

        gotoxy(forgotPageWinx + 10, forgotPageWinY + 9);
        if (selectedOption == 2)
            cout << "[ Back ]";
        else
            cout << "  Back  ";
        // Get the user input
        char key = _getch();

        // Process the user input
        switch (key)
        {
        case 72: // Up arrow key
            if (selectedOption > 1)
                selectedOption--;
            break;
        case 80: // Down arrow key
            if (selectedOption < 4)
                selectedOption++;
            break;
        case 13: // Enter key
            optionSelected = true;
            break;
        default:
            break;
        }
        int msg = account.forgotPassword(emailPhoneNum, username);
        gotoxy(forgotPageWinx + 2, forgotPageWinY + 3);
        if (msg != 1)
        {
            SetConsoleTextAttribute(hConsole, 14);
            if (msg == -1)
                cout << "Email/ phone number is incorrect, please check again!" << endl;
            else if (msg == -2)
                cout << "Username not found, please check again!" << endl;
            SetConsoleTextAttribute(hConsole, 15);
            sleep(5);
            forgotPassword();
        }
        else
        {
            SetConsoleTextAttribute(hConsole, 14);
            cout << "Code has been sent to your email/ phone number. Please check this out." << endl;
            sleep(5);
            SetConsoleTextAttribute(hConsole, 15);
            verifyForgotPassword(username);
        }
    }
}

/**
 * @brief After entering the username and phone number, it will redirect to  verification page. It will check the verification code and the user will enter a new password
 *
 * @param username
 */
void verifyForgotPassword(string username)
{
    system("cls");
    int forgotPageWinHeight = 10;
    int forgotPageWinWidth = 50;
    int forgotPageWinY = (height - forgotPageWinHeight) / 2;
    int forgotPageWinx = (width - forgotPageWinWidth) / 2;

    drawBox(forgotPageWinx, forgotPageWinY, forgotPageWinWidth, forgotPageWinHeight);

    gotoxy(forgotPageWinx + 2, forgotPageWinY + 2);
    cout << "\t\tVerify and change";

    gotoxy(forgotPageWinx + 5, forgotPageWinY + 4);
    cout << "Enter Code: ";

    gotoxy(forgotPageWinx + 5, forgotPageWinY + 5);
    cout << "New Password: ";

    gotoxy(forgotPageWinx + 5, forgotPageWinY + 6);
    cout << "Renew Password : ";

    char nCode[20];
    char newPassword[20];
    char reNewPassword[20];

    gotoxy(forgotPageWinx + 25, forgotPageWinY + 4);
    cin >> nCode;

    gotoxy(forgotPageWinx + 25, forgotPageWinY + 5);
    cin >> newPassword;

    gotoxy(forgotPageWinx + 25, forgotPageWinY + 6);
    cin >> reNewPassword;

    int selectedOption = 1;      // Store the currently selected option
    bool optionSelected = false; // Flag to indicate if an option is selected

    while (!optionSelected)
    {
        // Print the menu options
        gotoxy(forgotPageWinx + 10, forgotPageWinY + 8);
        if (selectedOption == 1)
            cout << "[ Submit ]";
        else
            cout << "  Submit  ";

        gotoxy(forgotPageWinx + 10, forgotPageWinY + 9);
        if (selectedOption == 2)
            cout << "[ Back ]";
        else
            cout << "  Back  ";

        // Get the user input
        char key = _getch();

        // Process the user input
        switch (key)
        {
        case 72: // Up arrow key
            if (selectedOption > 1)
                selectedOption--;
            break;
        case 80: // Down arrow key
            if (selectedOption < 4)
                selectedOption++;
            break;
        case 13: // Enter key
            optionSelected = true;
            break;
        default:
            break;
        }

        int msg = account.forgotPassword(username, nCode, newPassword, reNewPassword);
        gotoxy(forgotPageWinx + 2, forgotPageWinY + 3);
        if (msg != 1)
        {
            if (msg == -1)
                cout << "Your verify code is incorrect, please check again!" << endl;
            else if (msg == -2)
                cout << "New password aren't same with the new one." << endl;
            else if (msg == -3)
                cout << "Password has to be at least 8 letter." << endl;
            else if (msg == -4)
                cout << "Password have at least 1 number and 1 special letter." << endl;

            sleep(4);
            verifyForgotPassword(username);
        }
        else
        {
            cout << "Change password success!" << endl;
            account.writeActLog(username, "reset password successfully.");
            sleep(2);
            login();
        }
    }
}

/**
 * @brief View other user's activity. Only admin can view.
 *
 */
void activityLog()
{
    system("cls");
    previousPage.push_back("ActivityLog");

    vector<pair<string, string>> data;
    account.activityLog(data);

    int accountWinHeight = 10 + data.size();
    int accountWinWidth = 60;
    int accountWinY = (height - accountWinHeight) / 3;
    int accountWinX = (width - accountWinWidth) / 2;

    drawBox(accountWinX, accountWinY, accountWinWidth, accountWinHeight);

    gotoxy(accountWinX + 5, accountWinY + 2);
    cout << "\t\tActivity log";

    int i;
    for (i = 0; i < data.size(); i++)
    {
        gotoxy(accountWinX + 2, accountWinY + 4 + i);
        cout << data[i].first << ":\t" << data[i].second;
    }

    int selectedOption = 1;      // Store the currently selected option
    bool optionSelected = false; // Flag to indicate if an option is selected

    while (!optionSelected)
    {
        // Print the menu options
        gotoxy(accountWinX + 2, accountWinY + accountWinHeight - 5);
        if (selectedOption == 1)
            cout << "[ Back ]";
        else
            cout << "  Back  ";

        // Get the user input
        char key = _getch();

        // Process the user input
        if (key == 13)
            optionSelected = true;
    }

    // Process the selected option
    switch (selectedOption)
    {
    case 1:
        previousPage.pop_back();
        back();
        break;
    default:
        break;
    }
}

/**
 * @brief View other user's activity. Only admin can view.
 *
 * @param username
 */
void activityLog(string username)
{
    system("cls");

    vector<pair<string, string>> data;
    account.activityLog(data, username);

    int accountWinHeight = 10 + data.size();
    int accountWinWidth = 60;
    int accountWinY = (height - accountWinHeight) / 3;
    int accountWinX = (width - accountWinWidth) / 2;

    drawBox(accountWinX, accountWinY, accountWinWidth, accountWinHeight);

    gotoxy(accountWinX + 5, accountWinY + 2);
    cout << "\t\tActivity log";

    int i;
    for (i = 0; i < data.size(); i++)
    {
        gotoxy(accountWinX + 2, accountWinY + 4 + i);
        cout << data[i].first << ":\t" << data[i].second;
    }

    int selectedOption = 1;      // Store the currently selected option
    bool optionSelected = false; // Flag to indicate if an option is selected

    while (!optionSelected)
    {
        // Print the menu options
        gotoxy(accountWinX + 2, accountWinY + accountWinHeight - 5);
        if (selectedOption == 1)
            cout << "[ Back ]";
        else
            cout << "  Back  ";

        // Get the user input
        char key = _getch();

        // Process the user input
        if (key == 13)
            optionSelected = true;
    }

    // Process the selected option
    switch (selectedOption)
    {
    case 1:
        previousPage.pop_back();
        back();
        break;
    default:
        break;
    }
}

/**
 * @brief Create a Account object
 * Only admins can access to page.
 * In this page, admin can create user and set some option for this.
 */
void createAccount()
{
    system("cls");
    previousPage.push_back("CreateAccount");

    //! if this isn't admin => go back to previous page
    if (account.getInfo().typeAccount != "administrator")
    {
        previousPage.pop_back();
        back();
    }

    int createAccountWinHeight = 20;
    int createAccountWinWidth = 60;
    int createAccountWinY = (height - createAccountWinHeight) / 2;
    int createAccountWinX = (width - createAccountWinWidth) / 2;

    drawBox(createAccountWinX, createAccountWinY, createAccountWinWidth, createAccountWinHeight);

    // set center text
    int fillInfoX = createAccountWinX + (createAccountWinWidth - 19) / 2; // 19 is the length of "Fill your information"

    gotoxy(fillInfoX, createAccountWinY + 2);
    cout << "Fill your information";

    gotoxy(createAccountWinX + 2, createAccountWinY + 4);
    cout << "Full name: ";

    gotoxy(createAccountWinX + 2, createAccountWinY + 5);
    cout << "Email: ";

    gotoxy(createAccountWinX + 2, createAccountWinY + 6);
    cout << "Phone number: ";

    gotoxy(createAccountWinX + 2, createAccountWinY + 7);
    cout << "Username: ";

    gotoxy(createAccountWinX + 2, createAccountWinY + 8);
    cout << "Password: ";

    gotoxy(createAccountWinX + 2, createAccountWinY + 9);
    cout << "Confirm password: ";

    gotoxy(createAccountWinX + 2, createAccountWinY + 10);
    cout << "Account type: ";

    string fullname, email, phoneNumber, username, password, confirmPassword, type="user";
    bool isAdmin = false, isUser = true;
    bool isDisable = false, isChangePassword = false;

    cin.ignore();

    gotoxy(createAccountWinX + 20, createAccountWinY + 4);
    getline(cin, fullname);

    gotoxy(createAccountWinX + 20, createAccountWinY + 5);
    getline(cin, email);

    gotoxy(createAccountWinX + 20, createAccountWinY + 6);
    getline(cin, phoneNumber);

    gotoxy(createAccountWinX + 20, createAccountWinY + 7);
    getline(cin, username);

    while (account.checkInfo(username))
    {
        gotoxy(createAccountWinX + 2, createAccountWinY + 20);
        cout << "The account already exists!"; // Account is exists

        gotoxy(createAccountWinX + 20, createAccountWinY + 7);
        cout << setw(createAccountWinWidth - 22) << " "; // Xóa nội dung dòng tài khoản
        gotoxy(createAccountWinX + 20, createAccountWinY + 7);
        getline(cin, username);

        gotoxy(createAccountWinX + 2, createAccountWinY + 20);
        cout << setw(createAccountWinWidth) << " "; // Xóa nội dung dòng thông báo
    }

    gotoxy(createAccountWinX + 20, createAccountWinY + 8);
    getline(cin, password);

    string passwordRequirements = "";

    // check password
    while (password.length() < 8 || password.length() > 12 || !hasUppercase(password) || !hasLowercase(password) || !hasDigit(password))
    {
        passwordRequirements = "";
        if (password.length() < 8 || password.length() > 12)
        {
            passwordRequirements += "8-12 characters, ";
        }
        if (!hasUppercase(password))
        {
            passwordRequirements += "at least one uppercase letter, ";
        }
        if (!hasLowercase(password))
        {
            passwordRequirements += "at least one lowercase letter, ";
        }
        if (!hasDigit(password))
        {
            passwordRequirements += "at least one digit, ";
        }

        gotoxy(createAccountWinX + 2, createAccountWinY + 20);
        cout << "Password required " << passwordRequirements.substr(0, passwordRequirements.length() - 2);

        gotoxy(createAccountWinX + 20, createAccountWinY + 8);
        cout << setw(createAccountWinWidth - 22) << " "; // Xóa nội dung dòng mật khẩu
        gotoxy(createAccountWinX + 20, createAccountWinY + 8);
        getline(cin, password);

        gotoxy(createAccountWinX + 2, createAccountWinY + 20);
        cout << setw(createAccountWinWidth + 45) << " "; // Xóa nội dung dòng thông báo
    }

    gotoxy(createAccountWinX + 20, createAccountWinY + 9);
    getline(cin, confirmPassword);

    // check re-password
    while (password != confirmPassword)
    {
        gotoxy(createAccountWinX + 2, createAccountWinY + 20);
        cout << "Password mismatch. Try again!";

        gotoxy(createAccountWinX + 20, createAccountWinY + 9);
        cout << setw(createAccountWinWidth - 22) << " "; // Xóa nội dung dòng nhập lại mật khẩu
        gotoxy(createAccountWinX + 20, createAccountWinY + 9);
        getline(cin, confirmPassword);
    }

    // account type
    gotoxy(createAccountWinX + 20, createAccountWinY + 10);
    while (true)
    {
        gotoxy(createAccountWinX + 2, createAccountWinY + 11);
        // Draw checkboxes
        cout << "Press button 1, 2 or Q to:";
        gotoxy(createAccountWinX + 2, createAccountWinY + 12);
        drawCheckbox(isAdmin, "Administrator");
        gotoxy(createAccountWinX + 2, createAccountWinY + 13);
        drawCheckbox(isUser, "User");

        // Wait for user input
        char input = getch();
        cout << input;
        // Handle user input
        switch (input)
        {
        case '1':
            isAdmin = !isAdmin;
            isUser = false;
            type = "administrator";
            break;
        case '2':
            isUser = !isUser;
            isAdmin = false;
            type = "user";
            break;
        default:
            break;
        }

        if (input == 'q' || input == 'Q')
            break;
    }
    // if not choose type account => default is user
    if (!isUser && !isAdmin)
    {
        type = "user";
        isUser = true;
    }

    // account option
    while (true)
    {
        gotoxy(createAccountWinX + 2, createAccountWinY + 14);
        // Draw checkboxes
        cout << "Press button 1, 2 or Q to:";
        gotoxy(createAccountWinX + 2, createAccountWinY + 15);
        drawCheckbox(isChangePassword, "User must change password at next logon");
        gotoxy(createAccountWinX + 2, createAccountWinY + 16);
        drawCheckbox(isDisable, "Account is disabled");

        // Wait for user input
        char input = getch();

        // Handle user input
        switch (input)
        {
        case '1':
            isChangePassword = !isChangePassword;
            break;
        case '2':
            isDisable = !isDisable;
            break;
        default:
            break;
        }
        if (input == 'q' || input == 'Q')
            break;
    }

    if (fullname.empty() || email.empty() || phoneNumber.empty() || username.empty() || password.empty() || confirmPassword.empty())
    {
        cout << "Fill full the information." << endl;
    }
    else
    {
        gotoxy(createAccountWinX + 2, createAccountWinY + 17);
        cout << "Create account is successful." << endl;
        account.writeActLog(account.getInfo().username, "creates an account with username " + username);
        account.addAccountToList(fullname, email, phoneNumber, username, password, type, isDisable, isChangePassword);

        // auto create folder when create an account
        string folder = "./FileManager/" + username;
        
        mkdir(folder.c_str());

        sleep(3);
        home();
    }
}

void listUser()
{
    system("cls");
    previousPage.push_back("ListUser");
    vector<UserInfo> dataUser = account.getList();

    int userListHeight = 5 + dataUser.size();
    int userListWidth = 120;
    int userListY = (height - userListHeight) / 3;
    int userListX = (width - userListWidth) / 2;

    drawBox(userListX, userListY, userListWidth, userListHeight);
    gotoxy(userListX + 3, userListY + 2);
    cout << "STT";
    gotoxy(userListX + 10, userListY + 2);
    cout << "Name";
    gotoxy(userListX + 30, userListY + 2);
    cout << "Email";
    gotoxy(userListX + 55, userListY + 2);
    cout << "Phone number";
    gotoxy(userListX + 70, userListY + 2);
    cout << "Username";
    gotoxy(userListX + 85, userListY + 2);
    cout << "Role";
    gotoxy(userListX + 100, userListY + 2);
    cout << "Status";
    int row = 3;
    for (int i = 0; i < dataUser.size(); i++)
    {
        gotoxy(userListX + 3, userListY + row);
        cout << i + 1;
        gotoxy(userListX + 10, userListY + row);
        cout << dataUser[i].fullName;
        gotoxy(userListX + 30, userListY + row);
        cout << dataUser[i].email;
        gotoxy(userListX + 55, userListY + row);
        cout << dataUser[i].phoneNumber;
        gotoxy(userListX + 70, userListY + row);
        cout << dataUser[i].username;
        gotoxy(userListX + 85, userListY + row);
        cout << dataUser[i].typeAccount;
        gotoxy(userListX + 100, userListY + row);
        cout << dataUser[i].isDisable;
        row++;
    }

    int selectedOption = 1;      // Store the currently selected option
    bool optionSelected = false; // Flag to indicate if an option is selected

    while (!optionSelected)
    {
        // Print the menu options
        gotoxy(userListX + 30, userListY + userListHeight - 2);
        if (selectedOption == 1)
            cout << "[ Back ]";
        else
            cout << "  Back  ";

        // Get the user input
        char key = _getch();

        // Process the user input
        if (key == 13)
            optionSelected = true;
    }

    // Process the selected option
    switch (selectedOption)
    {
    case 1:
        previousPage.pop_back();
        back();
        break;
    default:
        break;
    }
}

void fileManager(){
    system("cls");
    previousPage.push_back("Home");

    // Tạo một cửa sổ con để hiển thị giao diện đăng nhập
    int fileHeight = 10;
    int fileWidth = 40;
    int fileY = (height - fileHeight) / 2;
    int fileX = (width - fileWidth) / 2;

    drawBox(fileX, fileY, fileWidth, fileHeight);
    gotoxy(fileX + 2, fileY + 2);
    cout << "\t\tMenu";
    int selectedOption = 1;      // Store the currently selected option
    bool optionSelected = false; // Flag to indicate if an option is selected

    while (!optionSelected)
    {
        // Print the menu options
        gotoxy(fileX + 2, fileY + 4);
        if (selectedOption == 1)
            cout << "-> 1. Create file.";
        else
            cout << "   1. Create file.";

        gotoxy(fileX + 2, fileY + 5);
        if (selectedOption == 2) // display with admin
            cout << "-> 2. List file.";
        else
            cout << "   2. List file.";
        
        gotoxy(fileX + 2, fileY + 6);
        if (selectedOption == 3)        
            cout << "-> 3. Back";
        else
            cout << "   3. Back";

        // Get the user input
        char key = _getch();

        // Process the user input
        switch (key)
        {
        case 72: // Up arrow key
            if (selectedOption > 1)
                selectedOption--;
            break;
        case 80: // Down arrow key
            if (selectedOption < 3)
                selectedOption++;
            break;
        case 13: // Enter key
            optionSelected = true;
            break;
        default:
            break;
        }
    }

    // Process the selected option
    switch (selectedOption)
    {
    case 1:
        createFile();
        break;
    case 2:
        // Handle list file option
        PrintFiles();
        break;
    case 3:
        previousPage.pop_back();
        back();
        break;    
    default:
        break;
    }
}

void createFile()
{
    system("cls");

    int fileHeight = 10;
    int fileWidth = 40;
    int fileY = (height - fileHeight) / 2;
    int fileX = (width - fileWidth) / 2;

    drawBox(fileX, fileY, fileWidth, fileHeight); 

    gotoxy(fileX + 2, fileY + 2);
    string dirName;
    cout << "Enter username: ";
    cin >> dirName;

    gotoxy(fileX + 2, fileY + 3);
    string fileName;   
    cout << "Enter file name: ";
    cin >> fileName;
    file.createFile(dirName, fileName);

    int selectedOption = 1;      // Store the currently selected option
    bool optionSelected = false; // Flag to indicate if an option is selected


    while (!optionSelected)
    {
        // Print the menu options
        gotoxy(fileX + 2, fileY + 4);
        if (selectedOption == 1)
            cout << "[ Back ]";

        // Get the user input
        char key = _getch();

        // Process the user input
        if (key == 13)
            optionSelected = true;
    }

    // Process the selected option
    switch (selectedOption)
    {
    case 1:
        previousPage.pop_back();
        back();
        break;
    default:
        break;
    }
}

void PrintFiles()
{
    system("cls");
    int fileHeight = 10;
    int fileWidth = 40;
    int fileY = (height - fileHeight) / 2;
    int fileX = (width - fileWidth) / 2;

    drawBox(fileX, fileY, fileWidth, fileHeight); 

    string folderName, fname;
    gotoxy(fileX + 2, fileY + 2);
    cout << "Enter foldername: ";
    cin >> folderName;
    int d=0;
    vector<UserInfo> dataUser = account.getList();
    for (int i = 0; i < dataUser.size(); i++){
        if (folderName == dataUser[i].username)
        {
            fname = folderName;
        }
        else d++;
    }    
    if (d==dataUser.size()) cout << "No one has this name!";
        
    system("cls");
    previousPage.push_back("File manager");

    drawBox(fileX, fileY, fileWidth, fileHeight);  
    
    string folderPath = "./FileManager/" + fname; 
    vector<string> fileList = PrintFiles(folderPath);

    gotoxy(fileX + 2, fileY + 2);
    cout << "Files in folder: " << folderPath << endl;
    
    int selectedOption = 0;      // Store the currently selected option
    bool optionSelected = false; // Flag to indicate if an option is selected

    while (!optionSelected)
    {
        // Print the menu options
        for (int i = 0; i < fileList.size(); i++)
        {
            gotoxy(fileX + 2, fileY + i + 4);
            if (selectedOption == i)
                        cout << "-> "<< i + 1 << "." << fileList[i];
                    else
                        cout << "   "<< i + 1 << "." << fileList[i];
        }

        char key = _getch();
        switch (key)
        {
        case 72: // Phím mũi tên lên
            if (selectedOption > 0)
                selectedOption--;
            break;
        case 80: // Phím mũi tên xuống
            if (selectedOption < fileList.size() - 1)
                selectedOption++;
            break;
        case 13: // Phím Enter
            optionSelected = true;
            break;
        default:
            break;
        }
    }

    // Xử lý tùy chọn được chọn
    if (selectedOption >= 0 && selectedOption < fileList.size())
    {
        string selectedFileName = fileList[selectedOption];

        // Xử lý tệp tin được chọn
        for(int i = 0; i < fileList.size(); i++)
        {
            if (selectedFileName == fileList[i])
            {
                string namefile = selectedFileName.substr(0, selectedFileName.length() - 4);
                file.getInfoFile(fname, namefile, fileInfo, fileAccess);        // get all information
                
                string infoname = account.getInfo().username;
                file.setUserInfo(infoname);
                system("cls");
                fileHeight = 15;

                drawBox(fileX, fileY, fileWidth, fileHeight);

                int selectedOption = 1;      // Store the currently selected option
                bool optionSelected = false; // Flag to indicate if an option is selected
                
                while (!optionSelected)
                {
                    // file.checkPermission(infoname,"view", fileAccess)
                    if ( (file.checkPermission(infoname, "view", fileAccess)) && 
                         (!file.checkPermission(infoname, "edit", fileAccess)) )
                    {

                        gotoxy(fileX + 2, fileY + 3);
                        cout << "\t\tMenu";

                        gotoxy(fileX + 2, fileY + 5);
                        if (selectedOption == 2)
                            cout << "[View file]";
                        else
                            cout << " View file ";
                    }
                    else if (file.checkPermission(infoname, "edit", fileAccess))
                    {
                        gotoxy(fileX + 2, fileY + 2);
                        cout << "\t\tMenu";
                        
                        gotoxy(fileX + 2, fileY + 4);
                        if (selectedOption == 1)
                            cout << "[Edit file]";
                        else
                            cout << " Edit file ";

                        gotoxy(fileX + 2, fileY + 5);
                        if (selectedOption == 2)
                            cout << "[View file]";
                        else
                            cout << " View file ";
                    }
                    // Print the menu options
                    gotoxy(fileX + 2, fileY + 6);
                    if (selectedOption == 3)
                        cout << "[Rename file]";
                    else
                        cout << " Rename file ";

                    gotoxy(fileX + 2, fileY + 7);
                    if (selectedOption == 4) // display with admin
                        cout << "[Delete file]";
                    else
                        cout << " Delete file ";
                    
                    gotoxy(fileX + 2, fileY + 8);
                    if (selectedOption == 5)        
                        cout << "[Move file]";
                    else
                        cout << " Move file ";

                    gotoxy(fileX + 2, fileY + 9);
                    if (selectedOption == 6)        
                        cout << "[Copy file]";
                    else
                        cout << " Copy file ";

                    gotoxy(fileX + 2, fileY + 10);
                    if (selectedOption == 7)        
                        cout << "[Add permission]";
                    else
                        cout << " Add permission ";

                    gotoxy(fileX + 2, fileY + 11);
                    if (selectedOption == 8)        
                        cout << "[Back]";
                    else
                        cout << " Back ";

                    // Get the user input
                    char key = _getch();

                    // Process the user input
                    switch (key)
                    {
                    case 72: // Up arrow key
                        if (selectedOption > 1)
                            selectedOption--;
                        break;
                    case 80: // Down arrow key
                        if (selectedOption < 8)
                            selectedOption++;
                        break;
                    case 13: // Enter key
                        optionSelected = true;
                        break;
                    default:
                        break;
                    }
                }

                // Process the selected option
                switch (selectedOption)
                {
                    case 1:
                        writeInfoFile(fname, namefile);
                        break;
                    case 2:
                        getInfoFile(fname,namefile);
                        break;
                    case 3:
                        renameFile(fname, namefile, fileInfo, fileAccess);
                        break;
                    case 4:
                        deleteFile(fname, namefile, fileInfo, fileAccess);
                        break;
                    case 5:
                        moveFile(fname, namefile, fileInfo, fileAccess);
                        break;
                    case 6:
                        copyFile(fname, namefile, fileInfo, fileAccess);
                        break;
                    case 7:
                        permissionsFile(fname, namefile, fileInfo, fileAccess);
                        break;
                    case 8:
                        previousPage.pop_back();
                        back();
                        break;    
                    default:
                        break;
                }
            }
        }
    }
}

void writeInfoFile(string dirName, string fileName)
{
    system("cls");

    cout << "Enter the author's name: ";
    cin.ignore();
    getline(cin, fileInfo.authorName);

    // Get user input for file content
    cout << "Enter file content (enter 'q' to finish):\n";
    string line;
    while (getline(cin, line) && line != "q") {
        fileInfo.content.push_back(line);
    }

    // Get user input for viewers
    cout << "Enter viewers (separated by commas): ";
    getline(cin, line);
    istringstream viewersStream(line);
    while (getline(viewersStream, line, ',')) {
        fileAccess.viewers.push_back(line);
    }

    // Get user input for editors
    cout << "Enter editors (separated by commas): ";
    getline(cin, line);
    istringstream editorsStream(line);
    while (getline(editorsStream, line, ',')) {
        fileAccess.editors.push_back(line);
    }

    // Get user input for deleters
    cout << "Enter deleters (separated by commas): ";
    getline(cin, line);
    istringstream deletersStream(line);
    while (getline(deletersStream, line, ',')) {
        fileAccess.deleters.push_back(line);
    }

    // Get user input for renamers
    cout << "Enter renamers (separated by commas): ";
    getline(cin, line);
    istringstream renamersStream(line);
    while (getline(renamersStream, line, ',')) {
        fileAccess.renamers.push_back(line);
    }

    // Call the writeInfoFile function
    file.writeInfoFile(dirName, fileName, fileInfo, fileAccess);
}

void moveFile(string currentDir, string fileName, FileInfo fileInfo, Permission fileAccess){
    system("cls");

    int moveHeight = 10;
    int moveWidth = 60;
    int moveY = (height - moveHeight) / 2;
    int moveX = (width - moveWidth) / 2;

    drawBox(moveX, moveY, moveWidth, moveHeight); 

    string targetDir;

    gotoxy(moveX + 2, moveY + 2);
    cout << "Enter the target directory: ";
    cin >> targetDir;

    // Call the moveFile function
    int result = file.moveFile(currentDir, targetDir, fileName, fileInfo, fileAccess);

    // Check the result
    if (result == 1)
    {
        gotoxy(moveX + 2, moveY + 5);
        cout << "File moved successfully." << endl;
    }
    else if (result == -2)
    {
        gotoxy(moveX + 2, moveY + 5);
        cout << "Unable to move file." << endl;
    }
    else if (result == -1)
    {
        gotoxy(moveX + 2, moveY + 5);
        cout << "You don't have this right." << endl;
    }
    int selectedOption = 1;      // Store the currently selected option
    bool optionSelected = false; // Flag to indicate if an option is selected

    while (!optionSelected)
    {
        // Print the menu options
        gotoxy(moveX + 2, moveY + 7);
        if (selectedOption == 1)
            cout << "[ Back ]";

        // Get the user input
        char key = _getch();

        // Process the user input
        if (key == 13)
            optionSelected = true;
    }

    // Process the selected option
    switch (selectedOption)
    {
    case 1:
        previousPage.pop_back();
        back();
        break;
    default:
        break;
    }
}

void renameFile(string currentDir, string fileName, FileInfo fileInfo, Permission fileAccess){
    system("cls");

    int renameHeight = 10;
    int renameWidth = 60;
    int renameY = (height - renameHeight) / 2;
    int renameX = (width - renameWidth) / 2;

    drawBox(renameX, renameY, renameWidth, renameHeight); 

    string newFileName;

    gotoxy(renameX + 2, renameY + 2);
    cout << "Enter new name: ";
    cin >> newFileName;

    // Call the renameFile method
    int result = file.renameFile(currentDir, fileName, newFileName, fileInfo, fileAccess);
    
    // Check the result
    if (result == 1)
    {
        gotoxy(renameX + 2, renameY + 5);
        cout << "File renamed successfully." << endl;
    }
    else if (result == -2)
    {
        gotoxy(renameX + 2, renameY + 5);
        cout << "Unable to rename the file." << endl;
    }
    else if (result == -1)
    {
        gotoxy(renameX + 2, renameY + 5);
        cout << "You don't have this right." << endl;
    }
    int selectedOption = 1;      // Store the currently selected option
    bool optionSelected = false; // Flag to indicate if an option is selected

    while (!optionSelected)
    {
        // Print the menu options
        gotoxy(renameX + 2, renameY + 7);
        if (selectedOption == 1)
            cout << "[ Back ]";

        // Get the user input
        char key = _getch();

        // Process the user input
        if (key == 13)
            optionSelected = true;
    }

    // Process the selected option
    switch (selectedOption)
    {
    case 1:
        previousPage.pop_back();
        back();
        break;
    default:
        break;
    }
}

void copyFile(string currentDir, string fileName, FileInfo fileInfo, Permission fileAccess){
    system("cls");

    int copyHeight = 10;
    int copyWidth = 60;
    int copyY = (height - copyHeight) / 2;
    int copyX = (width - copyWidth) / 2;

    drawBox(copyX, copyY, copyWidth, copyHeight); 

    string targetDir;

    gotoxy(copyX + 2, copyY + 2);
    cout << "Enter the target directory: ";
    cin >> targetDir;


    // Call the copyFile method
    int result = file.copyFile(currentDir, targetDir, fileName, fileInfo, fileAccess);
    
    // Check the result
    if (result == 1)
    {
        gotoxy(copyX + 2, copyY + 5);
        cout << "File copied successfully." << endl;
    }
    else if (result == -2)
    {
        gotoxy(copyX + 2, copyY + 5);
        cout << "Unable to copy file." << endl;
    }
    else if (result == -1)
    {
        gotoxy(copyX + 2, copyY + 5);
        cout << "You don't have this right." << endl;
    }
    int selectedOption = 1;      // Store the currently selected option
    bool optionSelected = false; // Flag to indicate if an option is selected

    while (!optionSelected)
    {
        // Print the menu options
        gotoxy(copyX + 2, copyY + 7);
        if (selectedOption == 1)
            cout << "[ Back ]";

        // Get the user input
        char key = _getch();

        // Process the user input
        if (key == 13)
            optionSelected = true;
    }

    // Process the selected option
    switch (selectedOption)
    {
    case 1:
        previousPage.pop_back();
        back();
        break;
    default:
        break;
    }
}

void deleteFile(string currentDir, string fileName, FileInfo fileInfo, Permission fileAccess){
    system("cls");

    int deleteHeight = 10;
    int deleteWidth = 60;
    int deleteY = (height - deleteHeight) / 2;
    int deleteX = (width - deleteWidth) / 2;

    drawBox(deleteX, deleteY, deleteWidth, deleteHeight); 

    string check;

    gotoxy(deleteX + 2, deleteY + 2);
    cout << "Are you sure you want to delete? (Y/N)";
    cin >> check;

    if (check == "Y" || check =="y") 
    {
        // Call the deleteFile method
        int result = file.deleteFile(currentDir, fileName, fileInfo, fileAccess);
        
        // Check the result
        if (result == 1)
        {
            gotoxy(deleteX + 2, deleteY + 5);
            cout << "File deleted successfully." << endl;
        }
        else if (result == -2)
        {
            gotoxy(deleteX + 2, deleteY + 5);
            cout << "Unable to delete the file." << endl;
        }
        else if (result == -1)
        {
            gotoxy(deleteX + 2, deleteY + 5);
            cout << "You don't have this right." << endl;
        }
    }
    int selectedOption = 1;      // Store the currently selected option
    bool optionSelected = false; // Flag to indicate if an option is selected

    while (!optionSelected)
    {
        // Print the menu options
        gotoxy(deleteX + 2, deleteY + 7);
        if (selectedOption == 1)
            cout << "[ Back ]";

        // Get the user input
        char key = _getch();

        // Process the user input
        if (key == 13)
            optionSelected = true;
    }

    // Process the selected option
    switch (selectedOption)
    {
    case 1:
        previousPage.pop_back();
        back();
        break;
    default:
        break;
    }
}

void permissionsFile(string currentDir, string fileName, FileInfo fileInfo, Permission fileAccess){
    system("cls");

    int permissionsHeight = 10;
    int permissionsWidth = 60;
    int permissionsY = (height - permissionsHeight) / 2;
    int permissionsX = (width - permissionsWidth) / 2;

    drawBox(permissionsX, permissionsY, permissionsWidth, permissionsHeight); 

    string targetUser;
    string permissionInput;
    vector<string> permission;

    gotoxy(permissionsX + 2, permissionsY + 2);
    cout << "Enter the target user: ";
    cin >> targetUser;
    
    cin.ignore();
    gotoxy(permissionsX + 2, permissionsY + 3);
    cout << "Enter permissions (separated by commas): ";
    getline(cin, permissionInput);

    istringstream iss(permissionInput);
    string perm;
    while (getline(iss, perm, ','))
    {
        permission.push_back(perm);
    }

    // Call the permissionsFile method
    int result = file.permissionsFile( targetUser, fileName, permission, fileInfo, fileAccess);
    
    file.writeInfoFile(currentDir, fileName, fileInfo, fileAccess);

    // Check the result
    if (result == 1)
    {
        gotoxy(permissionsX + 2, permissionsY + 5);
        cout << "Done ." << endl;
    }
    else if (result == -2)
    {
        gotoxy(permissionsX + 2, permissionsY + 5);
        cout << "Unable ." << endl;
    }
    else if (result == -1)
    {
        gotoxy(permissionsX + 2, permissionsY + 5);
        cout << "You don't have this right." << endl;
    }
    int selectedOption = 1;      // Store the currently selected option
    bool optionSelected = false; // Flag to indicate if an option is selected

    while (!optionSelected)
    {
        // Print the menu options
        gotoxy(permissionsX + 2, permissionsY + 7);
        if (selectedOption == 1)
            cout << "[ Back ]";

        // Get the user input
        char key = _getch();    

        // Process the user input
        if (key == 13)
            optionSelected = true;
    }

    // Process the selected option
    switch (selectedOption)
    {
    case 1:
        previousPage.pop_back();
        back();
        break;
    default:
        break;
    }
}

void getInfoFile(string dirName, string fileName){
    system("cls");

    file.getInfoFile(dirName, fileName, fileInfo, fileAccess);
    cout << "Author: " << fileInfo.authorName << endl;

    cout << "Viewers: ";
    for (const auto& viewer : fileAccess.viewers) {
        cout << viewer << ", ";
    }
    cout << endl;

    cout << "Editors: ";
    for (const auto& editor : fileAccess.editors) {
        cout << editor << ", ";
    }
    cout << endl;

    cout << "Deleters: ";
    for (const auto& deleter : fileAccess.deleters) {
        cout << deleter << ", ";
    }
    cout << endl;

    cout << "Renamers: ";
    for (const auto& renamer : fileAccess.renamers) {
        cout << renamer << ", ";
    }
    cout << endl;

    cout << "Content:" << endl;
    for (const auto& contentLine : fileInfo.content) {
        cout << contentLine << endl;
    }
}
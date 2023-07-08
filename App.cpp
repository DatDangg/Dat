#include <iostream>
#include <cstring>
#include <windows.h>
#include <unistd.h>
#include <conio.h> // Include the conio.h header for _getch() function
#include "Draw.h"
#include "Draw.cpp"
#include "CharacterHandling.h"
#include "CharacterHandling.cpp"
#include "Struct.h"
#include "Account.h"
#include "Account.cpp"

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

Account account;
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
    int homeWinHeight = 10;
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
            cout << "-> 4. Logout";
        else
            cout << "   4. Logout";

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

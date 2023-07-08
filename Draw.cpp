#include <iostream>
#include <cstring>
#include <windows.h>
#include <unistd.h>
#include <conio.h>
using namespace std;

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawBox(int x, int y, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                gotoxy(x + j, y + i);
                cout << "*";
            }
        }
    }
}

// Function to draw a checkbox
void drawCheckbox(bool isChecked, const string &label)
{
    if (isChecked)
        cout << "[x] " << label;
    else
        cout << "[ ] " << label;
}
#include <iostream>
using namespace std;

#ifndef DRAW_H
#define DRAW_H
void gotoxy(int x, int y);
void drawBox(int x, int y, int width, int height);
void drawCheckbox(bool isChecked, const string &label);
#endif

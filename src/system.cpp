#include<iostream>
#include <stdlib.h>
#include <windows.h>
using namespace std;

void consoleRowAndColumn(int &rows,int &columns)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void moveCursorToPosition(int x, int y)
{
    // Get the handle to the console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // Create a COORD structure to hold the position
    COORD pos;
    pos.X = x;  // Horizontal position (column)
    pos.Y = y;  // Vertical position (row)
    
    // Move the cursor to the specified position
    SetConsoleCursorPosition(hConsole, pos);
}


#include <string>
using namespace std;

#define GAME_NAME "~: WORDWISE :~"

void Header(int &rows, int &columns, string headding)
{

    cout << Color_Magenta;
    for (int j = 0; j <= 2; j++)
    {
        for (int i = 0; i < columns; i++)
        {
            if (i == 0 || i == columns - 1)
            {
                if (j == 0 || j == 2)
                {
                    cout << "+";
                }
                else
                {
                    cout << "|";
                }
            }
            else
            {
                if (j == 0 || j == 2)
                {
                    cout << "-";
                }
                else
                {
                    if (i == (columns - headding.length()) / 2)
                    {
                        cout << Color_Yellow << headding << Color_Magenta;
                        i += headding.length() - 1;
                    }
                    else
                    {
                        cout << " ";
                    }
                }
            }
        }
    }
    cout << Color_Reset;
}

void Footer(int &rows, int &columns, string Text)
{
    cout << Color_Magenta;
    for (int j = 0; j <= 2; j++)
    {
        for (int i = 0; i < columns; i++)
        {
            if (i == 0 || i == columns - 1)
            {
                if (j == 0 || j == 2)
                {
                    cout << "+";
                }
                else
                {
                    cout << "|";
                }
            }
            else
            {
                if (j == 0 || j == 2)
                {
                    cout << "-";
                }
                else
                {
                    if (i == (columns - Text.length()) / 2)
                    {
                        cout << Color_Yellow << Text << Color_Magenta;
                        i += Text.length() - 1;
                    }
                    else
                    {
                        cout << " ";
                    }
                }
            }
        }
    }
    cout << Color_Reset;
}

void ThemeFormat(int rows, int columns)
{
    int cardColumn = 95;
    system("cls");
    Header(rows, columns, GAME_NAME);
    moveCursorToPosition(0, rows - 3);
    Footer(rows, columns, "Use Arrow <Up> and <Down> Key For Navigation, Use <Enter Key> For Select or Remove Aleart Box.");
    if (columns > 125 && rows > 35)
    {
        BoldTitle(columns, cardColumn, 5);
    }
}

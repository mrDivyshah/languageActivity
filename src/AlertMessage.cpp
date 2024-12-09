using namespace std;

void AlertMessage(int rows, int columns, string type, string msg)
{
    int boxWidth = msg.length() + 8; // Adding padding to message box
    int boxHeight = 3, key;          // Top border, message row, bottom border
    cout << Color_Red;
    // Draw the top border
    moveCursorToPosition(columns - (boxWidth / 2), rows);
    cout << "* " << string(boxWidth - 4, '-') << " *";

    // Draw the message line with side borders
    moveCursorToPosition(columns - (boxWidth / 2), rows + 1);
    cout << "|   " << msg << "   |";

    // Draw the bottom border
    moveCursorToPosition(columns - (boxWidth / 2), rows + 2);
    cout << "* " << string(boxWidth - 4, '-') << " *";
    cout << Color_Reset;
    while (true)
    {
        key = _getch();
        if (key == 13)
        {
            clearLines(rows, rows + 3);
            break;
        }
    }
}
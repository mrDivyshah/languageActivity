// ########################################################
// ##                       FAQ                          ##
// ##  1.  How To Run This Game ?                        ##
// ##  Ans: g++ main.cpp -o main -std=c++11 && main      ##
// ##                                                    ##

#include <stdlib.h>
#include <windows.h>
#include <string>
#include <conio.h>
#include <random>
#include "src/headding.cpp" // nameSpace, windows.h, iostream, system.cpp
#include "src/databse_function/connection.cpp"
#include "src/databse_function/WordScrambleDatabase.cpp"
#include "src/game/WordScramble.cpp"
#include "src/Admin/main.cpp"
struct Games
{
    int index;
    string name;
    string functionName;
};
struct SelectionValue
{
    int selected;
    bool enterPressed;
};

vector<Games> gameList = {
    {1, "Sentence Scramble", "Hangman"},
    // {2, "Puzal Alfa", "Puzal"},
    // {3, "Verb and Noun", "VerbNoun"},
    {2, "Word Scramble", "wordScramble"}};

int G_columns, G_rows;
string GAME_NAME = "~: WORDWISE :~";
void Header(int &rows, int &columns, string headding);
void Footer(int &rows, int &columns, string Text);
void ThemeFormate(int rows, int columns);
User LoginUser(int columns, int rows);
void printMenu(int selected, int rows, int columns);
int menuSelectionPrint(int rows, int columns);
void clearLines(int startRow, int endRow);
void AlertMessage(int rows, int coumns, string type, string msg);
SelectionValue Selection(int selected, int total);
void ScoreBoard();
void time();
void LoginUser();
void Home(int rows, int columns, User userData);
void wordScramble(User userData, int rows, int columns);
void printLine(char start, char mid, char end, int widths[], int numCols, char fill);
void printCenteredText(const char *text, int width);
void ScoreBoard(char gameName[50], int level, int totalScore, int currentPlayScore, int columns, int rows);
void sen(User userData, int rows, int columns);

int main()
{
    int columns, rows;
    User userData = {-1, " ", " "};
    int cardColumn = 60, age;

    int index = 0;
    do
    {
        consoleRowAndColumn(rows, columns);
        if (columns < 120 && rows < 30)
        {
            system("cls");
            cout << "Please Open Maximized terminal And Press Enter" << endl;
            cout << "Column Size is  : " << columns << "  We need minimum: 120" << endl;
            cout << "Row Size is  : " << rows << "  We need minimum : 30" << endl;
            if (index != 0)
            {
                cout << "\n\nAttempt : " << index;
            }
            _getch();
        }
        else
        {
            break;
        }
        index++;
    } while (true);
    G_columns = columns;
    G_rows = rows;
    ThemeFormate(rows, columns);
    moveCursorToPosition((columns - 65) / 2, (columns > 125 && rows > 35) ? 15 : 5);
    cout << Color_Blue;
    cout << "Hello! Get ready to play and improve your language skills!";
    cout << Color_Reset;
    userData = LoginUser(((columns - 40) / 2), (columns > 125 && rows > 35) ? 18 : 8);
    if (userData.id == -2)
    {
        system("cls");
        return 0;
    }
    // userData.id = 1;
    // userData.joiningDate = "10/21/2022";
    // userData.name = "divyshah";
    // userData.password = "12131415";
    Home(rows, columns, userData);

    // cout << "columns " << columns << "\t Rows " << rows;

    // moveCursorToPosition(0, rows);

    _getch();
}

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

void time()
{
    time_t now = time(0);

    // Convert time_t to tm structure for local timezone
    tm *local_time = localtime(&now);
    cout << local_time->tm_hour;
    // Display the date and time in a formatted way
    cout << "Current Date and Time: ";
    cout << 1900 + local_time->tm_year << "-" // Year
         << 1 + local_time->tm_mon << "-"     // Month (0-11, so add 1)
         << local_time->tm_mday << " "        // Day of the month
         << local_time->tm_hour << ":"        // Hours
         << local_time->tm_min << ":"         // Minutes
         << local_time->tm_sec                // Seconds
         << endl;
}

User LoginUser(int columns, int rows)
{
    string userName, password, Cpassword;
    User userData = {-1, " ", " "};
    while (1)
    {
        int selected = menuSelectionPrint(rows, columns + 5);
        if (selected == getUserCount() + 1)
        {

            while (1)
            {
                clearLines(rows, rows + getUserCount() + 10);
                moveCursorToPosition(columns - 5, rows);
                cout << "Enter Your User Name : ";
                moveCursorToPosition(columns + 18, rows);
                getline(cin, userName);
                moveCursorToPosition(columns, rows + 2);
                cout << "Enter Password : ";
                // moveCursorToPosition(columns + 19, rows);
                getline(cin, password);
                userData = searchUser(userName);
                if (userData.id != -1 && userData.password == password)
                {
                    return userData;
                }
                else if (password.length() <= 6)
                {
                    moveCursorToPosition(columns - 20, rows + 6);
                    cout << Color_Red;
                    cout << "Your Password To Short Minimum length of Password is 6 Please Try Again....";
                    cout << Color_Reset;
                    _getch();
                    clearLines(rows + 2, rows + 7);
                }
                else if (userData.id != -1)
                {
                    AlertMessage(rows + 9, columns + 20, "Error", "Invalid Password");
                    clearLines(rows + 2, rows + 7);
                }
                else if (userName == "admin" && password == "admin123")
                {
                    system("cls");
                    adminPanel();
                    ThemeFormate(G_rows, G_columns);
                    break;
                }
                else
                {
                    AlertMessage(rows + 9, columns + 20, "Error", "Invalid Credentials");
                    clearLines(rows + 2, rows + 7);
                }
            }
            clearLines(rows + 2, rows + 7);
        }
        else if (selected == getUserCount() + 2)
        {
            clearLines(rows, rows + getUserCount() + 10);
            moveCursorToPosition(columns, rows);
            cout << "Enter Your Name : ";
            moveCursorToPosition(columns + 18, rows);
            getline(cin, userName);
            while (1)
            {
                moveCursorToPosition(columns, rows + 2);
                cout << "Enter Password : ";
                getline(cin, password);
                moveCursorToPosition(columns, rows + 4);
                cout << "Conform Password : ";
                getline(cin, Cpassword);
                moveCursorToPosition(columns + 19, rows);
                if (password != Cpassword)
                {
                    moveCursorToPosition(columns - 20, rows + 6);
                    cout << Color_Red;
                    cout << "Your Password and Conform Password Are Not Match Please Try Again....";
                    cout << Color_Reset;
                    _getch();
                    clearLines(rows + 2, rows + 7);
                }
                else if (password.length() <= 6)
                {
                    moveCursorToPosition(columns - 20, rows + 6);
                    cout << Color_Red;
                    cout << "Your Password To Short Minimum length of Password is 6 Please Try Again....";
                    cout << Color_Reset;
                    _getch();
                    clearLines(rows + 2, rows + 7);
                }
                else
                {
                    break;
                }
            }
            clearLines(rows + 2, rows + 7);

            if (userName.length() == 0)
            {
                AlertMessage(rows + 9, columns + 20, "Error", "Name is Require");
            }
            else if (userName.length() <= 2)
            {
                AlertMessage(rows + 9, columns + 20, "Error", "Require Name in minimum 3 latter");
            }
            else
            {
                User searchData = searchUser(userName);
                if (searchData.id == -1)
                {
                    cout << Color_Green;
                    moveCursorToPosition(columns - 30, rows + 4);
                    cout << "+----------------------------------------------------------------------------------------------------+";
                    moveCursorToPosition(columns - 30, rows + 5);
                    cout << "|";
                    cout << "     Hats off, " << Color_Cyan + userName + Color_Green << "! You've entered the Wordwise universe. Time to immerse yourself in ";
                    moveCursorToPosition(columns + 71, rows + 5);
                    cout << "|";
                    moveCursorToPosition(columns - 30, rows + 6);
                    cout << "|           language learning like never before! You're about to embark on an amazing                |";
                    moveCursorToPosition(columns - 30, rows + 7);
                    cout << "|                      journey filled with words, knowledge, and fun!                                |";
                    moveCursorToPosition(columns - 30, rows + 8);
                    cout << "+----------------------------------------------------------------------------------------------------+";
                    cout << Color_Reset;
                    moveCursorToPosition(columns - 13, rows + 10);
                    cout << "Ready for more? Tap < Enter Key > to keep moving forward....";
                    userData = addUser(userName, password);
                    addWordScrambleData(userData.id, userData.name, 1, 0, 10);
                    _getch();
                    return userData;
                }
                else
                {
                    AlertMessage(rows + 8, columns + 20, "Error", "User Already Available");
                }
            }
        }
        else if (selected == getUserCount() + 3)
        {
            userData = {-2, " ", " "};
            return userData;
        }
        else
        {
            userData = userDataUsingUserIndex(selected);
            while (1)
            {
                clearLines(rows, rows + getUserCount() + 10);
                moveCursorToPosition(columns, rows);
                cout << "Enter Your Password : ";
                moveCursorToPosition(columns + 23, rows);
                getline(cin, password);
                if (password == userData.password)
                {

                    return userData;
                }
                else
                {
                    moveCursorToPosition(columns, rows + 2);
                    cout << "Please Try Again Press Enter";
                    cout << Color_Background_Red;
                    moveCursorToPosition(columns - 5, G_rows - 6);
                    cout << " If You want to exit this process then press 1 ";
                    int key = _getch();
                    cout << Color_Reset;
                    if (key == 49)
                    {
                        system("cls");
                        exit(0);
                    }
                    clearLines(G_rows - 7, G_rows - 4);
                }
            }
        }
        clearLines(rows, rows + getUserCount() + 7);
    }
    return userData;
}

void printMenu(int selected, int rows, int columns)
{
    int index = 0;
    for (string user : AllAvailableUsers())
    {
        moveCursorToPosition(columns + 9 - (user.length() / 2), rows + index);
        cout << (selected == index ? Color_Cyan + "-> " + Color_Underline_On : "   ") << user << Color_Reset + Color_Underline_Off << "\n";
        index++;
        if (index == 5)
        {
            break;
        }
    }
    moveCursorToPosition(columns - 22, rows + index + 1);
    cout << (selected == index ? Color_Yellow : "") << "-------------------------------------------------------------------------";
    moveCursorToPosition(columns + 6, rows + index + 2);
    cout << (selected == index ? Color_Yellow + "-> " : "   ") << "Login Me" << Color_Reset << "\n";
    moveCursorToPosition(columns - 22, rows + index + 3);
    cout << (selected == index + 1 ? Color_Green : "") << (selected == index ? Color_Yellow : "") << "-------------------------------------------------------------------------" << Color_Reset;
    moveCursorToPosition(columns + 6, rows + index + 4);
    cout << (selected == index + 1 ? Color_Green + "-> " : "   ") << "New User" << Color_Reset << "\n";
    moveCursorToPosition(columns - 22, rows + index + 5);
    cout << (selected == index + 2 ? Color_Red : "") << (selected == index + 1 ? Color_Green : "") << "-------------------------------------------------------------------------" << Color_Reset;
    moveCursorToPosition(columns + 8, rows + index + 6);
    cout << (selected == index + 2 ? Color_Red + "-> " : "   ") << "EXIT" << Color_Reset;
    moveCursorToPosition(columns - 22, rows + index + 7);
    cout << (selected == index + 2 ? Color_Red : "") << "-------------------------------------------------------------------------\n"
         << Color_Reset;
}

int menuSelectionPrint(int rows, int columns)
{
    int selected = 0;
    printMenu(selected, rows, columns);
    while (true)
    {
        SelectionValue option = Selection(selected, getUserCount() + 2);
        if (option.enterPressed)
        {
            break;
        }
        selected = option.selected;
        printMenu(option.selected, rows, columns);
    }
    return selected;
}

void clearLines(int startRow, int endRow)
{
    for (int i = startRow; i <= endRow; ++i)
    {
        cout << "\033[" << i << ";" << 1 << "H";
        cout << "\033[K";
    }
}

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

void ThemeFormate(int rows, int columns)
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

void UserHeader(string content, int column, int minusLength, bool isFooterAvail, string leftContent, string rightContent)
{
    int contentLength = content.length() - minusLength;
    int padding = 12;
    int boxWidth = contentLength + padding;
    int boxHeight = 7;

    int startColumn = (column - boxWidth) / 2;
    int startRow = (G_columns > 125 && G_rows > 35) ? 13 : 4;
    clearLines(startRow, 7);

    moveCursorToPosition(startColumn, startRow);
    cout << Color_Bright_Green;
    for (int i = 0; i < boxWidth; i++)
        cout << ":";
    cout << Color_Reset;

    moveCursorToPosition(startColumn, startRow + 1);
    cout << "|";
    cout << Color_Bright_Black;
    for (int i = 0; i < boxWidth - 2; ++i)
        cout << "~";
    cout << Color_Reset;
    cout << "|";

    moveCursorToPosition(startColumn, startRow + 2);
    cout << "|     " << Color_Yellow + content + Color_Reset << "     |";

    moveCursorToPosition(startColumn, startRow + 3);
    cout << "|";
    cout << Color_Bright_Black;
    for (int i = 0; i < boxWidth - 2; ++i)
        cout << "~";
    cout << Color_Reset;
    cout << "|";

    cout << Color_Bright_Green;
    moveCursorToPosition(startColumn, startRow + 4);
    for (int i = 0; i < boxWidth; ++i)
        cout << ":";
    cout << Color_Reset;
    if (isFooterAvail)
    {
        moveCursorToPosition(startColumn + 1, startRow + 6);
        cout << leftContent;
        moveCursorToPosition(startColumn + boxWidth - rightContent.length() - 1, startRow + 6);
        cout << rightContent;
    }
}

int levelSelection(int rows, int columns, int numLevels, int restrictedFromLevel)
{
    int selected = 0;        // Start with the first level selected
    const int boxWidth = 42; // Width of the selection box
    int row = (columns > 125 && rows > 35) ? 20 : 10;
    while (true)
    {
        // Clear screen (this is a placeholder; replace with your clear function if available)
        clearLines(19, 24 + numLevels * 2);

        // Draw top border of the selection box
        moveCursorToPosition((columns - boxWidth) / 2, row);
        cout << "+";
        for (int i = 0; i < boxWidth - 2; i++)
            cout << "-";
        cout << "+";

        // Draw the title row
        moveCursorToPosition((columns - boxWidth) / 2, row + 1);
        cout << "|";
        moveCursorToPosition((columns - 12) / 2, row + 1);
        cout << "Select Level";
        moveCursorToPosition((columns + boxWidth - 2) / 2, row + 1);
        cout << "|";

        // Draw separator line after title
        moveCursorToPosition((columns - boxWidth) / 2, row + 2);
        cout << "+";
        for (int i = 0; i < boxWidth - 2; i++)
            cout << "-";
        cout << "+";

        // Draw levels dynamically
        int i;
        for (i = 0; i < numLevels; i++)
        {
            // Draw the level rows
            moveCursorToPosition((columns - boxWidth) / 2, row + 3 + i); // Adjusted row for spacing
            cout << "|";                                                 // Start of the box for this level

            // If the level is restricted, display in black, else in green for selected
            if (i >= restrictedFromLevel) // Restricted level starts from level 3
            {
                cout << "    ";
                cout << Color_Bright_Black << "  Level " << (i + 1) << Color_Reset; // Disabled levels are shown in black
                cout << "   ";                                                      // Padding for alignment
            }
            else // Non-restricted levels
            {
                if (selected == i) // Highlight selected level
                {
                    cout << "   >> "; // Padding before the selection
                    cout << Color_Green << "Level " << (i + 1) << Color_Reset;
                }
                else // Non-selected levels
                {
                    cout << "      Level " << (i + 1) << "  "; // Add spaces for proper alignment
                }
            }

            // End of the box for this level
            moveCursorToPosition((columns + boxWidth - 2) / 2, row + 3 + i);
            cout << "|";
        }

        // Draw bottom border
        moveCursorToPosition((columns - boxWidth) / 2, row + 3 + i);
        cout << "+";
        for (int j = 0; j < boxWidth - 2; j++)
            cout << "-";
        cout << "+";

        moveCursorToPosition((columns - 33) / 2, row + 4 + i + 1); // Centered footer
        cout << Color_Blue + "Press Enter to select the level" + Color_Reset;

        // Handle user input (Arrow keys and Enter)
        int ch = _getch();
        if (ch == 224) // Arrow keys
        {
            ch = _getch(); // Get the specific arrow key code
            if (ch == 72)  // Up arrow key
            {
                // Move up, but skip restricted levels
                do
                {
                    selected = (selected - 1 + numLevels) % numLevels;
                } while (selected >= restrictedFromLevel); // Skip restricted levels
            }
            else if (ch == 80) // Down arrow key
            {
                // Move down, but skip restricted levels
                do
                {
                    selected = (selected + 1) % numLevels;
                } while (selected >= restrictedFromLevel); // Skip restricted levels
            }
        }
        else if (ch == 13) // Enter key
        {
            // If the user selects a restricted level, do nothing
            if (selected >= restrictedFromLevel)
            {
                continue; // Skip restricted levels
            }
            // Return the selected level index (1-based index)
            return selected + 1;
        }
    }
}

int HomerMenu(int rows, int columns, int selected)
{
    int box_column = 42;
    int row = (G_columns > 125 && G_rows > 35) ? 20 : 11;
    moveCursorToPosition((columns - 43) / 2, row);
    cout << "+";
    for (int i = 0; i <= box_column - 2; i++)
        cout << "-";
    cout << "+";
    // cout << "+-----------------------------------------+";
    moveCursorToPosition((columns - 43) / 2, row + 1);
    cout << "|";
    moveCursorToPosition((columns - 39) / 2, row + 1);
    cout << "[-] Select Game";
    moveCursorToPosition((columns + 41) / 2, row + 1);
    cout << "|";
    moveCursorToPosition((columns - 43) / 2, row + 2);
    cout << "+-----------------------------------------+";
    // Games Here Show
    int count = 0;
    for (const auto &DSgame : gameList)
    {
        moveCursorToPosition((columns - 43) / 2, row + 3 + count);
        cout << "|";
        moveCursorToPosition((columns - 34) / 2, row + 3 + count);
        cout << (selected == count ? Color_Green + ">> " : Color_Bright_Black + "   ") << DSgame.name << Color_Reset;
        moveCursorToPosition((columns + 41) / 2, row + 3 + count);
        cout << "|";
        count++;
    }
    moveCursorToPosition((columns - 43) / 2, row + 3 + count);
    cout << "+-----------------------------------------+";
    moveCursorToPosition((columns - 43) / 2, row + 3 + count + 1);
    cout << "|";
    moveCursorToPosition((columns - 20) / 2, row + 3 + count + 1);
    cout << (selected == count ? Color_Yellow + ">> " : "   ") << "Manage Account" << Color_Reset;
    moveCursorToPosition((columns + 41) / 2, row + 3 + count + 1);
    cout << "|";
    moveCursorToPosition((columns - 43) / 2, row + 4 + count + 1);
    cout << "+-----------------------------------------+";
    moveCursorToPosition((columns - 43) / 2, row + 5 + count + 1);
    cout << "|";
    moveCursorToPosition((columns - 10) / 2, row + 5 + count + 1);
    cout << (selected == count + 1 ? Color_Red + ">> " : "   ") << "Exit" << Color_Reset;
    moveCursorToPosition((columns + 41) / 2, row + 5 + count + 1);
    cout << "|";
    moveCursorToPosition((columns - 43) / 2, row + 6 + count + 1);
    cout << "+-----------------------------------------+";
    return 0;
}

void Home(int rows, int columns, User userData)
{
    ThemeFormate(G_rows, G_columns);
    int gameListSize = gameList.size();
    struct HomeMenu
    {
        int index;
        string MenuItem;
    };
    int selected = 0;
    HomerMenu(rows, columns, selected);
    while (true)
    {
        UserHeader("User Name : " + userData.name + " [" + to_string(userData.id) + "]      Joined On: " + userData.joiningDate, columns, 0, false, "", "");
        SelectionValue option = Selection(selected, gameListSize);
        if (option.enterPressed)
        {
            if (option.selected == gameListSize)
            {
                cout << "Selected Menu";
            }
            else if (option.selected == gameListSize + 1)
            {
                system("cls");
                return;
            }
            else
            {
                for (const auto &game : gameList)
                {
                    if (option.selected == game.index - 1)
                    {
                        if (game.index == 1)
                        {
                            sen(userData, rows, columns);
                        }
                        else if (game.index == 2)
                        {
                            wordScramble(userData, rows, columns);
                        }
                    }
                    clearLines(13, rows - 10);
                }
            }
        }

        selected = option.selected;
        HomerMenu(rows, columns, option.selected);
    }
}

SelectionValue Selection(int selected, int total)
{
    int key = _getch();
    bool enterPressed = false;
    if (key == 72 && selected > 0) // Up arrow
    {
        selected--;
    }
    else if (key == 80 && selected <= total) // Down arrow
    {
        selected++;
    }
    else if (key == 13) // Enter key (ASCII 13)
    {
        enterPressed = true;
    }
    return {selected, enterPressed};
}

void center_Text(string str, int row)
{
    moveCursorToPosition((G_columns - str.length()) / 2, row);
    cout << str;
}

string shuffleLetter(string word)
{
    int length = word.length();
    string tempWord = word;
    for (int i = 0; i < length; i++)
    {
        int j = rand() % length;
        char temp = word[i];
        word[i] = word[j];
        word[j] = temp;
    }
    if (tempWord == word)
    {
        return shuffleLetter(word);
    }
    else
    {
        return word;
    }
}

string toLower(string &str)
{
    std::string fstr = str; // Copy the input string to fstr
    for (int i = 0; i < fstr.size(); i++)
    {
        fstr[i] = tolower(fstr[i]); // Convert each character to lowercase
    }
    return fstr; // Return the modified string
}

int hintButtons(int row)
{
    const int LEFT_ARROW = 75;
    const int RIGHT_ARROW = 77;
    const int ENTER_KEY = 13;

    // Calculate button positions based on G_columns
    int firstColumn = G_columns / 8;            // Updated for 4 buttons
    int secondColumn = 3 * (G_columns / 8) - 6; // Adjusted column spacing
    int thirdColumn = 5 * (G_columns / 8) - 9;
    int fourthColumn = 7 * (G_columns / 8) - 12; // fourth button

    int currentSelection = 0; // 0 -> Hint, 1 -> Retry, 2 -> Exit, 3 -> Help

    while (true)
    {
        // Draw the buttons, highlighting the selected one

        // Button 1: Hint
        moveCursorToPosition(firstColumn, row);
        if (currentSelection == 0)
        {
            cout << Color_Yellow << "***********" << Color_Reset;
        }
        else
        {
            cout << "-----------";
        }
        moveCursorToPosition(firstColumn, row + 1);
        cout << "|   Hint  |";
        moveCursorToPosition(firstColumn, row + 2);
        if (currentSelection == 0)
        {
            cout << Color_Yellow << "***********" << Color_Reset;
        }
        else
        {
            cout << "-----------";
        }

        // Button 2: Retry
        moveCursorToPosition(secondColumn, row);
        if (currentSelection == 1)
        {
            cout << Color_Blue << "***********" << Color_Reset;
        }
        else
        {
            cout << "-----------";
        }
        moveCursorToPosition(secondColumn, row + 1);
        cout << "|  Retry  |";
        moveCursorToPosition(secondColumn, row + 2);
        if (currentSelection == 1)
        {
            cout << Color_Blue << "***********" << Color_Reset;
        }
        else
        {
            cout << "-----------";
        }

        // Button 3: Exit
        moveCursorToPosition(thirdColumn, row);
        if (currentSelection == 2)
        {
            cout << Color_Red << "***********" << Color_Reset;
        }
        else
        {
            cout << "-----------";
        }
        moveCursorToPosition(thirdColumn, row + 1);
        cout << "|   Exit  |";
        moveCursorToPosition(thirdColumn, row + 2);
        if (currentSelection == 2)
        {
            cout << Color_Red << "***********" << Color_Reset;
        }
        else
        {
            cout << "-----------";
        }

        // Button 4: Help (New Button)
        moveCursorToPosition(fourthColumn, row);
        if (currentSelection == 3)
        {
            cout << Color_Cyan << "***********" << Color_Reset;
        }
        else
        {
            cout << "-----------";
        }
        moveCursorToPosition(fourthColumn, row + 1);
        cout << "|   Back  |";
        moveCursorToPosition(fourthColumn, row + 2);
        if (currentSelection == 3)
        {
            cout << Color_Cyan << "***********" << Color_Reset;
        }
        else
        {
            cout << "-----------";
        }

        // Footer instructions
        string footer = "Use Side Arrow Keys to Navigate Buttons";
        moveCursorToPosition((G_columns - footer.length()) / 2, row + 4);
        cout << Color_Green << footer << Color_Reset;

        // Wait for user input
        int key = _getch();

        // Arrow key handling
        if (key == 224)
        {
            key = _getch(); // Get the actual key code
            if (key == LEFT_ARROW)
            {
                currentSelection = (currentSelection + 3) % 4; // Move left, wrap around
            }
            else if (key == RIGHT_ARROW)
            {
                currentSelection = (currentSelection + 1) % 4; // Move right, wrap around
            }
        }

        // Enter key to confirm selection
        if (key == ENTER_KEY)
        {
            return currentSelection; // Return the selected button
        }
    }
}

string stageArrayToString(int stage[])
{

    stringstream ss;
    for (int i = 0; i < 3; ++i)
    {
        if (stage[i] == -1)
        {
            return ss.str();
        }
        ss << stage[i];
        if (i < 2)
        {
            ss << " ";
        }
    }
    return ss.str();
}

void wordScramble(User userData, int rows, int columns)
{
    map<int, vector<pair<string, vector<string>>>> words = vocabulary;
    srand(static_cast<unsigned int>(time(0)));
    int mrows = rows;
    while (true)
    {
        rows = mrows;
        int stage[3] = {-1, -1, -1};
        int sele = -1;
        system("cls");
        ThemeFormate(rows, columns);
        WordScrambleData WordScrambleUserData = getSingleUserWordScrambleData(userData.id, userData.name);
        int level = levelSelection(rows, columns, 5, WordScrambleUserData.level);
        system("cls");
        ThemeFormate(rows, columns);
        auto entry = words[level];
        int totalWords = words[level].size();
        int randomeIndex = rand() % totalWords;
        int itretion = 0;
        int hintCount = 0;
        int stg = 0;
        rows = rows / 2;
        while (sele <= 3)
        {
            for (const auto &entry : words[level])
            {
                if (itretion == randomeIndex)
                {
                    string MyWord = entry.first;
                    string wordIntr = shuffleLetter(MyWord);
                    while (1)
                    {
                        WordScrambleData WordScrambleUserData = getSingleUserWordScrambleData(userData.id, userData.name);
                        clearLines(rows - 10, rows + 11);
                        UserHeader("Level: " + to_string(level) + Color_Bright_Red + "   :::  Word Scramble :::  " + Color_Yellow + " Score : [" + to_string(WordScrambleUserData.score) + "] ", columns, Color_Bright_Red.length() + Color_Yellow.length(), true, "Stage : " + stageArrayToString(stage), "Coin : " + to_string(WordScrambleUserData.coin));
                        moveCursorToPosition((columns - (wordIntr.length() * 2) - wordIntr.length()) / 2, rows - 4);
                        for (const auto &latter : wordIntr)
                        {
                            cout << "  " << static_cast<char>(toupper(latter));
                        }
                        string trueWord = entry.first;
                        string userWord;
                        if (sele == 0)
                        {
                            updateWordScrambleData(userData.id, userData.name, WordScrambleUserData.level, WordScrambleUserData.score, WordScrambleUserData.coin - 1);
                            string hint = entry.second[hintCount++ % 5];
                            moveCursorToPosition((columns - hint.length() - 10) / 2, rows - 2);
                            cout << Color_Yellow << "Hint : " << Color_Blue << "'" << hint << "'" << Color_Reset;
                            sele = -1;
                        }
                        moveCursorToPosition((columns - (40)) / 2, rows);
                        cout << "Type Your Word Here : ";
                        getline(cin, userWord);
                        if (toLower(userWord) == trueWord)
                        {
                            moveCursorToPosition((columns - 22) / 2, rows + 2);
                            cout << Color_Bright_Green << "+---------------------+";
                            moveCursorToPosition((columns - 22) / 2, rows + 3);
                            cout << "|  Great You Are Win  |";
                            moveCursorToPosition((columns - 22) / 2, rows + 4);
                            cout << "+---------------------+" << Color_Reset;
                            moveCursorToPosition(columns, rows - 22);
                            if (hintCount != 0)
                            {
                                stage[stg++] = 5;
                            }
                            else
                            {
                                stage[stg++] = 10;
                            }
                            //  if (stg >= 2)
                            // {
                            // //    updateWordScrambleData(userData.id, userData.name, WordScrambleUserData.level+1, WordScrambleUserData.score+10, WordScrambleUserData.coin+1);
                            // // }else{
                            break;
                        }
                        else
                        {
                            moveCursorToPosition((columns - 35) / 2, rows + 2);
                            cout << Color_Bright_Red << "+--------------------------------+";
                            moveCursorToPosition((columns - 35) / 2, rows + 3);
                            cout << "|  Wrong Word! Please Try Again  |";
                            moveCursorToPosition((columns - 35) / 2, rows + 4);
                            cout << "+--------------------------------+" << Color_Reset;
                            sele = hintButtons(rows + 6);
                            if (sele == 1)
                            {
                                continue;
                            }
                            else if (sele == 2)
                            {
                                system("cls");
                                return;
                            }
                            else if (sele == 3)
                            {
                                break;
                            }
                        }
                    }
                    if (stg >= 3 || sele == 3)
                    {
                        break;
                    }
                }
                else
                {
                    itretion++;
                }
            }
            if (stg >= 3)
            {
                UserHeader("Level: " + to_string(level) + Color_Bright_Red + "   :::  Word Scramble :::  " + Color_Yellow + " Score : [" + to_string(WordScrambleUserData.score) + "] ", columns, Color_Bright_Red.length() + Color_Yellow.length(), true, "Stage : " + stageArrayToString(stage), "Coin : " + to_string(WordScrambleUserData.coin));
                char gameName[50] = "Word Scramble";
                int currentPlayScore = 0;
                for (int i = 0; i < 3; ++i)
                {
                    currentPlayScore += stage[i];
                }
                updateWordScrambleData(userData.id, userData.name, (level == WordScrambleUserData.level) ? WordScrambleUserData.level + 1 : WordScrambleUserData.level, WordScrambleUserData.score + currentPlayScore, (currentPlayScore == 30) ? WordScrambleUserData.coin + 1 : WordScrambleUserData.coin);
                ScoreBoard(gameName, level, WordScrambleUserData.score, currentPlayScore, columns, rows);
                level++;
                _getch();
                break;
            }
            else
            {
                itretion = 0;
            }
            if (sele == 3)
            {
                break;
            }
        }
    }

    //    cout << "Original: " << word << " | Shuffled: " << wordIntr << endl;
}

void printLine(char start, char mid, char end, int widths[], int numCols, char fill)
{
    printf("%c", start);
    for (int i = 0; i < numCols; i++)
    {
        for (int j = 0; j < widths[i] + 2; j++)
            printf("%c", fill);
        printf("%c", (i == numCols - 1) ? end : mid);
    }
    printf("\n");
}

void printCenteredText(const char *text, int width)
{
    int textLen = strlen(text);
    int padding = (width - textLen) / 2;
    int extraSpace = (width - textLen) % 2;

    printf("%*s%s%*s", padding + 1, "", text, padding + extraSpace + 1, "");
}

void ScoreBoard(char gameName[50], int level, int totalScore, int currentPlayScore, int screenWidth, int screenHeight)
{
    const char *headers[] = {"Game Name", "Level", "Score", "Add Score", "Total Score"};
    const int numCols = sizeof(headers) / sizeof(headers[0]);

    // Calculate the overall score
    int overallScore = totalScore + currentPlayScore;

    // Calculate the maximum width of each column dynamically
    int widths[numCols];
    widths[0] = strlen(headers[0]) > strlen(gameName) ? strlen(headers[0]) : strlen(gameName);
    widths[1] = strlen(headers[1]) > snprintf(NULL, 0, "%d", level) ? strlen(headers[1]) : snprintf(NULL, 0, "%d", level);
    widths[2] = strlen(headers[2]) > snprintf(NULL, 0, "%d", totalScore) ? strlen(headers[2]) : snprintf(NULL, 0, "%d", totalScore);
    widths[3] = strlen(headers[3]) > snprintf(NULL, 0, "%d", currentPlayScore) ? strlen(headers[3]) : snprintf(NULL, 0, "%d", currentPlayScore);
    widths[4] = strlen(headers[4]) > snprintf(NULL, 0, "%d", overallScore) ? strlen(headers[4]) : snprintf(NULL, 0, "%d", overallScore);

    // Calculate the total width of the scoreboard
    int totalWidth = 3 + (numCols - 1); // 3 for borders, and 1 space between columns
    for (int i = 0; i < numCols; i++)
    {
        totalWidth += widths[i] + 2; // Add column width with padding
    }

    // Create a dynamic title that fits the totalWidth of the scoreboard
    std::string title = " SCORE BOX ";
    int titlePadding = (totalWidth - title.length()) / 2;
    std::string dynamicTitle = std::string(titlePadding, '~') + title + std::string(titlePadding, '~');

    // If the title length is still less than totalWidth due to rounding, add one more '~' at the end
    if (dynamicTitle.length() < totalWidth)
    {
        dynamicTitle += "~";
    }

    // Calculate starting position to center the scoreboard
    int startColumn = (screenWidth - totalWidth) / 2;
    int startRow = screenHeight + 8; // Assuming 8 rows for the scoreboard height
    clearLines(startRow, startRow + 8);
    // Clear the area and move cursor to starting position
    cout << Color_Bright_White;
    moveCursorToPosition(startColumn, startRow - 2);
    cout << dynamicTitle;
    cout << Color_Bright_Black;
    moveCursorToPosition(startColumn, startRow);

    // Print the top border
    printLine('+', '+', '+', widths, numCols, '=');

    moveCursorToPosition(startColumn, startRow + 1);
    // Print header row with centered text
    printf("|");
    for (int i = 0; i < numCols; i++)
    {
        cout << Color_Bright_Magenta;
        printCenteredText(headers[i], widths[i]);
        cout << Color_Bright_Black;
        printf("|");
    }
    printf("\n");

    // Print separator line under header
    moveCursorToPosition(startColumn, startRow + 2);
    printLine('+', '+', '+', widths, numCols, '-');

    // Print an additional blank line for spacing
    moveCursorToPosition(startColumn, startRow + 3);
    printf("|");
    for (int i = 0; i < numCols; i++)
    {
        printf("%*s|", widths[i] + 2, "");
    }
    printf("\n");

    // Print data row with centered text
    moveCursorToPosition(startColumn, startRow + 4);
    printf("|");
    cout << Color_Cyan;
    printCenteredText(gameName, widths[0]);
    cout << Color_Bright_Black;
    printf("|");
    char levelStr[10];
    cout << Color_Green;
    sprintf(levelStr, "%d", level);
    printCenteredText(levelStr, widths[1]);
    cout << Color_Bright_Black;
    printf("|");
    char totalScoreStr[10];
    cout << Color_Bright_White;
    sprintf(totalScoreStr, "%d", totalScore);
    printCenteredText(totalScoreStr, widths[2]);
    cout << Color_Bright_Black;
    printf("|");
    cout << Color_Bright_White;
    char currentPlayScoreStr[10];
    sprintf(currentPlayScoreStr, "%d", currentPlayScore);
    printCenteredText(currentPlayScoreStr, widths[3]);
    cout << Color_Bright_Black;
    printf("|");
    char overallScoreStr[10];
    cout << Color_Yellow;
    sprintf(overallScoreStr, "%d", overallScore);
    printCenteredText(overallScoreStr, widths[4]);
    cout << Color_Bright_Black;
    printf("|\n");

    // Print an additional blank line for spacing
    moveCursorToPosition(startColumn, startRow + 5);
    printf("|");
    for (int i = 0; i < numCols; i++)
    {
        printf("%*s|", widths[i] + 2, "");
    }
    printf("\n");

    // Print the bottom border
    moveCursorToPosition(startColumn, startRow + 6);
    printLine('+', '+', '+', widths, numCols, '=');
    cout << Color_Reset;
}

// Shuffle Words Code started -----------+++++++++++++---------

string shuffleSentence(const string &sentence) {
    vector<string> words;
    string word;
    istringstream stream(sentence);
    while (stream >> word) {
        words.push_back(word);
    }

    vector<string> originalWords = words; 

    do {
        shuffle(words.begin(), words.end(), default_random_engine(rand()));
    } while (words == originalWords); 

    stringstream shuffledSentence;
    for (const auto &w : words) {
        shuffledSentence << w << " ";
    }

    string result = shuffledSentence.str();
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    return result;
}

map<int, vector<pair<string, vector<string>>>> loadVocabulary(const string &filename)
{
    map<int, vector<pair<string, vector<string>>>> vocabulary;
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Unable to open file " << filename << endl;
        return vocabulary;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string levelStr, sentence, hint1, hint2;

        if (getline(ss, levelStr, ',') && getline(ss, sentence, ',') && getline(ss, hint1, ',') && getline(ss, hint2, ','))
        {
            int level = stoi(levelStr); // Convert level to integer
            vector<string> hints = {hint1, hint2};
            vocabulary[level].emplace_back(sentence, hints);
        }
    }

    file.close();
    return vocabulary;
}

void sen(User userData, int rows, int columns)
{
    string filename = "./src/game/sen.txt";
    map<int, vector<pair<string, vector<string>>>> sentences = loadVocabulary(filename);
    srand(static_cast<unsigned int>(time(0)));
    int mrows = rows;

    while (true)
    {
        rows = mrows;
        int stage[3] = {-1, -1, -1};
        int sele = -1;
        system("cls");
        ThemeFormate(rows, columns);
        WordScrambleData WordScrambleUserData = getSingleUserWordScrambleData(userData.id, userData.name);
        int level = levelSelection(rows, columns, 5, WordScrambleUserData.level);
        system("cls");
        ThemeFormate(rows, columns);
        auto entry = sentences[level];
        int totalSentences = sentences[level].size();
        int randomIndex = rand() % totalSentences;
        int iteration = 0;
        int hintCount = 0;
        int stg = 0;
        rows = rows / 2;

        while (sele <= 3)
        {
            for (const auto &entry : sentences[level])
            {

                const int MAX_SENTENCES = 10; // Maximum capacity for the array
                int in[MAX_SENTENCES];        // Array to store used random indices
                int inSize = 0;               // Current size of the in array
                if (iteration == randomIndex)
                {
                    while (1)
                    {

                        bool abc = true;
                        string sentence = entry.first;
                        string jumbledSentence;

                        while (abc)
                        {

                            do
                            {
                                jumbledSentence = shuffleSentence(sentence);
                            } while (toLower(jumbledSentence) == toLower(sentence));

                            // Check if the index is already used
                            bool indexUsed = false;
                            for (int i = 0; i < inSize; i++)
                            {
                                if (in[i] == randomIndex)
                                {
                                    indexUsed = true;
                                    break;
                                }
                            }

                            if (indexUsed)
                            {
                                // If the index is already used, generate a new one
                                randomIndex = rand() % totalSentences;
                            }
                            else
                            {
                                // If the index is unique, add it to the array
                                if (inSize < MAX_SENTENCES)
                                {
                                    in[inSize++] = randomIndex;
                                }
                                abc = false;
                            }
                        }
                        WordScrambleData WordScrambleUserData = getSingleUserWordScrambleData(userData.id, userData.name);
                        clearLines(rows - 10, rows + 11);
                        UserHeader("Level: " + to_string(level) + Color_Bright_Red + "   :::  Sentence Jumble :::  " + Color_Yellow + " Score : [" + to_string(WordScrambleUserData.score) + "] ", columns, Color_Bright_Red.length() + Color_Yellow.length(), true, "Stage : " + stageArrayToString(stage), "Coin : " + to_string(WordScrambleUserData.coin));
                        // moveCursorToPosition((columns - (jumbledSentence.length() * 2) - jumbledSentence.length()) / 2, rows - 4);
                        // moveCursorToPosition((columns - (jumbledSentence.length() * 2) - jumbledSentence.length())/1.7, rows - 2);
                        // center_Text(jumbledSentence, rows);
                        int charCount = jumbledSentence.length();
                        moveCursorToPosition((columns - charCount) / 2, rows - 4);

                        cout << jumbledSentence;
                        string trueSentence = entry.first;
                        string userSentence;
                        if (sele == 0)
                        {
                            updateWordScrambleData(userData.id, userData.name, WordScrambleUserData.level, WordScrambleUserData.score, WordScrambleUserData.coin - 1);
                            string hint = entry.second[hintCount++ % entry.second.size()];
                            moveCursorToPosition((columns - hint.length() - 10) / 2, rows - 2);
                            cout << Color_Yellow << "Hint : " << Color_Blue << "'" << hint << "'" << Color_Reset;
                        }

                        moveCursorToPosition((columns - 40) / 2, rows);
                        cout << "Type Your Sentence Here: ";
                        getline(cin, userSentence);

                        if (toLower(userSentence) == toLower(trueSentence))
                        {
                            moveCursorToPosition((columns - 22) / 2, rows + 2);
                            cout << Color_Bright_Green << "+---------------------+";
                            moveCursorToPosition((columns - 22) / 2, rows + 3);
                            cout << "|  Great! You Win!   |";
                            moveCursorToPosition((columns - 22) / 2, rows + 4);
                            cout << "+---------------------+" << Color_Reset;
                            moveCursorToPosition(columns, rows - 22);
                            sele = -1;
                            stage[stg++] = hintCount != 0 ? 5 : 10;
                            break;
                        }
                        else
                        {
                            moveCursorToPosition((columns - 35) / 2, rows + 2);
                            cout << Color_Bright_Red << "+--------------------------------+";
                            moveCursorToPosition((columns - 35) / 2, rows + 3);
                            cout << "|  Wrong Sentence! Try Again!   |";
                            moveCursorToPosition((columns - 35) / 2, rows + 4);
                            cout << "+--------------------------------+" << Color_Reset;
                            sele = hintButtons(rows + 6);
                            if (sele == 1)
                                continue;
                            else if (sele == 2)
                            {
                                system("cls");
                                return;
                            }
                            else if (sele == 3)
                                break;
                        }
                    }

                    if (stg >= 3 || sele == 3)
                        break;
                }
                else
                {
                    iteration++;
                }
            }

            if (stg >= 3)
            {
                UserHeader("Level: " + to_string(level) + Color_Bright_Red + "   :::  Sentence Jumble :::  " + Color_Yellow + " Score : [" + to_string(WordScrambleUserData.score) + "] ", columns, Color_Bright_Red.length() + Color_Yellow.length(), true, "Stage : " + stageArrayToString(stage), "Coin : " + to_string(WordScrambleUserData.coin));
                char gameName[50] = "Sentence Jumble";
                int currentPlayScore = 0;
                for (int i = 0; i < 3; ++i)
                {
                    currentPlayScore += stage[i];
                }
                updateWordScrambleData(userData.id, userData.name, (level == WordScrambleUserData.level) ? WordScrambleUserData.level + 1 : WordScrambleUserData.level, WordScrambleUserData.score + currentPlayScore, (currentPlayScore == 30) ? WordScrambleUserData.coin + 1 : WordScrambleUserData.coin);
                ScoreBoard(gameName, level, WordScrambleUserData.score, currentPlayScore, columns, rows);
                level++;
                _getch();
                break;
            }
            else
            {
                iteration = 0;
            }

            if (sele == 3)
                break;
        }
    }
}
// void verbOrNoun(int rows, int columns, User userData) {
//     clearScreen();
//     drawHeader("Verb or Noun Game");

//     map<string, string> words = {{"run", "verb"}, {"apple", "noun"}, {"jump", "verb"}, {"table", "noun"}};
//     int score = 0;

//     for (int i = 0; i < 5; ++i) {
//         auto it = words.begin();
//         advance(it, rand() % words.size());
//         string word = it->first;
//         string type = it->second;

//         displayText("Is '" + word + "' a verb or noun? (v/n): ", YELLOW);
//         char answer;
//         cin >> answer;

//         if ((answer == 'v' && type == "verb") || (answer == 'n' && type == "noun")) {
//             displayText("Correct!", GREEN);
//             score += 10;
//         } else {
//             displayText("Wrong!", RED);
//         }
//     }

//     displayText("Your final score: " + to_string(score), BOLD + GREEN);
//     drawBorder();
// }

// void hangman() {
//     clearScreen();
//     drawHeader("Hangman Game");

//     vector<string> words = {"hangman", "game", "terminal", "program"};
//     string word = words[rand() % words.size()];

//     string guessed(word.size(), '_');
//     int lives = 6;

//     while (lives > 0 && guessed != word) {
//         displayText("Word: " + guessed, YELLOW);
//         displayText("Lives remaining: " + to_string(lives), RED);

//         char guess;
//         displayText("Enter a letter: ", GREEN);
//         cin >> guess;

//         bool correct = false;
//         for (size_t i = 0; i < word.size(); ++i) {
//             if (word[i] == guess) {
//                 guessed[i] = guess;
//                 correct = true;
//             }
//         }

//         if (!correct) {
//             --lives;
//         }
//     }

//     if (guessed == word) {
//         displayText("You won! The word was: " + word, GREEN);
//     } else {
//         displayText("Game over! The word was: " + word, RED);
//     }

//     drawBorder();
// }

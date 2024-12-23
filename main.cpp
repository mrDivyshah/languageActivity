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
#include <unordered_set>
#include "src/gameList.cpp"
#include "src/headding.cpp" // nameSpace, windows.h, iostream, system.cpp
#include "src/databse_function/connection.cpp"
#include "src/databse_function/WordScrambleDatabase.cpp"
#include "src/databse_function/SenScramble.cpp"
#include "src/databse_function/fillin.cpp"
// #include "src/game/WordScramble.cpp"
#include "src/game/SentenceJumbble.cpp"
#include "src/game/fillingTheBlanks.cpp"
#include "src/themeFormat.cpp"
#include "src/AlertMessage.cpp"
#include "src/Manager.cpp"
#include "src/Admin/main.cpp"

struct SelectionValue
{
    int selected;
    bool enterPressed;
};

int G_columns, G_rows;
User LoginUser(int columns, int rows);
void printMenu(int selected, int rows, int columns);
int menuSelectionPrint(int rows, int columns);
SelectionValue Selection(int selected, int total);
void Home(int rows, int columns, User userData);
void wordScramble(User userData, int rows, int columns);
void printLine(char start, char mid, char end, int widths[], int numCols, char fill);
void printCenteredText(const char *text, int width);
void ScoreBoard(char gameName[50], int level, int totalScore, int currentPlayScore, int columns, int rows);
void CrossWords(User userData, int rows, int columns);
void fill(User userData, int rows, int columns);

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
    ThemeFormat(rows, columns);
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
    Home(rows, columns, userData);
    _getch();
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
                    ThemeFormat(G_rows, G_columns);
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
                    addSenData(userData.id, userData.name, 1, 0, 10);
                    addFillintheData(userData.id, userData.name, 1, 0, 10);
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
    int gameListSize = gameList.size();
    struct HomeMenu
    {
        int index;
        string MenuItem;
    };
    int selected = 0;
    ThemeFormat(G_rows, G_columns);
    while (true)
    {
        HomerMenu(rows, columns, selected);
        UserHeader("User Name : " + userData.name + " [" + to_string(userData.id) + "]      Joined On: " + userData.joiningDate, columns, 0, false, "", "");
        SelectionValue option = Selection(selected, gameListSize);
        if (option.enterPressed)
        {
            if (option.selected == gameListSize)
            {
                ManageUserDataMenu(rows, columns, userData);
                clearLines(G_rows-30,G_rows-5);
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

                            CrossWords(userData, rows, columns);
                        }
                        else if (game.index == 2)
                        {
                            wordScramble(userData, rows, columns);
                        }
                        else if (game.index == 3)
                        {
                            fill(userData, rows, columns);
                        }
                        ThemeFormat(G_rows, G_columns);
                    }
                    clearLines(13, rows - 10);
                }
            }
        }

        selected = option.selected;
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
    map<int, vector<pair<string, vector<string>>>> words = parseFiles();
    srand(static_cast<unsigned int>(time(0)));
    int mrows = rows;
    WordScrambleData WordScrambleUserData = getSingleUserWordScrambleData(userData.id, userData.name);
    while (true)
    {
        rows = mrows;
        int stage[3] = {-1, -1, -1};
        int sele = -1;
        system("cls");
        ThemeFormat(rows, columns);
        int level = levelSelection(rows, columns, 5, WordScrambleUserData.level);
        system("cls");
        ThemeFormat(rows, columns);
        auto entry = words[level];
        int totalWords = words[level].size();
        int randomeIndex = rand() % totalWords;
        int itretion = 0;
        int hintCount = 0;
        int stg = 0;
        rows = rows / 2;
        bool hintUse = false;
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
                        if (sele == 0)
                        {
                            updateWordScrambleData(userData.id, userData.name, WordScrambleUserData.level, WordScrambleUserData.score, WordScrambleUserData.coin - 1);
                        }
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
                            string hint = entry.second[hintCount++ % 5];
                            moveCursorToPosition((columns - hint.length() - 10) / 2, rows - 2);
                            cout << Color_Yellow << "Hint : " << Color_Blue << "'" << hint << "'" << Color_Reset;
                            sele = -1;
                            hintUse = true;
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
                            if (hintUse == true)
                            {
                                stage[stg++] = 5;
                                hintUse = false;
                            }
                            else
                            {
                                stage[stg++] = 10;
                            }
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
                WordScrambleUserData = getSingleUserWordScrambleData(userData.id, userData.name);
                UserHeader("Level: " + to_string(level) + Color_Bright_Red + "   :::  Word Scramble :::  " + Color_Yellow + " Score : [" + to_string(WordScrambleUserData.score) + "] ", columns, Color_Bright_Red.length() + Color_Yellow.length(), true, "Stage : " + stageArrayToString(stage), "Coin : " + to_string(WordScrambleUserData.coin));
                char gameName[50] = "Word Scramble";
                int currentPlayScore = 0;
                for (int i = 0; i < 3; ++i)
                {
                    currentPlayScore += stage[i];
                }
                updateWordScrambleData(userData.id, userData.name, (level == WordScrambleUserData.level) ? WordScrambleUserData.level + 1 : WordScrambleUserData.level, WordScrambleUserData.score + currentPlayScore, currentPlayScore == 30 ? WordScrambleUserData.coin + 1 : WordScrambleUserData.coin);
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

// CrossWords Code started -----------+++++++++++++---------

void CrossWords(User userData, int rows, int columns)
{
    map<int, vector<pair<string, vector<string>>>> sentences = loadVocabulary();
    srand(static_cast<unsigned int>(time(0)));

    int mrows = rows;
    int sele = -1;

    while (true)
    {
        rows = mrows;
        int stage[3] = {-1, -1, -1};
        system("cls");
        ThemeFormat(rows, columns);

        SenData SenUserData = getSingleUserSenData(userData.id, userData.name);
        int level = levelSelection(rows, columns, 5, SenUserData.level);
        system("cls");
        ThemeFormat(rows, columns);
        auto entry = sentences[level];
        int totalSentences = sentences[level].size();
        int randomIndex = rand() % totalSentences;
        int iteration = 0;
        int hintCount = 0;
        int stg = 0;
        rows = rows / 2;
        bool hintUsed = false;
        while (sele <= 3)
        {

            for (const auto &entry : sentences[level])
            {

                if (iteration == randomIndex)
                {
                    const int MAX_SENTENCES = 10; // Maximum capacity for the array
                    int in[MAX_SENTENCES];        // Array to store used random indices
                    int inSize = 0;
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
                        if (sele == 0)
                        {
                            updateSenData(userData.id, userData.name, SenUserData.level, SenUserData.score, SenUserData.coin - 1);
                        }
                        SenData SenUserData = getSingleUserSenData(userData.id, userData.name);
                        clearLines(rows - 10, rows + 11);
                        UserHeader("Level: " + to_string(level) + Color_Bright_Red + "   :::  CrossWords :::  " + Color_Yellow + " Score : [" + to_string(SenUserData.score) + "] ", columns, Color_Bright_Red.length() + Color_Yellow.length(), true, "Stage : " + stageArrayToString(stage), "Coin : " + to_string(SenUserData.coin));

                        if (sele == 0)
                        {
                            string hint = entry.second[hintCount++ % entry.second.size()];
                            moveCursorToPosition((columns - hint.length() - 10) / 2, rows - 2);
                            cout << Color_Yellow << "Hint : " << Color_Blue << "'" << hint << "'" << Color_Reset;
                            sele = -1;
                            hintUsed = true;
                        }
                        int charCount = jumbledSentence.length();
                        moveCursorToPosition((columns - charCount) / 2, rows - 4);

                        cout << jumbledSentence;
                        string trueSentence = entry.first;
                        string userSentence;

                        moveCursorToPosition((columns - 40) / 2, rows);
                        cout << "Type Your Sentence Here: ";
                        getline(cin, userSentence);

                        if (toLower(userSentence) == toLower(trueSentence))
                        {
                            moveCursorToPosition((columns - 22) / 2, rows + 2);
                            cout << Color_Bright_Green << "+---------------------+";
                            moveCursorToPosition((columns - 22) / 2, rows + 3);
                            cout << "|   Great! You Win!   |";
                            moveCursorToPosition((columns - 22) / 2, rows + 4);
                            cout << "+---------------------+" << Color_Reset;
                            moveCursorToPosition(columns, rows - 22);
                            sele = -1;
                            stage[stg++] = hintUsed == true ? 5 : 10;
                            hintUsed = false;
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
                            {
                                sele = -1;
                                continue;
                            }
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
                SenData SenUserData = getSingleUserSenData(userData.id, userData.name);
                UserHeader("Level: " + to_string(level) + Color_Bright_Red + "   :::  CrossWords :::  " + Color_Yellow + " Score : [" + to_string(SenUserData.score) + "] ", columns, Color_Bright_Red.length() + Color_Yellow.length(), true, "Stage : " + stageArrayToString(stage), "Coin : " + to_string(SenUserData.coin));
                char gameName[50] = "CrossWords";
                int currentPlayScore = 0;
                for (int i = 0; i < 3; ++i)
                {
                    currentPlayScore += stage[i];
                }
                updateSenData(userData.id, userData.name, (level == SenUserData.level) ? SenUserData.level + 1 : SenUserData.level, SenUserData.score + currentPlayScore, (currentPlayScore == 30) ? SenUserData.coin + 1 : SenUserData.coin);
                ScoreBoard(gameName, level, SenUserData.score, currentPlayScore, columns, rows);
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

// filling the blnks Code started -----------+++++++++++++---------

int hintButtonsforfil(int row)
{
    const int LEFT_ARROW = 75;
    const int RIGHT_ARROW = 77;
    const int ENTER_KEY = 13;

    // Calculate button positions based on G_columns
    int firstColumn = G_columns / 6;            // Updated for 3 buttons
    int secondColumn = 3 * (G_columns / 6) - 6; // Adjusted column spacing
    int thirdColumn = 5 * (G_columns / 6) - 12; // third button

    int currentSelection = 0; // 0 -> Retry, 1 -> Exit, 2 -> Back

    while (true)
    {
        // Draw the buttons, highlighting the selected one

        // Button 1: Retry
        moveCursorToPosition(firstColumn, row);
        if (currentSelection == 0)
        {
            cout << Color_Blue << "***********" << Color_Reset;
        }
        else
        {
            cout << "-----------";
        }
        moveCursorToPosition(firstColumn, row + 1);
        cout << "|  Retry  |";
        moveCursorToPosition(firstColumn, row + 2);
        if (currentSelection == 0)
        {
            cout << Color_Blue << "***********" << Color_Reset;
        }
        else
        {
            cout << "-----------";
        }

        // Button 2: Exit
        moveCursorToPosition(secondColumn, row);
        if (currentSelection == 1)
        {
            cout << Color_Red << "***********" << Color_Reset;
        }
        else
        {
            cout << "-----------";
        }
        moveCursorToPosition(secondColumn, row + 1);
        cout << "|   Exit  |";
        moveCursorToPosition(secondColumn, row + 2);
        if (currentSelection == 1)
        {
            cout << Color_Red << "***********" << Color_Reset;
        }
        else
        {
            cout << "-----------";
        }

        // Button 3: Back
        moveCursorToPosition(thirdColumn, row);
        if (currentSelection == 2)
        {
            cout << Color_Cyan << "***********" << Color_Reset;
        }
        else
        {
            cout << "-----------";
        }
        moveCursorToPosition(thirdColumn, row + 1);
        cout << "|   Back  |";
        moveCursorToPosition(thirdColumn, row + 2);
        if (currentSelection == 2)
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
                currentSelection = (currentSelection + 2) % 3; // Move left, wrap around
            }
            else if (key == RIGHT_ARROW)
            {
                currentSelection = (currentSelection + 1) % 3; // Move right, wrap around
            }
        }

        // Enter key to confirm selection
        if (key == ENTER_KEY)
        {
            return currentSelection; // Return the selected button
        }
    }
}

string buttons(int row, int columns, const vector<string> &buttonLabels)

{
    const int LEFT_ARROW = 75;
    const int RIGHT_ARROW = 77;
    const int ENTER_KEY = 13;
    char alpha[4] = {'A', 'B', 'C', 'D'};
    int buttonCount = buttonLabels.size();
    if (buttonCount < 3 || buttonCount > 4)
    {
        throw invalid_argument("Button count must be 3 or 4.");
    }

    int currentSelection = 0;

    while (true)
    {
        // Clear previous buttons
        for (int i = 0; i < buttonCount; ++i)
        {
            moveCursorToPosition(0, row + i * 3);
            cout << string(columns, ' ');
        }

        // Draw buttons dynamically
        for (int i = 0; i < buttonCount; ++i)
        {
            int buttonWidth = 12;
            int buttonSpacing = columns / (buttonCount + 1);
            int buttonX = buttonSpacing * (i + 1) - buttonWidth / 2;

            // Set color based on selection
            string color = (i == currentSelection) ? Color_Bright_Cyan : Color_White;

            // Draw top border

            // Draw label
            moveCursorToPosition(buttonX, row + 1);
            cout << color << "(" << alpha[i] << ") " << buttonLabels[i] << Color_Reset;
        }

        // Wait for user input
        int key = _getch();

        // Arrow key handling
        if (key == 224)
        {
            key = _getch(); // Get the actual key code
            if (key == LEFT_ARROW)
            {
                currentSelection = (currentSelection - 1 + buttonCount) % buttonCount;
            }
            else if (key == RIGHT_ARROW)
            {
                currentSelection = (currentSelection + 1) % buttonCount;
            }
        }

        // Enter key to confirm selection
        if (key == ENTER_KEY)
        {
            return buttonLabels[currentSelection];
        }
    }
}

void fill(User userData, int rows, int columns)
{
    map<int, vector<pair<string, vector<string>>>> sentences = loadfillintheblanks();
    srand(static_cast<unsigned int>(time(0)));
    int mrows = rows;

    while (true)
    {
        rows = mrows;
        int stage[3] = {-1, -1, -1};
        int sele = -1;
        system("cls");
        ThemeFormat(rows, columns);
        int attp = 0;
        FillintheData FillintheUserData = getSingleUserFillintheData(userData.id, userData.name);
        int level = levelSelection(rows, columns, 5, FillintheUserData.level);
        system("cls");
        ThemeFormat(rows, columns);
        auto entry = sentences[level];
        int totalSentences = sentences[level].size();
        unordered_set<int> usedIndices;

        int stg = 0;
        rows = rows / 2;
        while (stg < 3)
        {
            attp = 0;
            int randomIndex;
            do
            {
                randomIndex = rand() % totalSentences;
            } while (usedIndices.count(randomIndex));
            usedIndices.insert(randomIndex);

            const auto &entry = sentences[level][randomIndex];
            string jumbledSentence = entry.first;
            string trueSentence = entry.second[0];
            vector<string> options = {entry.second[1], entry.second[2], entry.second[3], entry.second[4]};

            clearLines(rows - 10, rows + 11);
            UserHeader("Level: " + to_string(level) + " ::: Fill In the Blanks ::: Score : [" + to_string(FillintheUserData.score) + "] ", columns, 0, true, "Stage : " + stageArrayToString(stage), " ");

            int charCount = jumbledSentence.length();
            moveCursorToPosition((columns - charCount) / 2, rows - 4);
            cout << jumbledSentence;

            string userSentence = buttons(rows - 2, columns, options);

            if (toLower(userSentence) == toLower(trueSentence))
            {
                moveCursorToPosition((columns - 22) / 2, rows + 2);
                cout << "+---------------------+";
                moveCursorToPosition((columns - 22) / 2, rows + 3);
                cout << "|  Great! You Win!   |";
                moveCursorToPosition((columns - 22) / 2, rows + 4);
                cout << "+---------------------+";
                stage[stg++] = 10;
            }
            else
            {
                if (attp < 3)
                {
                    attp = attp + 1;
                }
                if (attp > 1)
                {
                    moveCursorToPosition((columns - 35) / 2, rows + 2);
                    cout << "+--------------------------------+";
                    moveCursorToPosition((columns - 35) / 2, rows + 3);
                    cout << "|  attempts done!    " << "Attempts :" + to_string(attp) + "   |";
                    moveCursorToPosition((columns - 35) / 2, rows + 4);
                    cout << "+--------------------------------+";
                    _getch();
                    break;
                }
                else
                {
                    moveCursorToPosition((columns - 50) / 2, rows + 2);
                    cout << Color_Red << "+------------------------------------------------+";
                    moveCursorToPosition((columns - 50) / 2, rows + 3);
                    cout << "|  Wrong Sentence! Try Again!     " << Color_Bright_Cyan << "Attempts : " << to_string(attp) << Color_Red << "   |";
                    moveCursorToPosition((columns - 50) / 2, rows + 4);
                    cout << "+------------------------------------------------+" << Color_Reset;
                    sele = hintButtonsforfil(rows + 6);

                    if (sele == 0)
                    {
                        continue;
                    }
                    else if (sele == 1)
                    {
                        system("cls");
                        return;
                    }
                    else if (sele == 2)
                        break;
                }
            }

            if (sele == 3)
                break;

            if (stg >= 3)
            {
                UserHeader("Level: " + to_string(level) + " ::: Fill In the Blanks ::: Score : [" + to_string(FillintheUserData.score) + "] ", columns, 0, true, "Stage : " + stageArrayToString(stage), " ");
                char gameName[50] = "Fill In the Blanks";
                int currentPlayScore = 0;
                for (int i = 0; i < 3; ++i)
                    currentPlayScore += stage[i];
                updateFillintheData(userData.id, userData.name, (level == FillintheUserData.level) ? FillintheUserData.level + 1 : FillintheUserData.level, FillintheUserData.score + currentPlayScore, (currentPlayScore == 30) ? FillintheUserData.coin + 1 : FillintheUserData.coin);
                ScoreBoard(gameName, level, FillintheUserData.score, currentPlayScore, columns, rows);
                level++;
                _getch();
                break;
            }
            else
            {
                if (sele == 3)
                    break;
            }
        }
    }
}

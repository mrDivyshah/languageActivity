#include <stdlib.h>
#include <windows.h>
#include <string>
#include <conio.h>
#include "src/colors.cpp"
#include "src/headding.cpp" // nameSpace, windows.h, iostream, system.cpp
#include "src/time.cpp"     //nameSpace, ctime, thread, chrono
#include "src/databse_function/connection.cpp"
#include "src/game/WordScramble.cpp"
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
    {1, "Hangmen", "Hangman"},
    {2, "Puzal Alfa", "Puzal"},
    {3, "Verb and Noun", "VerbNoun"},
    {4, "Word Scramble", "wordScramble"}};

void Header(int &rows, int &columns, string headding);
void Footer(int &rows, int &columns, string Text);
void ThemeFormate(int rows, int columns);
void printMenu(int selected, int rows, int columns);
int menuSelectionPrint(int rows, int columns);
void clearLines(int startRow, int endRow);
void AlertMessage(int rows, int coumns, string type, string msg);
SelectionValue Selection(int selected, int total);
void ScoreBoard();
void time();
void Home(int rows, int columns, User userData);
void wordScramble(User userData);
int G_columns, G_rows;
string GAME_NAME = "~: WORDWISE :~";

int main()
{
    int columns, rows;
    User userData = {-1, " ", " "};
    int cardColumn = 60, age;

    int index = 0;
    do
    {
        consoleRowAndColumn(rows, columns);
        if (columns < 204 && rows < 50)
        {
            system("cls");
            cout << "Please Open Maximized terminal And Press Enter";
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
    userData.id = 1;
    userData.joiningDate = "10/21/2022";
    userData.name = "divyshah";
    userData.password = "12131415";
    Home(rows, columns, userData);
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

void printMenu(int selected, int rows, int columns)
{
    int index = 0;
    for (string user : AllAvailableUsers())
    {
        moveCursorToPosition(columns + 9 - (user.length() / 2), rows + index);
        cout << (selected == index ? Color_Cyan + "-> " + Color_Underline_On : "   ") << user << Color_Reset + Color_Underline_Off << "\n";
        index++;
    }
    moveCursorToPosition(columns - 22, rows + index + 1);
    cout << (selected == index ? Color_Green : "") << "-------------------------------------------------------------------------";
    moveCursorToPosition(columns + 6, rows + index + 2);
    cout << (selected == index ? Color_Green + "-> " : "   ") << "New User" << Color_Reset << "\n";
    moveCursorToPosition(columns - 22, rows + index + 3);
    cout << (selected == index + 1 ? Color_Red : "") << (selected == index ? Color_Green : "") << "-------------------------------------------------------------------------" << Color_Reset;
    moveCursorToPosition(columns + 8, rows + index + 4);
    cout << (selected == index + 1 ? Color_Red + "-> " : "   ") << "EXIT" << Color_Reset;
    moveCursorToPosition(columns - 22, rows + index + 5);
    cout << (selected == index + 1 ? Color_Red : "") << "-------------------------------------------------------------------------\n"
         << Color_Reset;
}

int menuSelectionPrint(int rows, int columns)
{
    int selected = 0;
    printMenu(selected, rows, columns);
    while (true)
    {
        SelectionValue option = Selection(selected, getUserCount() + 1);
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
    Footer(rows, columns, "Use Arrow <Up> and <Down> Key For Manu Navigation, Use <Enter Key> For Select a Option, Remove Aleart Box using <Enter Key>.");
    BoldTitle(columns, cardColumn, 5);
}

void UserHeader(string content, int column, int minusLength)
{
    int contentLength = content.length() - minusLength;
    int padding = 12;
    int boxWidth = contentLength + padding;
    int boxHeight = 7;

    int startColumn = (column - boxWidth) / 2;
    int startRow = 13;

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
}

int HomerMenu(int rows, int columns, int selected)
{
    int box_column = 42;
    moveCursorToPosition((columns - 43) / 2, 20);
    cout << "+";
    for (int i = 0; i <= box_column - 2; i++)
        cout << "-";
    cout << "+";
    // cout << "+-----------------------------------------+";
    moveCursorToPosition((columns - 43) / 2, 21);
    cout << "|";
    moveCursorToPosition((columns - 39) / 2, 21);
    cout << "[-] Select Game";
    moveCursorToPosition((columns + 42) / 2, 21);
    cout << "|";
    moveCursorToPosition((columns - 43) / 2, 22);
    cout << "+-----------------------------------------+";
    // Games Here Show
    int count = 0;
    for (const auto &DSgame : gameList)
    {
        moveCursorToPosition((columns - 43) / 2, 23 + count);
        cout << "|";
        moveCursorToPosition((columns - 34) / 2, 23 + count);
        cout << (selected == count ? Color_Green + ">> " : Color_Bright_Black + "   ") << DSgame.name << Color_Reset;
        moveCursorToPosition((columns + 42) / 2, 23 + count);
        cout << "|";
        count++;
    }
    moveCursorToPosition((columns - 43) / 2, 22 + count + 1);
    cout << "+-----------------------------------------+";
    moveCursorToPosition((columns - 43) / 2, 23 + count + 1);
    cout << "|";
    moveCursorToPosition((columns - 20) / 2, 23 + count + 1);
    cout << (selected == count ? Color_Yellow + ">> " : "   ") << "Manage Account" << Color_Reset;
    moveCursorToPosition((columns + 42) / 2, 23 + count + 1);
    cout << "|";
    moveCursorToPosition((columns - 43) / 2, 24 + count + 1);
    cout << "+-----------------------------------------+";
    moveCursorToPosition((columns - 43) / 2, 25 + count + 1);
    cout << "|";
    moveCursorToPosition((columns - 10) / 2, 25 + count + 1);
    cout << (selected == count + 1 ? Color_Red + ">> " : "   ") << "Exit" << Color_Reset;
    moveCursorToPosition((columns + 42) / 2, 25 + count + 1);
    cout << "|";
    moveCursorToPosition((columns - 42) / 2, 26 + count + 1);
    cout << "+-----------------------------------------+";
    return 0;
}

void Home(int rows, int columns, User userData)
{
    ThemeFormate(rows, columns);
    int gameListSize = gameList.size();
    struct HomeMenu
    {
        int index;
        string MenuItem;
    };

    UserHeader("User Name : " + userData.name + " [" + to_string(userData.id) + "]      Joined On: " + userData.joiningDate, columns, 0);
    int selected = 0;
    HomerMenu(rows, columns, selected);
    while (true)
    {
        SelectionValue option = Selection(selected, gameListSize);
        if (option.enterPressed)
        {
            break;
        }
        selected = option.selected;
        HomerMenu(rows, columns, option.selected);
    }

    if (selected == gameListSize)
    {
        cout << "Selected Menu";
    }

    else if (selected == gameListSize + 1)
    {
        cout << "this is Exit";
        return;
    }
    else
    {
        for (const auto &game : gameList)
        {
            if (selected == game.index - 1)
            {
                if (game.index == 4)
                {
                    // wordScramble(userData);
                    system("cls");
                    ScoreBoard();
                }
                // game.functionName(userData);
                // cout << "Selected Game is :: " << game.name;
            }
        }
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
    int firstColumn = G_columns / 6;
    int secondColumn = G_columns / 2 - 6;
    int thirdColumn = 5 * (G_columns / 6) - 9;

    int currentSelection = 0; // 0 -> Hint, 1 -> Retry, 2 -> Exit

    while (true)
    {
        // Clear the previous buttons before redrawing (if necessary)

        // Draw the buttons, highlighting the selected one
        moveCursorToPosition(firstColumn, row);
        if (currentSelection == 0)
        {

            cout << "***********"; // Highlighted button
        }
        else
        {
            cout << "-----------"; // Normal button
        }
        moveCursorToPosition(firstColumn, row + 1);
        cout << "|   Hint  |";
        moveCursorToPosition(firstColumn, row + 2);
        if (currentSelection == 0)
        {
            cout << "***********";
        }
        else
        {
            cout << "-----------";
        }

        moveCursorToPosition(secondColumn, row);
        if (currentSelection == 1)
        {
            cout << "***********";
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
            cout << "***********";
        }
        else
        {
            cout << "-----------";
        }

        moveCursorToPosition(thirdColumn, row);
        if (currentSelection == 2)
        {
            cout << "***********";
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
            cout << "***********";
        }
        else
        {
            cout << "-----------";
        }

        // Wait for user input
        int key = _getch();

        // Arrow key handling
        if (key == 224)
        {                   // Arrow keys are signaled by a 224 prefix
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

void wordScramble(User userData)
{
    int rows = G_rows;
    int columns = G_columns;
    ThemeFormate(rows, columns);
    int sele = -1;
    map<int, vector<pair<string, vector<string>>>> words = vocabulary;
    srand(static_cast<unsigned int>(time(0)));
    int score = 0;
    int level = 1;
    while (true)
    {
        UserHeader(userData.name + " [" + to_string(userData.id) + "] " + Color_Bright_Red + " :::  Word Scramble :::  " + Color_Yellow + "  Level: " + to_string(level), columns, Color_Bright_Red.length() + Color_Yellow.length());

        auto entry = words[level];
        int hintCount = 0;
        int totalWords = words[level].size();
        int randomeIndex = rand() % totalWords;
        int itretion = 0;
        for (const auto &entry : words[level])
        {
            if (itretion == randomeIndex)
            {
                string MyWord = entry.first;
                string wordIntr = shuffleLetter(MyWord);
                while (1)
                {
                    clearLines(rows - 32, rows - 10);
                    moveCursorToPosition((columns - (20)) / 2, rows - 35);
                    cout << ":: Scramble Word ::";
                    moveCursorToPosition((columns - (wordIntr.length() * 3) - wordIntr.length()) / 2, rows - 32);
                    for (const auto &latter : wordIntr)
                    {
                        cout << "  " << static_cast<char>(toupper(latter));
                    }
                    string trueWord = entry.first;
                    string userWord;
                    if (sele == 0)
                    {
                        string hint = entry.second[hintCount++ % 5];
                        moveCursorToPosition((columns - hint.length() - 10) / 2, rows - 30);
                        cout << Color_Yellow << "Hint : " << Color_Blue << "'" << hint << "'" << Color_Reset;
                    }
                    moveCursorToPosition((columns - (40)) / 2, rows - 28);
                    cout << "Type Your Word Here : " << trueWord << "  ";
                    getline(cin, userWord);
                    if (toLower(userWord) == trueWord)
                    {
                        moveCursorToPosition((columns - 22) / 2, rows - 25);
                        cout << Color_Bright_Green << "+---------------------+";
                        moveCursorToPosition((columns - 22) / 2, rows - 24);
                        cout << "|  Great You Are Win  |";
                        moveCursorToPosition((columns - 22) / 2, rows - 23);
                        cout << "+---------------------+" << Color_Reset;
                        break;
                    }
                    else
                    {
                        moveCursorToPosition((columns - 35) / 2, rows - 25);
                        cout << Color_Bright_Red << "+--------------------------------+";
                        moveCursorToPosition((columns - 35) / 2, rows - 24);
                        cout << "|  Wrong Word! Please Try Again  |";
                        moveCursorToPosition((columns - 35) / 2, rows - 23);
                        cout << "+--------------------------------+" << Color_Reset;
                    }
                    sele = hintButtons(34);
                }
                // center_Text("Type Your Word Here : ", 30);
                // cout << "\nHints: ";
                // for (const string &hint : entry.second)
                // {
                //     cout << hint << ", ";
                // }
            }
            itretion++;
        }
        cout << "\n";
        break;
    }

    //    cout << "Original: " << word << " | Shuffled: " << wordIntr << endl;
}

void ScoreBoard()
{
    cout << "+-------------------------------------+";
    
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

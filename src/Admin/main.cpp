#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <conio.h>
#include "../databse_function/admin_data.cpp"

using namespace std;

void AdmindisplayUsers()
{
    fstream file(USER_DATABASE, ios::in);
    string line;

    if (file.is_open())
    {
        cout << Color_Cyan << "\n+------------+--------------------+--------------------+" << Color_Reset << "\n";
        cout << Color_Cyan << "| " << setw(10) << "ID" << Color_Reset
             << Color_Cyan << " | " << setw(18) << "Name" << Color_Reset
             << Color_Cyan << " | " << setw(18) << "Joining Date" << Color_Reset << Color_Cyan << " |" << "\n";
        cout << Color_Cyan << "+------------+--------------------+--------------------+" << Color_Reset << "\n";

        bool hasUsers = false;

        while (getline(file, line))
        {
            hasUsers = true;

            stringstream ss(line);
            string id, name, joiningDate;

            // Split by comma
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, joiningDate, ',');

            // Display data
            cout << Color_Cyan << "| " << Color_Reset << setw(10) << id
                 << Color_Cyan << " | " << Color_Reset << setw(18) << name
                 << Color_Cyan << " | " << Color_Reset << setw(18) << joiningDate
                 << Color_Cyan << " |" << Color_Reset << "\n";
        }

        if (!hasUsers)
        {
            cout << Color_Cyan << "| " << Color_Reset << setw(52) << "No users found!" << Color_Cyan << " |" << Color_Reset << "\n";
        }

        cout << Color_Cyan << "+------------+--------------------+--------------------+" << Color_Reset << "\n";

        file.close();
    }
    else
    {
        cout << Color_Red << "Unable to open file.\n"
             << Color_Reset;
    }
}

void printUserDetailsBox(const User &user)
{
    // Gather user details
    cout << "\n";
    stringstream userDetails;
    userDetails << "User found:\n";
    userDetails << "ID: " << user.id << "\n";
    userDetails << "Name: " << user.name << "\n";
    userDetails << "Joining Date: " << user.joiningDate << "\n";

    // Extract details as a string and determine the maximum line width
    string details = userDetails.str();
    istringstream iss(details);
    string line;
    size_t maxLineWidth = 0;

    while (getline(iss, line))
    {
        maxLineWidth = max(maxLineWidth, line.length());
    }

    // Add padding for aesthetics
    size_t boxWidth = maxLineWidth + 4;

    // Reset the stringstream to read the lines again
    iss.clear();
    iss.seekg(0, ios::beg);

    // Print the top border
    cout << Color_Green << string(boxWidth, '*') << "\n"
         << Color_Reset;

    // Print each line with padding
    while (getline(iss, line))
    {
        cout << Color_Green << "* " << left << setw(maxLineWidth) << line << " *\n"
             << Color_Reset;
    }

    // Print the bottom border
    cout << Color_Green << string(boxWidth, '*') << "\n"
         << Color_Reset;
}

void displayMenu()
{
    // Define menu items
    string title = "Admin Panel Of WordWise";
    string menuItems[] = {
        "1. Display All Users",
        "2. Update User",
        "3. Search User",
        "4. Word Scramble",
        "5. - Display Words",
        "6. - Search word",
        "7. - Add Word",
        "8. Exit"};
    size_t menuCount = sizeof(menuItems) / sizeof(menuItems[0]); // Total number of menu items
    // Determine the width of the table based on the longest item
    size_t maxWidth = title.length();
    for (const string &item : menuItems)
    {
        maxWidth = max(maxWidth, item.length());
    }
    maxWidth += 4;                              // Add padding for aesthetics
    size_t tableHeight = 2 + 1 + menuCount + 1; // Header, divider, items, bottom border

    // Get console dimensions
    int rows, columns;
    consoleRowAndColumn(rows, columns);
    Header(rows, columns, "WordWise Admin");
    // Calculate starting position for centering
    int startRow = (rows - tableHeight - 10) / 4;
    int startColumn = (columns - (maxWidth + 4)) / 2;

    // Print the table at the center
    moveCursorToPosition(startColumn, startRow);
    cout << Color_Blue << string(maxWidth + 4, '=') << "\n";
    moveCursorToPosition(startColumn, startRow + 1);
    cout << "| " << Color_White << setw(maxWidth) << left << title << Color_Blue << " |\n";
    moveCursorToPosition(startColumn, startRow + 2);
    cout << string(maxWidth + 4, '=') << "\n";

    // Print the menu items with pipe-separated indices

    for (size_t i = 0; i < menuCount; i++) // Use `menuCount` as the limit
    {
        moveCursorToPosition(startColumn, startRow + 3 + i);
        string index = to_string(i + 1); // Get the menu index as a string
        cout << "| "
             << setw(3) << left << index
             << "| " << Color_Yellow
             << setw(maxWidth - 4) << left << menuItems[i].substr(3) // Skip the "1. ", "2. ", etc.
             << Color_Blue
             << "|\n";
    }
    moveCursorToPosition(startColumn, startRow + menuCount + 3);
    cout << string(maxWidth + 4, '-') << "\n"
         << Color_Reset;

    // Prompt for user input
    moveCursorToPosition(startColumn, startRow + menuCount + 4);
    cout << Color_Green << "Enter your choice: " << Color_Reset;
}

void updateHints(vector<string> &hints)
{
    int option;
    while (true)
    {
        // Display current hints
        int s_rows, s_columns;
        consoleRowAndColumn(s_rows, s_columns);
        clearLines(s_rows - 28, s_rows);
        s_rows = s_rows - 1;
        moveCursorToPosition((s_columns - 27) / 2, (s_rows + 2) / 2);
        cout << "Current Hints: " << endl;
        int jk = (s_rows + 2) / 2 + 1;
        for (size_t i = 0; i < hints.size(); ++i)
        {
            moveCursorToPosition((s_columns - 27) / 2, jk++);
            cout << i + 1 << ". " << hints[i] << endl;
        }

        // Show options
        moveCursorToPosition((s_columns - 27) / 2, jk + 1);
        cout << "Choose an option: " << endl;
        moveCursorToPosition((s_columns - 27) / 2, jk + 2);
        cout << "1. Add a Hint" << endl;
        moveCursorToPosition((s_columns - 27) / 2, jk + 3);
        cout << "2. Change a Hint" << endl;
        moveCursorToPosition((s_columns - 27) / 2, jk + 4);
        cout << "3. Delete a Hint" << endl;
        moveCursorToPosition((s_columns - 27) / 2, jk + 5);
        cout << "4. Save and Exit" << endl;
        moveCursorToPosition((s_columns - 27) / 2, jk + 6);
        cout << "Enter your choice: ";
        cin >> option;

        if (option == 1)
        {
            // Add a hint
            string newHint;
            moveCursorToPosition((s_columns - 27) / 2, jk + 7);
            cout << "Enter the new hint: ";
            cin.ignore(); // To clear the input buffer
            getline(cin, newHint);
            hints.push_back(newHint);
            moveCursorToPosition((s_columns - 27) / 2, jk + 8);
            cout << "Hint added successfully!" << endl;
        }
        else if (option == 2)
        {
            // Modify an existing hint
            int hintIndex;
            moveCursorToPosition((s_columns - 27) / 2, jk + 7);
            cout << "Enter the index of the hint to change: ";
            cin >> hintIndex;

            if (hintIndex > 0 && hintIndex <= hints.size())
            {
                string updatedHint;
                moveCursorToPosition((s_columns - 27) / 2, jk + 8);
                cout << "Enter the new hint: ";
                cin.ignore(); // To clear the input buffer
                getline(cin, updatedHint);
                hints[hintIndex - 1] = updatedHint;
                moveCursorToPosition((s_columns - 27) / 2, jk + 9);
                cout << "Hint updated successfully!" << endl;
            }
            else
            {
                moveCursorToPosition((s_columns - 27) / 2, jk + 8);
                cout << "Invalid hint number!" << endl;
            }
        }
        else if (option == 3)
        {
            // Delete a hint
            int hintIndex;
            moveCursorToPosition((s_columns - 27) / 2, jk + 7);
            cout << "Enter the number of the hint to delete: ";
            cin >> hintIndex;

            if (hintIndex > 0 && hintIndex <= hints.size())
            {

                hints.erase(hints.begin() + hintIndex - 1); // Remove the hint
                moveCursorToPosition((s_columns - 27) / 2, jk + 8);
                cout << "Hint deleted successfully!" << endl;
            }
            else
            {
                moveCursorToPosition((s_columns - 27) / 2, jk + 8);
                cout << "Invalid hint number!" << endl;
            }
        }
        else if (option == 4)
        {
            // Save and exit
            moveCursorToPosition((s_columns - 27) / 2, jk + 7);
            cout << "Hints saved successfully!" << endl;
            break;
        }
        else
        {
            moveCursorToPosition((s_columns - 27) / 2, jk + 7);
            cout << "Invalid option! Please try again." << endl;
        }
    }
}

void addDataToFiles(int rows, int columns)
{
    WordDetails newWord;
    rows = rows / 2;
    columns = columns / 2;
    // Automatically assign the next ID
    newWord.id = getLastWordId() + 1;

    // Get word details from the user
    while (true)
    {
        moveCursorToPosition(columns - 18, rows - 3);
        cout << "Enter the word: ";
        getline(cin, newWord.word);
        if (newWord.word.find(' ') != std::string::npos)
        {
            AlertMessage(rows + 5, (columns) / 2, "Error", "The word should not contain any spaces. Please try again.");
        }
        else
        {
            break; // Exit the loop if no spaces are found
        }
    }
    moveCursorToPosition(columns - 18, rows - 2);
    cout << "Enter the level: ";
    cin >> newWord.level;

    newWord.wordLength = newWord.word.length();

    int hintCount;
    moveCursorToPosition(columns - 28, rows - 1);
    cout << "Enter the number of hints: ";
    cin >> hintCount;

    cin.ignore(); // Clear input buffer
    int add_ji = rows;
    for (int i = 0; i < hintCount; ++i)
    {
        string hint;
        moveCursorToPosition(columns - 13, add_ji);
        cout << "Enter hint " << i + 1 << ": ";
        getline(cin, hint);
        newWord.hints.push_back(hint);
    }

    if (addNewWord(newWord))
    {
        moveCursorToPosition(columns - 35, add_ji + 1);
        cout << "Word and hints added successfully!" << endl;
    }
    else
    {
        moveCursorToPosition(columns - 30, add_ji + 1);
        cout << "Failed to add word and hints." << endl;
    }
}

void adminPanel()
{
    while (true)
    {
        int choice;
        displayMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            cout << "\n";
            cout << "\n";
            cout << "\n";
            vector<DISPLAYUSER> A_users = fetchAllUserData();
            displayUserData(A_users);
        }
        else if (choice == 2)
        {
            string name;
            cout << "Enter the name of the user to update: ";
            getline(cin, name);
            // updateUser(name);
        }
        else if (choice == 3)
        {
            string name;
            cout << "Enter the name of the user to search: ";
            getline(cin, name);
            User user = searchUser(name);

            if (user.id != -1)
            {
                printUserDetailsBox(user);
            }
            else
            {
                cout << Color_Red << "User not found.\n"
                     << Color_Reset;
            }
        }
        else if (choice == 4)
        {
            cout << "\n\n";
            displayDataAsTable(getWordScrambleData());
        }
        else if (choice == 5)
        {
            map<int, vector<pair<string, vector<string>>>> dataMap = parseFiles();
            printDataMap(parseFileswithId());
            _getch();
        }
        else if (choice == 6)
        {
            bool exit = true;
            while (exit)
            {
                int s_rows, s_columns;
                consoleRowAndColumn(s_rows, s_columns);
                clearLines(s_rows - 30, s_rows);
                map<int, vector<tuple<int, string, vector<string>>>> dataMap = parseFileswithId();
                int rows, columns;
                consoleRowAndColumn(rows, columns);
                rows = rows / 2;
                clearLines(rows, rows + 10);
                moveCursorToPosition((columns - 64) / 2, rows - 5);
                cout << Color_Cyan << "+-------------------------------------------------------------+";
                moveCursorToPosition((columns - 64) / 2, rows - 4);
                cout << "| " << Color_Bright_White << "Search Word :" << Color_Cyan << "                                               |";
                moveCursorToPosition((columns - 64) / 2, rows - 3);
                cout << "+-------------------------------------------------------------+" << Color_Reset;
                string searcWord;
                moveCursorToPosition((columns - 32) / 2, rows - 4);
                cin >> searcWord;
                while (1)
                {
                    int ans = searchWordAndPrint(dataMap, searcWord);
                    if (ans == 0)
                    {
                        while (true)
                        {
                            try
                            {
                                clearLines(s_rows - 28, s_rows);
                                int opt;
                                WordDetails result = searchWord(dataMap, searcWord);
                                string re_word = result.word;
                                int re_level = result.level;
                                moveCursorToPosition((columns - 27) / 2, rows - 2);
                                cout << "What you want to Update It" << endl;
                                moveCursorToPosition((columns - 27) / 2, rows - 1);
                                cout << " 1. Edit Word" << endl;
                                moveCursorToPosition((columns - 27) / 2, rows);
                                cout << " 2. Edit Level" << endl;
                                moveCursorToPosition((columns - 27) / 2, rows + 1);
                                cout << " 3. Edit Hints" << endl;
                                moveCursorToPosition((columns - 27) / 2, rows + 2);
                                cout << " 4. Back" << endl;
                                moveCursorToPosition((columns - 27) / 2, rows + 3);
                                cout << "Enter Your Choice: ";
                                cin >> opt;
                                if (opt == 1)
                                {
                                    clearLines(s_rows - 28, s_rows);
                                    moveCursorToPosition((columns - 27) / 2, rows + 1);
                                    cout << "Word : " << re_word << endl;
                                    moveCursorToPosition((columns - 27) / 2, rows + 2);
                                    cout << "Enter Your New Word : ";
                                    cin.ignore();
                                    getline(cin, re_word);
                                    if (isWordAvailable(dataMap, re_word))
                                    {
                                        AlertMessage(rows + 5, (columns - 29) / 2, "Error", "This Word Already Available!");
                                        continue;
                                    }
                                    else if (re_word.find(' ') != std::string::npos)
                                    {
                                        AlertMessage(rows + 5, (columns) / 2, "Error", "The word should not contain any spaces. Please try again.");
                                        continue;
                                    }
                                    else
                                    {
                                        updateFilesWithId(result.id, re_word, result.hints, result.level);
                                    }
                                }
                                else if (opt == 2)
                                {
                                    clearLines(s_rows - 28, s_rows);
                                    moveCursorToPosition((columns - 27) / 2, rows + 2);
                                    cout << "Level : " << re_level << endl;
                                    moveCursorToPosition((columns - 27) / 2, rows + 2);
                                    cout << "Enter New level : ";
                                    cin >> re_level;
                                    updateFilesWithId(result.id, result.word, result.hints, re_level);
                                }
                                else if (opt == 3)
                                {
                                    updateHints(result.hints);
                                    updateFilesWithId(result.id, result.word, result.hints, result.level);
                                }
                                else if (opt == 4)
                                {
                                    break;
                                }
                            }
                            catch (const runtime_error &e)
                            {
                                cerr << e.what() << endl;
                            }
                        }
                    }
                    else if (ans == 1)
                    {
                        clearLines(s_rows - 28, s_rows);
                        moveCursorToPosition((columns - 63) / 2, rows - 2);
                        WordDetails result = searchWord(dataMap, searcWord);
                        cout << "Are you sure you want to delete the word '" << result.word << "'? (yes/no): ";
                        string confirmation;
                        cin >> confirmation;

                        // Check user's response
                        if (confirmation == "yes" || confirmation == "y")
                        {
                            string deletedWord = deleteWordById(result.id);

                            if (!deletedWord.empty())
                            {
                                AlertMessage(rows + 5, columns / 2, "Error", "Deleted Word: " + deletedWord);
                                break;
                            }
                            else
                            {
                                AlertMessage(rows + 5, columns / 2, "Error", "No word was deleted. The ID might not exist.");
                                break;
                            }
                        }
                        else
                        {
                            AlertMessage(rows + 5, columns / 2, "Error", "Deletion canceled. The word was not deleted.");
                            break;
                        }
                    }
                    else if (ans == 2)
                    {
                        break;
                    }
                    else if (ans == 3)
                    {
                        exit = false;
                        break;
                    }
                }
            }
        }
        else if (choice == 7)
        {
            int s_rows, s_columns;
            consoleRowAndColumn(s_rows, s_columns);
            clearLines(s_rows - 30, s_rows);
            addDataToFiles(s_rows, s_columns);
            system("cls");
        }
        else if (choice == 8)
        {
            cout << Color_Green << "Exiting admin panel...\n"
                 << Color_Reset;
            system("cls");
            break;
        }
        else
        {
            cout << Color_Red << "Invalid choice. Please try again.\n"
                 << Color_Reset;
            _getch();
            break;
        }
        system("cls");
    }
}
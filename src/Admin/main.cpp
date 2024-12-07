#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <iomanip>
#include "../colors.cpp"

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
        "2. Display All Word Scramble Users",
        "3. Update User",
        "4. Search User",
        "5. Exit"};
    size_t menuCount = sizeof(menuItems) / sizeof(menuItems[0]); // Total number of menu items
    // Determine the width of the table based on the longest item
    size_t maxWidth = title.length();
    for (const string &item : menuItems)
    {
        maxWidth = max(maxWidth, item.length());
    }
    maxWidth += 4;                      // Add padding for aesthetics
    size_t tableHeight = 2 + 1 + menuCount + 1; // Header, divider, items, bottom border

    // Get console dimensions
    int rows, columns;
    consoleRowAndColumn(rows, columns);

    // Calculate starting position for centering
    int startRow = (rows - tableHeight - 10) / 2;
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




using namespace std;

// File names
const string WORD_DATA_FILE = "../game/WordScrumble_Words.txt";
const string HINTS_DATA_FILE = "../game/WordScrumble_Words_Hints.txt";

void addWordScrambleData()
{
    fstream wordFile(WORD_DATA_FILE, ios::app);
    fstream hintsFile(HINTS_DATA_FILE, ios::app);

    if (!wordFile.is_open() || !hintsFile.is_open())
    {
        cout << "Error: Unable to open data files.\n";
        return;
    }

    string word, hint;
    int id, category;

    cout << "Enter the Word ID: ";
    cin >> id;
    cin.ignore();

    cout << "Enter the Word: ";
    getline(cin, word);

    cout << "Enter the Category (1 for easy, 2 for medium, 3 for hard): ";
    cin >> category;
    cin.ignore();

    wordFile << id << "," << word << "," << category << "\n";

    cout << "Enter hints for the word (type 'done' to finish):\n";
    while (true)
    {
        cout << "Hint: ";
        getline(cin, hint);

        if (hint == "done")
            break;

        hintsFile << id << "," << '"' << hint << '"' << "\n";
    }

    cout << "Word and hints added successfully!\n";

    wordFile.close();
    hintsFile.close();
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
            AdmindisplayUsers();
        }
        else if (choice == 2)
        {
            cout << "\n\n";
            displayDataAsTable(getWordScrambleData());
        }
        else if (choice == 3)
        {
            string name;
            cout << "Enter the name of the user to update: ";
            getline(cin, name);
            updateUser(name);
        }
        else if (choice == 4)
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
        else if (choice == 5)
        {
            cout << Color_Green << "Exiting admin panel...\n"
                 << Color_Reset;
            system("cls");
            break;
        }
        else if (choice == 6) // Assuming option 6 is for adding Word Scramble data
        {
            addWordScrambleData();
        }

        else
        {
            cout << Color_Red << "Invalid choice. Please try again.\n"
                 << Color_Reset;
            _getch();
            break;
        }
        _getch();
        system("cls");
    }
}


int main()
{
    adminPanel();
        
        return 0;
}    
    

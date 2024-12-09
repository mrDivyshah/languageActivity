
void Message(int rows, int columns, string type, string msg)
{
    int boxWidth = msg.length() + 8; // Adding padding to message box
    int boxHeight = 3, key;          // Top border, message row, bottom border
    cout << Color_Bright_Green;
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

int Homergame(int rows, int columns, int selected)
{
    int box_column = 42;
    int row = (columns > 125 && rows > 35) ? 20 : 11; // Dynamic row positioning

    while (true)
    {
        clearLines(row - 1, row + gameList.size() + 3);

        moveCursorToPosition((columns - box_column) / 2, row);
        cout << "+-----------------------------------------+";

        moveCursorToPosition((columns - box_column) / 2, row + 1);
        cout << "| [-] Select Game                         |";

        moveCursorToPosition((columns - box_column) / 2, row + 2);
        cout << "+-----------------------------------------+";

        int count = 0;
        for (const auto &DSgame : gameList)
        {
            moveCursorToPosition((columns - box_column) / 2, row + 3 + count);
            cout << "| ";
            moveCursorToPosition((columns - 34) / 2, row + 3 + count);
            cout << (selected == count ? Color_Green + ">> " : Color_Bright_Black + "   ") << DSgame.name << Color_Reset;
            moveCursorToPosition((columns + 41) / 2, row + 3 + count);
            cout << " |";
            count++;
        }

        moveCursorToPosition((columns - box_column) / 2, row + 3 + count);
        cout << "+-----------------------------------------+";

        int key = _getch(); // Capture key press
        if (key == 224)
        {                   // Arrow keys
            key = _getch(); // Get specific key
            if (key == 72)  // Up arrow
                selected = (selected - 1 + gameList.size()) % gameList.size();
            else if (key == 80) // Down arrow
                selected = (selected + 1) % gameList.size();
        }
        else if (key == 13)
        { // Enter key
            return selected;
        }
    }
}

void clearScreen(int rows, int columns)
{
    for (int i = 0; i < rows; ++i)
    {
        cout << "\033[" << (i + 1) << ";1H";
        cout << "\033[K";
    }
}

void printCenteredMessage(int rows, int columns, const string &message)
{
    int row = rows / 2;
    int col = (columns - message.length()) / 2;
    moveCursorToPosition(col, row);
    cout << message;
}

bool printCenteredConfirmation(int rows, int columns, const string &message)
{
    int row = rows / 2;
    int col = (columns - message.length()) / 2;
    moveCursorToPosition(col, row);
    cout << message;

    char choice;
    cin >> choice;
    if (choice != 'y' && choice != 'Y')
    {
        return false;
    }
    else
    {
        return true;
    }
}

int verifyPassword(int rows, int columns, User &userData)
{
    clearScreen(rows, columns);
    ThemeFormat(rows, columns);
    moveCursorToPosition((columns - 20) / 2, rows / 2);
    cout << "Enter Your Password: ";
    string password;
    getline(cin, password);
    if (password != userData.password)
    {
        moveCursorToPosition((columns - 20) / 2, rows / 2 + 2);
        cout << Color_Red << "Incorrect Password!" << Color_Reset;
        _getch();
        return false;
    }
    else
    {
        return true;
    }
}

void UpdateUsernameMenu(int rows, int columns, User &userData)
{
    if (verifyPassword(rows, columns, userData))
    {
        clearScreen(rows, columns);
        ThemeFormat(rows, columns);
        moveCursorToPosition((columns - 20) / 2, rows / 2);
        cout << "Enter New Username: ";
        string newUsername;
        moveCursorToPosition(((columns - 20) / 2) + 20, rows / 2);
        getline(cin, newUsername);
        User existingUser = searchUser(newUsername);
        if (existingUser.id != -1)
        {
            AlertMessage(rows + 2, columns / 2, "Error", "Username Already Taken");
        }
        else
        {
            word_username_changes(userData.id, newUsername);
            sentence_username_changes(userData.id, newUsername);
            fill_username_changes(userData.id, newUsername);
            updateUsername(userData.id, newUsername);
            userData.name = newUsername;

            Message((rows / 2) + 3, columns / 2, "Success", "Username Updated Successfully");
        }
    }
    else
    {
        clearScreen(rows, columns);
        ThemeFormat(rows, columns);
        moveCursorToPosition((columns - 20) / 2, rows / 2);
        cout << "password is wrong ";
    }
}

void ChangePasswordMenu(int rows, int columns, User &userData)
{
    bool xaa;
    string newPassword = "";
    if (verifyPassword(rows, columns, userData))
    {
        clearScreen(rows, columns);
        ThemeFormat(rows, columns);
        moveCursorToPosition((columns - 20) / 2, rows / 2);
        cout << "Enter New Password: ";

        moveCursorToPosition(((columns - 20) / 2) + 20, rows / 2);
        getline(cin, newPassword);
        if (newPassword.length() <= 6)
        {
            AlertMessage((rows / 2) + 3, columns / 2, "Error", "Password Too Short");
        }
        else
        {
            clearScreen(rows, columns);
            ThemeFormat(rows, columns);
            moveCursorToPosition((columns - 20) / 2, rows / 2);
            xaa = printCenteredConfirmation(rows, columns, "Are you sure you want to change your password? (y/n): ");
            if (xaa)
            {
                updatePassword(userData.id, newPassword);
                userData.password = newPassword;

                Message((rows / 2) + 3, columns / 2, "Success", "Password Updated Successfully");
                return;
            }

            else
            {
                AlertMessage((rows / 2) + 3, columns / 2, "Error", "You selected No");
                cout << "Entd " << xaa;
                _getch();
            }
        }
    }
}

void ResetAllGamesMenu(int rows, int columns, User &userData)
{
    verifyPassword(rows, columns, userData);
    clearScreen(rows, columns);
    ThemeFormat(rows, columns);
    clearScreen(rows, columns);
    ThemeFormat(rows, columns);
    moveCursorToPosition((columns - 20) / 2, rows / 2);
    printCenteredConfirmation(rows, columns, "Are you sure you want to reset all games? (y/n): ");
    updateSenData(userData.id, userData.name, 1, 0, 10);
    updateFillintheData(userData.id, userData.name, 1, 0, 10);
    updateWordScrambleData(userData.id, userData.name, 1, 0, 10);
    AlertMessage(rows + 2, columns / 2, "Success", "All Games Reset Successfully");
}

void ResetParticularGameMenu(int rows, int columns, User &userData)
{
    verifyPassword(rows, columns, userData);
    clearScreen(rows, columns);
    ThemeFormat(rows, columns);
    int gameIndex = Homergame(rows, columns, 0);
    if (gameIndex < gameList.size())
    {
        clearScreen(rows, columns);
        ThemeFormat(rows, columns);
        moveCursorToPosition((columns - 20) / 2, rows / 2);
        printCenteredConfirmation(rows, columns, "Are you sure you want to reset this game? (y/n): ");
        switch (gameIndex)
        {
        case 0: // Sentence Scramble
            updateSenData(userData.id, userData.name, 1, 0, 10);
            break;
        case 1: // Grammar Game
            // Logic for resetting Grammar Game
            break;
        case 2: // Fill In the blanks
            updateFillintheData(userData.id, userData.name, 1, 0, 10);
            break;
        case 3: // Word Scramble
            updateWordScrambleData(userData.id, userData.name, 1, 0, 10);
            break;
        }
        clearScreen(rows, columns);
        ThemeFormat(rows, columns);
        moveCursorToPosition((columns - 20) / 2, rows / 2);
        AlertMessage(rows / 2, (columns - 20) / 2, "Success", "Game Reset Successfully");
    }
}

void ManageUserDataMenu(int rows, int columns, User &userData)
{
    int selected = 0;                                 // Currently selected option
    int menuCount = 5;                                // Total number of menu options
    int box_column = 42;                              // Width of the menu box
    int row = (columns > 125 && rows > 35) ? 20 : 11; // Dynamic row positioning

    while (true)
    {
        clearScreen(rows, columns);
        ThemeFormat(rows, columns);

        // Draw menu box
        moveCursorToPosition((columns - box_column) / 2, row);
        cout << "+-----------------------------------------+";

        moveCursorToPosition((columns - box_column) / 2, row + 1);
        cout << "| [-] Manage User Data                    |";

        moveCursorToPosition((columns - box_column) / 2, row + 2);
        cout << "+-----------------------------------------+";

        // Menu options
        string menuOptions[] = {
            "Update Username",
            "Change Password",
            "Reset All Games",
            "Reset Particular Game",
            "Back"};

        for (int i = 0; i < menuCount; i++)
        {
            moveCursorToPosition((columns - box_column) / 2, row + 3 + i);
            cout << "| ";
            moveCursorToPosition((columns - 32) / 2, row + 3 + i);
            cout << (selected == i ? Color_Green + ">> " : Color_Bright_Black + "   ") << menuOptions[i] << Color_Reset;
            moveCursorToPosition((columns + 41) / 2, row + 3 + i);
            cout << " |";
        }

        moveCursorToPosition((columns - box_column) / 2, row + 3 + menuCount);
        cout << "+-----------------------------------------+";

        // Get user input for navigation
        int key = _getch(); // Capture key press
        if (key == 224)
        {                   // Arrow keys
            key = _getch(); // Get specific key
            if (key == 72)  // Up arrow
                selected = (selected - 1 + menuCount) % menuCount;
            else if (key == 80) // Down arrow
                selected = (selected + 1) % menuCount;
        }
        else if (key == 13)
        { // Enter key
            // Handle menu option selection
            switch (selected)
            {
            case 0:

                UpdateUsernameMenu(rows, columns, userData);
                break;
            case 1:
                ChangePasswordMenu(rows, columns, userData);
                break;
            case 2:
                ResetAllGamesMenu(rows, columns, userData);
                break;
            case 3:
                ResetParticularGameMenu(rows, columns, userData);
                break;
            case 4:
                return; // Back to main menu
            }
        }
    }
}

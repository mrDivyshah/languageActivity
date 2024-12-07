int Homergame(int rows, int columns, int selected) {
    int box_column = 42;
    int row = (columns > 125 && rows > 35) ? 20 : 11; // Dynamic row positioning

    while (true) {
        clearLines(row - 1, row + gameList.size() + 3);

        moveCursorToPosition((columns - 43) / 2, row);
        cout << "+";
        for (int i = 0; i <= box_column - 2; i++)
            cout << "-";
        cout << "+";

        moveCursorToPosition((columns - 43) / 2, row + 1);
        cout << "|";
        moveCursorToPosition((columns - 32) / 2, row + 1);
        cout << "[-] Select Game";
        moveCursorToPosition((columns + 41) / 2, row + 1);
        cout << "|";

        moveCursorToPosition((columns - 43) / 2, row + 2);
        cout << "+-----------------------------------------+";

        int count = 0;
        for (const auto &DSgame : gameList) {
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

        int key = _getch(); // Capture key press
        if (key == 224) { // Arrow keys
            key = _getch(); // Get specific key
            if (key == 72) // Up arrow
                selected = (selected - 1 + gameList.size()) % gameList.size();
            else if (key == 80) // Down arrow
                selected = (selected + 1) % gameList.size();
        } else if (key == 13) { // Enter key
            return selected;
        }
    }
}

void ManageUserDataMenu(int rows, int columns, User userData) {
    int selected = 0; // Currently selected option
    int menuCount = 5; // Total number of menu options
    int box_column = 42; // Width of the menu box
    int row = (columns > 125 && rows > 35) ? 20 : 11; // Dynamic row positioning

    while (true) {
        clearLines(rows - 12, rows + 12);

        // Draw menu box
        moveCursorToPosition((columns - 43) / 2, row);
        cout << "+";
        for (int i = 0; i <= box_column - 2; i++)
            cout << "-";
        cout << "+";

        moveCursorToPosition((columns - 43) / 2, row + 1);
        cout << "|";
        moveCursorToPosition((columns - 32) / 2, row + 1);
        cout << "[-] Manage User Data";
        moveCursorToPosition((columns + 41) / 2, row + 1);
        cout << "|";

        moveCursorToPosition((columns - 43) / 2, row + 2);
        cout << "+-----------------------------------------+";

        // Menu options
        string menuOptions[] = {
            "Update Username",
            "Change Password",
            "Reset All Games",
            "Reset Particular Game",
            "Back"
        };

        for (int i = 0; i < menuCount; i++) {
            moveCursorToPosition((columns - 43) / 2, row + 3 + i);
            cout << "|";
            moveCursorToPosition((columns - 32) / 2, row + 3 + i);
            cout << (selected == i ? Color_Green + ">> " : Color_Bright_Black + "   ") << menuOptions[i] << Color_Reset;
            moveCursorToPosition((columns + 41) / 2, row + 3 + i);
            cout << "|";
        }

        moveCursorToPosition((columns - 43) / 2, row + 3 + menuCount);
        cout << "+-----------------------------------------+";

        // Get user input for navigation
        int key = _getch(); // Capture key press
        if (key == 224) { // Arrow keys
            key = _getch(); // Get specific key
            if (key == 72) // Up arrow
                selected = (selected - 1 + menuCount) % menuCount;
            else if (key == 80) // Down arrow
                selected = (selected + 1) % menuCount;
        } else if (key == 13) { // Enter key
            // Handle menu option selection
            if (selected == 0) {
                // Update Username
                
                cout << "Enter New Username: ";
                string newUsername;
                cin >> newUsername;
                User existingUser = searchUser(newUsername);
                if (existingUser.id != -1) {
                    AlertMessage(rows + 5, columns / 2, "Error", "Username Already Taken");
                } else {
                           word_username_changes(userData.id, newUsername);
                    sentence_username_changes(userData.id, newUsername);
                    fill_username_changes(userData.id, newUsername);
                    
                    updateUsername(userData.id, newUsername);

                    
                    AlertMessage(rows + 5, columns / 2, "Success", "Username Updated Successfully It will visible when restart the game");
                  
                    
                }
            } else if (selected == 1) {
                
                cout << "Enter New Password: ";
                string newPassword;
                cin >> newPassword;
                if (newPassword.length() <= 6) {
                    AlertMessage(rows + 5, columns / 2, "Error", "Password Too Short");
                } else {
                         

                    updatePassword(userData.id, newPassword);
                    AlertMessage(rows + 5, columns / 2, "Success", "Password Updated Successfully");
                }
            } else if (selected == 2) {
                // Reset All Games
             AlertMessage(rows + 5, columns / 2, "Warning", "All Games will be reset");
                _getch();
                updateSenData(userData.id, userData.name, 1, 0, 10);
                updateFillintheData(userData.id, userData.name, 1, 0, 10);
                updateWordScrambleData(userData.id, userData.name, 1, 0, 10);
                
            } else if (selected == 3) {
                clearLines(rows - 12, rows + 12);
                int gameIndex = Homergame(rows, columns, 0);
                
                if (gameIndex < gameList.size()) {
                    switch (gameIndex) {
                        case 0: // Sentence Scramble
                            updateSenData(userData.id, userData.name, 1, 1, 10);
                            break;
                        case 1: // Grammar Game
                            // Logic for resetting Grammar Game
                            break;
                        case 2: // Fill In the blanks
                            updateFillintheData(userData.id, userData.name, 1, 1, 10);
                            break;
                        case 3: // Word Scramble
                            updateWordScrambleData(userData.id, userData.name, 1, 1, 10);
                            break;
                    }
                    AlertMessage(rows + 5, columns / 2, "Success", "Game Reset Successfully");
                }
            } else if (selected == 4) {
                // Back
                break;
            }
        }
    }
}

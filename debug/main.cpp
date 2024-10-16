#include <iostream>
#include <map>
#include <string>
#include <conio.h>  // For _getch()

using namespace std;

// Define the menu structure using nested maps
map<int, string> mainMenu = {
    {1, "Play Game"},
    {2, "Manage Account"},
    {3, "Exit"}
};

map<int, string> gameSubMenu = {
    {1, "Letter Shuffle"},
    {2, "Hangman"},
    {3, "Word Scramble"},
    {4, "Verb or Noun"}
};

// Function to move the cursor to a specific column and row (ANSI escape code)
void moveCursorToPosition(int columns, int rows) {
    cout << "\033[" << rows << ";" << columns << "H";
}

// Function to render the menu dynamically
void renderMenu(map<int, string>& menuData, int selected, int terminalWidth, int terminalHeight) {
    system("CLS");  // Clear the console

    int boxWidth = 45;  // Fixed width of the box for aesthetics
    int startRow = 5;   // Starting row for the menu

    // Loop through menu items and render them dynamically
    for (auto& item : menuData) {
        string menuItem = item.second;
        int padding = ((boxWidth - menuItem.length()) / 2);

        // Draw top border
        moveCursorToPosition((terminalWidth - boxWidth) / 2, startRow);
        cout << "+";
        for (int i = 0; i < boxWidth - 2; ++i) cout << "-";
        cout << "+";

        // Draw the menu item
        moveCursorToPosition((terminalWidth - boxWidth) / 2, startRow + 1);
        cout << "|";

        if (item.first == selected) {
            // Highlight selected menu item
            cout << string(padding -3, ' ') << ">> " << menuItem << " <<" << string(padding-4, ' ');
        } else {
            cout << string(padding, ' ') << menuItem << string(padding-1, ' ');
        }
        cout << "|";

        // Draw bottom border
        moveCursorToPosition((terminalWidth - boxWidth) / 2, startRow + 2);
        cout << "+";
        for (int i = 0; i < boxWidth - 2; ++i) cout << "-";
        cout << "+";

        startRow += 3;  // Move down for the next menu item
    }
}

// Function to display a specific sub-menu (e.g., games)
void renderGameSubMenu(int terminalWidth, int terminalHeight) {
    int selected = 1;  // First item is selected by default
    while (true) {
        renderMenu(gameSubMenu, selected, terminalWidth, terminalHeight);
        
        // Handle input to navigate through sub-menu
        int key = _getch();
        if (key == 224) { // Arrow keys
            key = _getch();
            if (key == 72) { // Up Arrow
                selected = (selected == 1) ? gameSubMenu.size() : selected - 1;
            } else if (key == 80) { // Down Arrow
                selected = (selected == gameSubMenu.size()) ? 1 : selected + 1;
            }
        } else if (key == 13) { // Enter key
            system("CLS");
            cout << "You selected: " << gameSubMenu[selected] << endl;
            _getch();
            break;
        } else if (key == 27) { // Escape key to go back
            break;
        }
    }
}

// Main function to render the primary menu and handle navigation
int main() {
    int terminalWidth = 80;  // Example terminal width
    int terminalHeight = 24; // Example terminal height
    int selected = 1;        // Default selected menu item

    while (true) {
        renderMenu(mainMenu, selected, terminalWidth, terminalHeight);

        // Capture key input for navigation
        int key = _getch();
        if (key == 224) { // Arrow keys are detected
            key = _getch(); // Read the second byte for arrow keys
            if (key == 72) { // Up Arrow
                selected = (selected == 1) ? mainMenu.size() : selected - 1;
            } else if (key == 80) { // Down Arrow
                selected = (selected == mainMenu.size()) ? 1 : selected + 1;
            }
        } else if (key == 13) { // Enter key is pressed
            // Handle different menu selections
            if (selected == 1) { // Play Game selected
                renderGameSubMenu(terminalWidth, terminalHeight);
            } else if (selected == 2) { // Manage Account selected
                system("CLS");
                cout << "Manage Account selected!" << endl;
                _getch(); // Wait for user input
            } else if (selected == 3) { // Exit selected
                system("CLS");
                cout << "Exiting the program..." << endl;
                break; // Exit the program
            }
        }
    }

    return 0;
}

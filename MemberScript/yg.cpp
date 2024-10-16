#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include <iomanip>
#include <map>

using namespace std;

const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";

// Helper functions for UI
void displayText(const string &text, const string &color) {
    cout << color << text << RESET << endl;
}

void drawHeader(const string &header) {
    cout << BOLD << CYAN;
    cout << "=============================" << endl;
    cout << "   " << header << endl;
    cout << "=============================" << RESET << endl;
}

// Function to create a border-like visual
void drawBorder() {
    cout << BOLD << MAGENTA << "-------------------------------------" << RESET << endl;
}



// Function to clear the screen (Cross-platform)
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Store and validate login credentials using file system
map<string, string> userCredentials;

void loadCredentials() {
    ifstream file("users.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string username, password;
        ss >> username >> password;
        userCredentials[username] = password;
    }
    file.close();
}

void saveCredentials() {
    ofstream file("users.txt", ios::trunc);
    for (const auto &[username, password] : userCredentials) {
        file << username << " " << password << endl;
    }
    file.close();
}

// Dummy password encryption (for demo purposes only)
string encryptPassword(const string &password) {
    string encrypted = password;
    for (char &ch : encrypted)
        ch += 2;  // Simple Caesar Cipher
    return encrypted;
}

bool loginUser() {
    string username, password;
    displayText("Enter Username: ", GREEN);
    cin >> username;
    displayText("Enter Password: ", GREEN);
    cin >> password;

    if (userCredentials.find(username) != userCredentials.end()) {
        if (userCredentials[username] == encryptPassword(password)) {
            displayText("Login successful!", GREEN);
            return true;
        } else {
            displayText("Incorrect password!", RED);
        }
    } else {
        displayText("User not found!", RED);
    }
    return false;
}

void registerUser() {
    string username, password;
    displayText("Create Username: ", GREEN);
    cin >> username;
    if (userCredentials.find(username) != userCredentials.end()) {
        displayText("User already exists!", RED);
        return;
    }
    displayText("Create Password: ", GREEN);
    cin >> password;
    userCredentials[username] = encryptPassword(password);
    saveCredentials();
    displayText("Registration successful!", GREEN);
}

// Games
void wordScramble() {
    clearScreen();  // Clear the screen before starting the game
    drawHeader("Word Scramble Game");

    // List of words to be scrambled
    vector<string> words = {"programming", "terminal", "keyboard", "computer", "cplusplus"};
    
    // Random engine to shuffle the word
    random_device rd;  // Seed for random number generation
    mt19937 g(rd());   // Standard mersenne_twister_engine

    int score = 0;  // Initialize score
    for (int i = 0; i < 5; ++i) {
        // Select a random word from the list
        string word = words[rand() % words.size()];
        string scrambled = word;  // Create a scrambled version of the word
        shuffle(scrambled.begin(), scrambled.end(), g);  // Shuffle the word

        // Display the scrambled word to the player
        displayText("Scrambled word: " + scrambled, YELLOW);
        
        string guess;  // Variable to store the player's guess
        displayText("Your guess: ", BLUE);
        cin >> guess;  // Get the player's guess

        // Check if the guess is correct
        if (guess == word) {
            displayText("Correct!", GREEN);  // Inform the player of the correct guess
            score += 10;  // Increase score
        } else {
            displayText("Wrong! The correct word was: " + word, RED);  // Inform the player of the correct word
        }
    }

    // Display the final score after 5 attempts
    displayText("Your final score: " + to_string(score), BOLD + GREEN);
    drawBorder();  // Draw a border after the game ends
}


void verbOrNoun() {
    clearScreen();
    drawHeader("Verb or Noun Game");

    map<string, string> words = {{"run", "verb"}, {"apple", "noun"}, {"jump", "verb"}, {"table", "noun"}};
    int score = 0;

    for (int i = 0; i < 5; ++i) {
        auto it = words.begin();
        advance(it, rand() % words.size());
        string word = it->first;
        string type = it->second;

        displayText("Is '" + word + "' a verb or noun? (v/n): ", YELLOW);
        char answer;
        cin >> answer;

        if ((answer == 'v' && type == "verb") || (answer == 'n' && type == "noun")) {
            displayText("Correct!", GREEN);
            score += 10;
        } else {
            displayText("Wrong!", RED);
        }
    }

    displayText("Your final score: " + to_string(score), BOLD + GREEN);
    drawBorder();
}

void hangman() {
    clearScreen();
    drawHeader("Hangman Game");

    vector<string> words = {"hangman", "game", "terminal", "program"};
    string word = words[rand() % words.size()];

    string guessed(word.size(), '_');
    int lives = 6;

    while (lives > 0 && guessed != word) {
        displayText("Word: " + guessed, YELLOW);
        displayText("Lives remaining: " + to_string(lives), RED);

        char guess;
        displayText("Enter a letter: ", GREEN);
        cin >> guess;

        bool correct = false;
        for (size_t i = 0; i < word.size(); ++i) {
            if (word[i] == guess) {
                guessed[i] = guess;
                correct = true;
            }
        }

        if (!correct) {
            --lives;
        }
    }

    if (guessed == word) {
        displayText("You won! The word was: " + word, GREEN);
    } else {
        displayText("Game over! The word was: " + word, RED);
    }

    drawBorder();
}

// Main Menu
void mainMenu() {
    while (true) {
        clearScreen();
        drawHeader("Main Menu");
        displayText("1. Word Scramble\n2. Verb or Noun\n3. Hangman\n4. Exit", CYAN);
        displayText("Select an option (1-4): ", BLUE);

        char choice = _getch();  // Use getch() for single-char input

        switch (choice) {
            case '1':
                wordScramble();
                break;
            case '2':
                verbOrNoun();
                break;
            case '3':
                hangman();
                break;
            case '4':
                exit(0);
            default:
                displayText("Invalid option. Try again.", RED);
        }
        getchar();  // Pause after each game
    }
}

int main() {
    loadCredentials();

    while (true) {
        clearScreen();
        drawHeader("Word Wise Terminal");
        displayText("1. Login\n2. Register\n3. Exit", CYAN);
        displayText("Select an option (1-3): ", BLUE);

        char option = getch();

        switch (option) {
            case '1':
                if (loginUser()) {
                    mainMenu();
                }
                break;
            case '2':
                registerUser();
                break;
            case '3':
                exit(0);
            default:
                displayText("Invalid option. Try again.", RED);
        }
    }

    return 0;
}
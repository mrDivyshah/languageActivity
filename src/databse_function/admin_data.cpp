#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iomanip>
// #include "src/game/WordScramble.cpp"
#include "../game/WordScramble.cpp"

// #define A_USER_DATABASE getCurrentDirectory() + "/database/user.txt"
// #define A_Fillinthe getCurrentDirectory() + "/database/fillinUser.txt"
// #define A_Sen getCurrentDirectory() + "/database/CrossWords_User.txt"
// #define A_WordScramble getCurrentDirectory() + "/database/WordScramble.txt"

#define A_USER_DATABASE "D:/cpp project/languageActivity/database/user.txt"
#define A_Fillinthe "D:/cpp project/languageActivity/database/fillinUser.txt"
#define A_Sen "D:/cpp project/languageActivity/database/CrossWords_User.txt"
#define A_WordScramble "D:/cpp project/languageActivity/database/WordScramble.txt"

using namespace std;

struct DISPLAYUSER
{
    int id;
    string joiningDate;
    string name;

    struct WordScrambleData
    {
        string lastPlayedDate;
        int level;
        int score;
        int coin;
    } wordScramble;

    struct SenData
    {
        string lastPlayedDate;
        int level;
        int score;
        int coin;
    } sen;

    struct FillintheData
    {
        string modifyingTimestamp;
        string lastPlayedDate;
        int level;
        int score;
        int coin;
    } fillinthe;

    string password;
};

// Function to split a comma-separated string
vector<string> splitCSV(const string &line)
{
    vector<string> tokens;
    stringstream ss(line);
    string token;

    while (getline(ss, token, ','))
    {
        tokens.push_back(token);
    }

    return tokens;
}

// Function to safely convert a string to an integer
int safe_stoi(const string &str)
{
    try
    {
        return stoi(str);
    }
    catch (const invalid_argument &e)
    {
        cerr << "Error: Invalid number format: " << str << endl;
        return -1; // Return a default invalid value
    }
    catch (const out_of_range &e)
    {
        cerr << "Error: Out of range number: " << str << endl;
        return -1;
    }
}

// Function to fetch all user data
vector<DISPLAYUSER> fetchAllUserData()
{
    vector<DISPLAYUSER> users;

    // Open the user file
    ifstream userFile(A_USER_DATABASE);
    if (!userFile)
    {
        cerr << "Error: Could not open user database file." << endl;
        return users;
    }

    // Read general user data
    string line;
    while (getline(userFile, line))
    {
        vector<string> tokens = splitCSV(line);
        if (tokens.size() < 4)
        {
            cerr << "Error: Incorrect format in user database." << endl;
            continue;
        }

        DISPLAYUSER user;
        user.id = safe_stoi(tokens[0]);
        user.joiningDate = tokens[1];
        user.name = tokens[2];
        user.password = tokens[3];

        users.push_back(user);
    }
    userFile.close();

    // Open Fillinthe data file
    ifstream fillinFile(A_Fillinthe);
    if (!fillinFile)
    {
        cerr << "Error: Could not open Fillinthe database file." << endl;
    }
    else
    {
        int i = 0;
        while (getline(fillinFile, line) && i < users.size())
        {
            vector<string> tokens = splitCSV(line);
            if (tokens.size() < 7)
            {
                cerr << "Error: Incorrect format in Fillinthe database." << endl;
                continue;
            }
            users[i].fillinthe.modifyingTimestamp = tokens[1];
            users[i].fillinthe.lastPlayedDate = tokens[2];
            users[i].fillinthe.level = safe_stoi(tokens[4]);
            users[i].fillinthe.score = safe_stoi(tokens[5]);
            users[i].fillinthe.coin = safe_stoi(tokens[6]);
            i++;
        }
        fillinFile.close();
    }

    // Open Sen (CrossWords) data file
    ifstream senFile(A_Sen);
    if (!senFile)
    {
        cerr << "Error: Could not open Sen database file." << endl;
    }
    else
    {
        int i = 0;
        while (getline(senFile, line) && i < users.size())
        {
            vector<string> tokens = splitCSV(line);
            if (tokens.size() < 6)
            {
                cerr << "Error: Incorrect format in Sen database." << endl;
                continue;
            }
            users[i].sen.lastPlayedDate = tokens[2];
            users[i].sen.level = safe_stoi(tokens[4]);
            users[i].sen.score = safe_stoi(tokens[5]);
            users[i].sen.coin = safe_stoi(tokens[6]);
            i++;
        }
        senFile.close();
    }

    // Open WordScramble data file
    ifstream wordScrambleFile(A_WordScramble);
    if (!wordScrambleFile)
    {
        cerr << "Error: Could not open WordScramble database file." << endl;
    }
    else
    {
        int i = 0;
        while (getline(wordScrambleFile, line) && i < users.size())
        {
            vector<string> tokens = splitCSV(line);
            if (tokens.size() < 6)
            {
                cerr << "Error: Incorrect format in WordScramble database." << endl;
                continue;
            }
            users[i].wordScramble.lastPlayedDate = tokens[2];
            users[i].wordScramble.level = safe_stoi(tokens[4]);
            users[i].wordScramble.score = safe_stoi(tokens[5]);
            users[i].wordScramble.coin = safe_stoi(tokens[6]);
            i++;
        }
        wordScrambleFile.close();
    }

    return users;
}

// Function to display user data
// Function to display user data
void displayUserData(const vector<DISPLAYUSER> &users)
{
    // Find the maximum width for each column dynamically
    int userIdWidth = 5;
    int joiningDateWidth = 12;
    int nameWidth = 10;
    int passwordWidth = 10;
    int fillintheTimestampWidth = 15;
    int fillintheLevelWidth = 6;
    int fillintheScoreWidth = 6;
    int fillintheCoinWidth = 6;
    int senLastPlayedWidth = 15;
    int senLevelWidth = 6;
    int senScoreWidth = 6;
    int senCoinWidth = 6;
    int wordScrambleLastPlayedWidth = 15;
    int wordScrambleLevelWidth = 6;
    int wordScrambleScoreWidth = 6;
    int wordScrambleCoinWidth = 6;

    // Loop through users and find the maximum length for each column
    for (const auto &user : users)
    {
        userIdWidth = max(static_cast<size_t>(userIdWidth), to_string(user.id).length());
        joiningDateWidth = max(static_cast<size_t>(joiningDateWidth), user.joiningDate.length());
        nameWidth = max(static_cast<size_t>(nameWidth), user.name.length());
        passwordWidth = max(static_cast<size_t>(passwordWidth), user.password.length());
        fillintheTimestampWidth = max(static_cast<size_t>(fillintheTimestampWidth), user.fillinthe.modifyingTimestamp.length());
        fillintheLevelWidth = max(static_cast<size_t>(fillintheLevelWidth), to_string(user.fillinthe.level).length());
        fillintheScoreWidth = max(static_cast<size_t>(fillintheScoreWidth), to_string(user.fillinthe.score).length());
        fillintheCoinWidth = max(static_cast<size_t>(fillintheCoinWidth), to_string(user.fillinthe.coin).length());
        senLastPlayedWidth = max(static_cast<size_t>(senLastPlayedWidth), user.sen.lastPlayedDate.length());
        senLevelWidth = max(static_cast<size_t>(senLevelWidth), to_string(user.sen.level).length());
        senScoreWidth = max(static_cast<size_t>(senScoreWidth), to_string(user.sen.score).length());
        senCoinWidth = max(static_cast<size_t>(senCoinWidth), to_string(user.sen.coin).length());
        wordScrambleLastPlayedWidth = max(static_cast<size_t>(wordScrambleLastPlayedWidth), user.wordScramble.lastPlayedDate.length());
        wordScrambleLevelWidth = max(static_cast<size_t>(wordScrambleLevelWidth), to_string(user.wordScramble.level).length());
        wordScrambleScoreWidth = max(static_cast<size_t>(wordScrambleScoreWidth), to_string(user.wordScramble.score).length());
        wordScrambleCoinWidth = max(static_cast<size_t>(wordScrambleCoinWidth), to_string(user.wordScramble.coin).length());
    }

    // Add some padding to each column width
    userIdWidth += 4;
    joiningDateWidth += 4;
    nameWidth += 4;
    passwordWidth += 4;
    fillintheTimestampWidth += 4;
    fillintheLevelWidth += 4;
    fillintheScoreWidth += 4;
    fillintheCoinWidth += 4;
    senLastPlayedWidth += 4;
    senLevelWidth += 4;
    senScoreWidth += 4;
    senCoinWidth += 4;
    wordScrambleLastPlayedWidth += 4;
    wordScrambleLevelWidth += 4;
    wordScrambleScoreWidth += 4;
    wordScrambleCoinWidth += 4;

    // Print the header row with dynamic column widths
    cout << left
         << setw(userIdWidth) << "User"
         << setw(joiningDateWidth) << "Joining Date"
         << setw(nameWidth) << "Name"
         << setw(passwordWidth) << "Password"
         << Color_Bright_Blue << setw(fillintheTimestampWidth) << "Fill L_Played"
         << setw(fillintheLevelWidth) << "Level"
         << setw(fillintheScoreWidth) << "Score"
         << setw(fillintheCoinWidth) << "Coin"
         << Color_Bright_Cyan << setw(senLastPlayedWidth) << "CrossWord L_Played"
         << setw(senLevelWidth) << "Level"
         << setw(senScoreWidth) << "Score"
         << setw(senCoinWidth) << "Coin"
         << Color_Bright_Blue << setw(wordScrambleLastPlayedWidth) << "WS L_Played"
         << setw(wordScrambleLevelWidth) << "Level"
         << setw(wordScrambleScoreWidth) << "Score"
         << setw(wordScrambleCoinWidth) << "Coin"
         << Color_Reset << endl;

    cout << string(userIdWidth + joiningDateWidth + nameWidth + passwordWidth + fillintheTimestampWidth + fillintheLevelWidth +
                       fillintheScoreWidth + fillintheCoinWidth + senLastPlayedWidth + senLevelWidth + senScoreWidth +
                       senCoinWidth + wordScrambleLastPlayedWidth + wordScrambleLevelWidth + wordScrambleScoreWidth +
                       wordScrambleCoinWidth,
                   '-')
         << endl;

    for (const auto &user : users)
    {
        cout << left
             << setw(userIdWidth) << user.id
             << setw(joiningDateWidth) << user.joiningDate
             << setw(nameWidth) << user.name
             << setw(passwordWidth) << user.password
             << Color_Bright_Blue << setw(fillintheTimestampWidth) << user.fillinthe.modifyingTimestamp
             << setw(fillintheLevelWidth) << user.fillinthe.level
             << setw(fillintheScoreWidth) << user.fillinthe.score
             << setw(fillintheCoinWidth) << user.fillinthe.coin
             << Color_Bright_Cyan << setw(senLastPlayedWidth) << user.sen.lastPlayedDate
             << setw(senLevelWidth) << user.sen.level
             << setw(senScoreWidth) << user.sen.score
             << setw(senCoinWidth) << user.sen.coin
             << Color_Bright_Blue << setw(wordScrambleLastPlayedWidth) << user.wordScramble.lastPlayedDate
             << setw(wordScrambleLevelWidth) << user.wordScramble.level
             << setw(wordScrambleScoreWidth) << user.wordScramble.score
             << setw(wordScrambleCoinWidth) << user.wordScramble.coin
             << Color_Reset << endl;
    }
}

// int main() {
//     vector<DISPLAYUSER> users = fetchAllUserData();
//     displayUserData(users);
//     return 0;
// }

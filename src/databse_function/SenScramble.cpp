#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include "../time.cpp"
#include "../colors.cpp"

using namespace std;

#define SenScramble "../../database/sentenceUser.txt"
// #define SenScramble "D:/cpp project/languageActivity/database/WordScramble.txt"

struct SenScrambleData {
    int UserId;
    string Timestamp;
    string modifyingTimestamp;
    string name;
    int level;
    int score;
    int coin;
};

// Add Data 
void addSenScrambleData(int userId, const string name, int level, int score, int coin)
{
    ofstream file;
    SenScrambleData data;
    data.UserId = userId;
    data.Timestamp = getTime();
    data.modifyingTimestamp = data.Timestamp;
    data.name = name;
    data.level = level;
    data.score = score;
    data.coin = coin;
    file.open(SenScramble, ios::app);
    if (!file.is_open())
    {
        cerr << "Failed to open the file." << endl;
    }

    // Write the data to the file
    file << data.UserId << ","
         << data.Timestamp << ","
         << data.modifyingTimestamp << ","
         << data.name << ","
         << data.level << ","
         << data.score << ","
         << data.coin << endl;

    file.close();
}

// Update Data
void updateSenScrambleData(int userId, const string name, int newLevel, int newScore, int newCoin)
{
    ifstream inFile(SenScramble);
    if (!inFile.is_open())
    {
        cerr << "Failed to open the file for reading." << endl;
        return;
    }

    vector<SenScrambleData> dataEntries;
    string line;

    while (getline(inFile, line))
    {
        stringstream ss(line);
        SenScrambleData data;
        string userIdStr, levelStr, scoreStr, coinStr;

        getline(ss, userIdStr, ',');
        getline(ss, data.Timestamp, ',');
        getline(ss, data.modifyingTimestamp, ',');
        getline(ss, data.name, ',');
        getline(ss, levelStr, ',');
        getline(ss, scoreStr, ',');
        getline(ss, coinStr, ',');

        data.UserId = stoi(userIdStr);
        data.level = stoi(levelStr);
        data.score = stoi(scoreStr);
        data.coin = stoi(coinStr);

        if (data.UserId == userId && data.name == name)
        {
            data.level = newLevel;
            data.score = newScore;
            data.coin = newCoin;
            data.modifyingTimestamp = getTime();
        }

        dataEntries.push_back(data);
    }
    inFile.close();

    ofstream outFile(SenScramble);
    if (!outFile.is_open())
    {
        cerr << "Failed to open the file for writing." << endl;
        return;
    }

    for (const auto &entry : dataEntries)
    {
        outFile << entry.UserId << ","
                << entry.Timestamp << ","
                << entry.modifyingTimestamp << ","
                << entry.name << ","
                << entry.level << ","
                << entry.score << ","
                << entry.coin << endl;
    }
    outFile.close();
}

// Get Data
vector<SenScrambleData> getSenScrambleData()
{
    vector<SenScrambleData> dataEntries;
    ifstream inFile(SenScramble);

    if (!inFile.is_open())
    {
        cerr << "Failed to open the file for reading." << endl;
        return dataEntries; 
    }

    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        SenScrambleData data;
        string userIdStr, levelStr, scoreStr, coinStr;

        getline(ss, userIdStr, ',');
        getline(ss, data.Timestamp, ',');
        getline(ss, data.modifyingTimestamp, ',');
        getline(ss, data.name, ',');
        getline(ss, levelStr, ',');
        getline(ss, scoreStr, ',');
        getline(ss, coinStr, ',');

        data.UserId = stoi(userIdStr);
        data.level = stoi(levelStr);
        data.score = stoi(scoreStr);
        data.coin = stoi(coinStr);

        dataEntries.push_back(data);
    }

    inFile.close();
    return dataEntries; 
}

// Display Data In Table
void displayDataAsTable(const vector<SenScrambleData> &dataEntries)
{
    const int widthId = 8;
    const int widthTimestamp = 25;
    const int widthModifyingTimestamp = 25;
    const int widthName = 20;
    const int widthLevel = 8;
    const int widthScore = 10;
    const int widthCoin = 8;
    int count = 0;
    cout << Color_Green << left << setw(widthId) << "UserId"
         << setw(widthTimestamp) << "Timestamp"
         << setw(widthModifyingTimestamp) << "Modifying Timestamp"
         << setw(widthName) << "Name"
         << setw(widthLevel) << "Level"
         << setw(widthScore) << "Score"
         << setw(widthCoin) << "Coin"
         << endl;

    cout << Color_Bright_Black << string(widthId + widthTimestamp + widthModifyingTimestamp + widthName + widthLevel + widthScore + widthCoin, '-') << endl;

    for (const auto &entry : dataEntries)
    {
        count++;
        cout << (count % 2 == 0 ? Color_Blue : Color_Cyan);
        cout << left << setw(widthId) << entry.UserId
             << setw(widthTimestamp) << entry.Timestamp
             << setw(widthModifyingTimestamp) << entry.modifyingTimestamp
             << setw(widthName) << entry.name
             << (count % 2 == 0 ? Color_Blue : Color_Cyan) << setw(widthLevel) << entry.level
             << setw(widthScore) << entry.score
             << setw(widthCoin) << entry.coin
             << Color_Reset + Color_Background_Default
             << endl;
    }
}

// Delete Data
void deleteSenScrambleData(int userId, const string &name)
{
    vector<SenScrambleData> dataEntries = getSenScrambleData();
    bool userFound = false;

    auto it = remove_if(dataEntries.begin(), dataEntries.end(),
                        [&](const SenScrambleData &entry) {
                            return entry.UserId == userId && entry.name == name;
                        });

    if (it != dataEntries.end())
    {
        dataEntries.erase(it, dataEntries.end());
        userFound = true;
    }

    if (!userFound)
    {
        cout << "User not found in the database." << endl;
        return;
    }

    ofstream outFile(SenScramble);
    if (!outFile.is_open())
    {
        cerr << "Failed to open the file for writing." << endl;
        return;
    }

    for (const auto &entry : dataEntries)
    {
        outFile << entry.UserId << ","
                << entry.Timestamp << ","
                << entry.modifyingTimestamp << ","
                << entry.name << ","
                << entry.level << ","
                << entry.score << ","
                << entry.coin << endl;
    }
    outFile.close();

    cout << "User deleted successfully." << endl;
}

// find single user data
SenScrambleData getSingleUserSenScrambleData(int userId, const string &name)
{
    vector<SenScrambleData> dataEntries = getSenScrambleData();
    for (const auto &entry : dataEntries)
    {
        if (entry.UserId == userId && entry.name == name)
        {
            return entry; 
        }
    }
    cout << "User not found in the database." << endl;
    return SenScrambleData{-1, "", "", "", 0, 0, 0}; 
}

// fefkewfnjanajkfwnfjnfijnfnibifnew WordScumble Database  jefjkwebfiwebfdasjkdfevasasfeqj
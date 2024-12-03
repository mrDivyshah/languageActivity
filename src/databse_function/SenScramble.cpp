 #include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;

#define Sen getCurrentDirectory() + "/database/sentenceUser.txt"
// #define Sen "D:/cpp project/languageActivity/database/Sen.txt"

struct SenData {
    int UserId;
    string Timestamp;
    string modifyingTimestamp;
    string name;
    int level;
    int score;
    int coin;
};

// Add Data 
void addSenData(int userId, const string name, int level, int score, int coin)
{
    ofstream file;
    SenData data;
    data.UserId = userId;
    data.Timestamp = getTime();
    data.modifyingTimestamp = data.Timestamp;
    data.name = name;
    data.level = level;
    data.score = score;
    data.coin = coin;
    file.open(Sen, ios::app);
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
void updateSenData(int userId, const string name, int newLevel, int newScore, int newCoin)
{
    ifstream inFile(Sen);
    if (!inFile.is_open())
    {
        cerr << "Failed to open the file for reading." << endl;
        return;
    }

    vector<SenData> dataEntries;
    string line;

    while (getline(inFile, line))
    {
        stringstream ss(line);
        SenData data;
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

    ofstream outFile(Sen);
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
vector<SenData> getSenData()
{
    vector<SenData> dataEntries;
    ifstream inFile(Sen);

    if (!inFile.is_open())
    {
        cerr << "Failed to open the file for reading." << endl;
        return dataEntries; 
    }

    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        SenData data;
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
void displayDataAsTable(const vector<SenData> &dataEntries)
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
void deleteSenData(int userId, const string &name)
{
    vector<SenData> dataEntries = getSenData();
    bool userFound = false;

    auto it = remove_if(dataEntries.begin(), dataEntries.end(),
                        [&](const SenData &entry) {
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

    ofstream outFile(Sen);
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
SenData getSingleUserSenData(int userId, const string &name)
{
    vector<SenData> dataEntries = getSenData();
    for (const auto &entry : dataEntries)
    {
        if (entry.UserId == userId && entry.name == name)
        {
            return entry; 
        }
    }
    cout << "User not found in the database." << endl;
    return SenData{-1, "", "", "", 0, 0, 0}; 
}

// fefkewfnjanajkfwnfjnfijnfnibifnew WordScumble Database  jefjkwebfiwebfdasjkdfevasasfeqj
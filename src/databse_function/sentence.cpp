#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include "../time.cpp"  // Assuming you have a function for time retrieval
#include "../colors.cpp"  // Assuming you have color formatting for console output

using namespace std;

#define SentenceSCM getCurrentDirectory() + "/database/SentenceSCM.txt"

struct SentenceSCMData {
    int UserId;
    string Timestamp;
    string modifyingTimestamp;
    string sentence;
    int level;
    int score;
    int coin;
};

// Add Data
void addSentenceSCMData(int userId, const string &sentence, int level, int score, int coin) {
    ofstream file;
    SentenceSCMData data;
    data.UserId = userId;
    data.Timestamp = getTime();
    data.modifyingTimestamp = data.Timestamp;
    data.sentence = sentence;
    data.level = level;
    data.score = score;
    data.coin = coin;
    file.open(SentenceSCM, ios::app);
    if (!file.is_open()) {
        cerr << "Failed to open the file." << endl;
    }

    // Write the data to the file
    file << data.UserId << ","
         << data.Timestamp << ","
         << data.modifyingTimestamp << ","
         << data.sentence << ","
         << data.level << ","
         << data.score << ","
         << data.coin << endl;

    file.close();
}

// Update Data
void updateSentenceSCMData(int userId, const string &sentence, int newLevel, int newScore, int newCoin) {
    ifstream inFile(SentenceSCM);
    if (!inFile.is_open()) {
        cerr << "Failed to open the file for reading." << endl;
        return;
    }

    vector<SentenceSCMData> dataEntries;
    string line;

    while (getline(inFile, line)) {
        stringstream ss(line);
        SentenceSCMData data;
        string userIdStr, levelStr, scoreStr, coinStr;

        getline(ss, userIdStr, ',');
        getline(ss, data.Timestamp, ',');
        getline(ss, data.modifyingTimestamp, ',');
        getline(ss, data.sentence, ',');
        getline(ss, levelStr, ',');
        getline(ss, scoreStr, ',');
        getline(ss, coinStr, ',');

        data.UserId = stoi(userIdStr);
        data.level = stoi(levelStr);
        data.score = stoi(scoreStr);
        data.coin = stoi(coinStr);

        if (data.UserId == userId && data.sentence == sentence) {
            data.level = newLevel;
            data.score = newScore;
            data.coin = newCoin;
            data.modifyingTimestamp = getTime();
        }

        dataEntries.push_back(data);
    }
    inFile.close();

    ofstream outFile(SentenceSCM);
    if (!outFile.is_open()) {
        cerr << "Failed to open the file for writing." << endl;
        return;
    }

    for (const auto &entry : dataEntries) {
        outFile << entry.UserId << ","
                << entry.Timestamp << ","
                << entry.modifyingTimestamp << ","
                << entry.sentence << ","
                << entry.level << ","
                << entry.score << ","
                << entry.coin << endl;
    }
    outFile.close();
}

// Get Data
vector<SentenceSCMData> getSentenceSCMData() {
    vector<SentenceSCMData> dataEntries;
    ifstream inFile(SentenceSCM);

    if (!inFile.is_open()) {
        cerr << "Failed to open the file for reading." << endl;
        return dataEntries; 
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        SentenceSCMData data;
        string userIdStr, levelStr, scoreStr, coinStr;

        getline(ss, userIdStr, ',');
        getline(ss, data.Timestamp, ',');
        getline(ss, data.modifyingTimestamp, ',');
        getline(ss, data.sentence, ',');
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
void displayDataAsTable(const vector<SentenceSCMData> &dataEntries) {
    const int widthId = 8;
    const int widthTimestamp = 25;
    const int widthModifyingTimestamp = 25;
    const int widthSentence = 30;
    const int widthLevel = 8;
    const int widthScore = 10;
    const int widthCoin = 8;
    int count = 0;
    cout << Color_Green << left << setw(widthId) << "UserId"
         << setw(widthTimestamp) << "Timestamp"
         << setw(widthModifyingTimestamp) << "Modifying Timestamp"
         << setw(widthSentence) << "Sentence"
         << setw(widthLevel) << "Level"
         << setw(widthScore) << "Score"
         << setw(widthCoin) << "Coin"
         << endl;

    cout << Color_Bright_Black << string(widthId + widthTimestamp + widthModifyingTimestamp + widthSentence + widthLevel + widthScore + widthCoin, '-') << endl;

    for (const auto &entry : dataEntries) {
        count++;
        cout << (count % 2 == 0 ? Color_Blue : Color_Cyan);
        cout << left << setw(widthId) << entry.UserId
             << setw(widthTimestamp) << entry.Timestamp
             << setw(widthModifyingTimestamp) << entry.modifyingTimestamp
             << setw(widthSentence) << entry.sentence
             << (count % 2 == 0 ? Color_Blue : Color_Cyan) << setw(widthLevel) << entry.level
             << setw(widthScore) << entry.score
             << setw(widthCoin) << entry.coin
             << Color_Reset + Color_Background_Default
             << endl;
    }
}

// Delete Data
void deleteSentenceSCMData(int userId, const string &sentence) {
    vector<SentenceSCMData> dataEntries = getSentenceSCMData();
    bool userFound = false;

    auto it = remove_if(dataEntries.begin(), dataEntries.end(),
                        [&](const SentenceSCMData &entry) {
                            return entry.UserId == userId && entry.sentence == sentence;
                        });

    if (it != dataEntries.end()) {
        dataEntries.erase(it, dataEntries.end());
        userFound = true;
    }

    if (!userFound) {
        cout << "User not found in the database." << endl;
        return;
    }

    ofstream outFile(SentenceSCM);
    if (!outFile.is_open()) {
        cerr << "Failed to open the file for writing." << endl;
        return;
    }

    for (const auto &entry : dataEntries) {
        outFile << entry.UserId << ","
                << entry.Timestamp << ","
                << entry.modifyingTimestamp << ","
                << entry.sentence << ","
                << entry.level << ","
                << entry.score << ","
                << entry.coin << endl;
    }
    outFile.close();

    cout << "User deleted successfully." << endl;
}

// Find single user data
SentenceSCMData getSingleUserSentenceSCMData(int userId, const string &sentence) {
    vector<SentenceSCMData> dataEntries = getSentenceSCMData();
    for (const auto &entry : dataEntries) {
        if (entry.UserId == userId && entry.sentence == sentence) {
            return entry; 
        }
    }
    cout << "User not found in the database." << endl;
    return SentenceSCMData(); 
}


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

 
 
#define sen getCurrentDirectory() + "/database/sen.txt"
// #define WordScramble "D:/cpp project/languageActivity/database/sen.txt"

// Structure for Sentence Scramble Data
struct senData {
    int UserId;
    string Timestamp;
    string modifyingTimestamp;
    string sentence;
    int level;
    int score;
    int coin;
};

// Helper function to scramble a sentence
string scrambleSentence(const string &sentence) {
    vector<string> words;
    stringstream ss(sentence);
    string word;
    
    while (ss >> word) {
        words.push_back(word);
    }

    // Shuffle the words randomly
    random_device rd;
    mt19937 g(rd());
    shuffle(words.begin(), words.end(), g);

    string scrambledSentence;
    for (const string &w : words) {
        scrambledSentence += w + " ";
    }
    scrambledSentence.pop_back(); // Remove the trailing space
    return scrambledSentence;
}

// Add Sentence Scramble Data
void addsenData(int userId, const string &sentence, int level, int score, int coin)
{
    ofstream file;
    senData data;
    data.UserId = userId;
    data.Timestamp = getTime();
    data.modifyingTimestamp = data.Timestamp;
    data.sentence = scrambleSentence(sentence); // Scramble the sentence before storing
    data.level = level;
    data.score = score;
    data.coin = coin;

    file.open(sen, ios::app);
    if (!file.is_open()) {
        cerr << "Failed to open the file." << endl;
        return;
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

// Update Sentence Scramble Data
void updatesenData(int userId, const string &sentence, int newLevel, int newScore, int newCoin)
{
    ifstream inFile(sen);
    if (!inFile.is_open()) {
        cerr << "Failed to open the file for reading." << endl;
        return;
    }

    vector<senData> dataEntries;
    string line;

    while (getline(inFile, line)) {
        stringstream ss(line);
        senData data;
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

    ofstream outFile(sen);
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

// Get Sentence Scramble Data
vector<senData> getsenData()
{
    vector<senData> dataEntries;
    ifstream inFile(sen);

    if (!inFile.is_open()) {
        cerr << "Failed to open the file for reading." << endl;
        return dataEntries; 
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        senData data;
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

// Display Sentence Scramble Data
void displaysenDataAsTable(const vector<senData> &dataEntries)
{
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
         << setw(widthSentence) << "Scrambled Sentence"
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

// Delete Sentence Scramble Data
void deletesenData(int userId, const string &sentence)
{
    vector<senData> dataEntries = getsenData();
    bool userFound = false;

    auto it = remove_if(dataEntries.begin(), dataEntries.end(),
                        [&](const senData &entry) {
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

    ofstream outFile(sen);
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

    cout << "Sentence data deleted successfully." << endl;
}

// Find a Single User's Scrambled Sentence Data
senData getSingleUsersenData(int userId, const string &sentence)
{
    vector<senData> dataEntries = getsenData();
    for (const auto &entry : dataEntries) {
        if (entry.UserId == userId && entry.sentence == sentence) {
            return entry; 
        }
    }
    cout << "User not found in the database." << endl;
    return senData{-1, "", "", "", 0, 0, 0}; 
}

//int main() {
//    // Sample test calls
//    addsenData(1, "Hello world this is a test", 1, 100, 10);
//    vector<senData> data = getsenData();
//    displaysenDataAsTable(data);
//    return 0;
//}


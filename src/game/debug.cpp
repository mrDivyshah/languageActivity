#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>  // For setting width and formatting the table
#include <algorithm>

using namespace std;

#define HintsFile "D:/cpp project/languageActivity/src/game/WordScrumble_Words_Hints.txt"
#define WordsFile "D:/cpp project/languageActivity/src/game/WordScrumble_Words.txt"

map<int, vector<pair<string, vector<string>>>> parseFiles() {
    map<int, vector<pair<string, vector<string>>>> dataMap;

    // Read hints from the file
    ifstream hintsInput(HintsFile);
    if (!hintsInput) {
        cerr << "Error: Unable to open hints file: " << HintsFile << endl;
        return dataMap;
    }

    string line;
    map<int, vector<string>> hints;
    while (getline(hintsInput, line)) {
        istringstream iss(line);
        string idStr, hint;

        // Read ID and hint
        if (getline(iss, idStr, ',') && getline(iss, hint, ',')) {
            int id = stoi(idStr);
            hint.erase(0, hint.find_first_not_of(" \""));
            hint.erase(hint.find_last_not_of(" \"") + 1); // Trim quotes and spaces
            hints[id].push_back(hint);
        } else {
            cerr << "Error parsing hint line: " << line << endl;
        }
    }
    hintsInput.close();

    // Debug: Print loaded hints
    // for (const auto &hintEntry : hints) {
    //     cout << "Hint ID: " << hintEntry.first << " | Hints: ";
    //     for (const string &hint : hintEntry.second) {
    //         cout << "\"" << hint << "\" ";
    //     }
    //     cout << endl;
    // }

    // Read words from the file
    ifstream wordsInput(WordsFile);
    if (!wordsInput) {
        cerr << "Error: Unable to open words file: " << WordsFile << endl;
        return dataMap;
    }

    while (getline(wordsInput, line)) {
        istringstream iss(line);
        string idStr, word, levelStr;

        // Read ID, word, and level
        if (getline(iss, idStr, ',') && getline(iss, word, ',') && getline(iss, levelStr, ',')) {
            int id = stoi(idStr);
            int level = stoi(levelStr);

            word.erase(0, word.find_first_not_of(" \""));
            word.erase(word.find_last_not_of(" \"") + 1); // Trim quotes and spaces

            if (hints.find(id) != hints.end()) {
                dataMap[level].push_back({word, hints[id]});
            } else {
                cerr << "Warning: No hints found for word ID: " << id << endl;
            }
        } else {
            cerr << "Error parsing word line: " << line << endl;
        }
    }
    wordsInput.close();

    // Debug: Print loaded dataMap
    // for (const auto &levelEntry : dataMap) {
    //     cout << "Level: " << levelEntry.first << endl;
    //     for (const auto &wordEntry : levelEntry.second) {
    //         cout << "  Word: " << wordEntry.first << " | Hints: ";
    //         for (const string &hint : wordEntry.second) {
    //             cout << "\"" << hint << "\" ";
    //         }
    //         cout << endl;
    //     }
    // }

    return dataMap;
}


// Function to trim spaces and quotes from a string
string trim(const string& str)
{
    size_t start = str.find_first_not_of(" \"");
    size_t end = str.find_last_not_of(" \"");
    return (start == string::npos || end == string::npos) ? "" : str.substr(start, end - start + 1);
}

// Function to update files based on new map and word ID and return old/new data
map<string, map<string, string>> updateFiles(int wordId, const map<string, string>& updatedData)
{
    map<string, map<string, string>> changes; // Store old and new data for the word ID

    // Load hints from file
    ifstream hintsInput(HintsFile);
    ofstream hintsOutput("temp_hints.txt"); // Temporary file to write updated hints
    if (!hintsInput || !hintsOutput)
    {
        cerr << "Error: Unable to open hints file." << endl;
        return changes;
    }

    string line;
    while (getline(hintsInput, line))
    {
        istringstream iss(line);
        string idStr, hint;
        if (getline(iss, idStr, ',') && getline(iss, hint, ','))
        {
            int id = stoi(trim(idStr));
            hint = trim(hint);

            if (id == wordId && updatedData.find("hint") != updatedData.end())
            {
                // Store old data
                changes["old"]["hint"] = hint;
                // Write updated data
                hintsOutput << id << ", " << updatedData.at("hint") << endl;
                // Store new data
                changes["new"]["hint"] = updatedData.at("hint");
            }
            else
            {
                // Write the line as is if not updating
                hintsOutput << id << ", " << hint << endl;
            }
        }
    }
    hintsInput.close();
    hintsOutput.close();
    rename("temp_hints.txt", HintsFile.c_str()); // Replace original file with updated file

    // Load words from file
    ifstream wordsInput(WordsFile);
    ofstream wordsOutput("temp_words.txt"); // Temporary file to write updated words
    if (!wordsInput || !wordsOutput)
    {
        cerr << "Error: Unable to open words file." << endl;
        return changes;
    }

    while (getline(wordsInput, line))
    {
        istringstream iss(line);
        string idStr, word, levelStr;
        if (getline(iss, idStr, ',') && getline(iss, word, ',') && getline(iss, levelStr, ','))
        {
            int id = stoi(trim(idStr));
            word = trim(word);
            levelStr = trim(levelStr);

            if (id == wordId)
            {
                // Store old data
                changes["old"]["word"] = word;
                changes["old"]["level"] = levelStr;

                // Write updated data if available
                string newWord = updatedData.count("word") ? updatedData.at("word") : word;
                string newLevel = updatedData.count("level") ? updatedData.at("level") : levelStr;

                wordsOutput << id << ", " << newWord << ", " << newLevel << endl;

                // Store new data
                changes["new"]["word"] = newWord;
                changes["new"]["level"] = newLevel;
            }
            else
            {
                // Write the line as is if not updating
                wordsOutput << id << ", " << word << ", " << levelStr << endl;
            }
        }
    }
    wordsInput.close();
    wordsOutput.close();
    rename("temp_words.txt", WordsFile.c_str()); // Replace original file with updated file

    return changes;
}

int main()
{
    int wordId;
    cout << "Enter word ID to update: ";
    cin >> wordId;

    map<string, string> updatedData;
    string input;

    cout << "Enter new word (or leave blank to keep unchanged): ";
    cin.ignore();
    getline(cin, input);
    if (!input.empty())
        updatedData["word"] = input;

    cout << "Enter new hint (or leave blank to keep unchanged): ";
    getline(cin, input);
    if (!input.empty())
        updatedData["hint"] = input;

    cout << "Enter new level (or leave blank to keep unchanged): ";
    getline(cin, input);
    if (!input.empty())
        updatedData["level"] = input;

    // Update files and retrieve changes
    map<string, map<string, string>> changes = updateFiles(wordId, updatedData);

    // Print changes
    cout << "\nOld Data:\n";
    for (const auto& item : changes["old"])
    {
        cout << item.first << ": " << item.second << endl;
    }

    cout << "\nNew Data:\n";
    for (const auto& item : changes["new"])
    {
        cout << item.first << ": " << item.second << endl;
    }

    return 0;
}

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip> // For setting width and formatting the table
#include <stdexcept>

using namespace std;

#define HintsFile getCurrentDirectory() + "/src/game/WordScrumble_Words_Hints.txt"
#define WordsFile getCurrentDirectory() + "/src/game/WordScrumble_Words.txt"
struct WordDetails
{
    int id;
    string word;
    int level;
    int wordLength;
    vector<string> hints;
};

// txt file to map parseing
map<int, vector<pair<string, vector<string>>>> parseFiles()
{
    map<int, vector<pair<string, vector<string>>>> dataMap;

    // Read hints from the file
    ifstream hintsInput(HintsFile);
    if (!hintsInput)
    {
        cerr << "Error: Unable to open hints file: " << HintsFile << endl;
        return dataMap;
    }

    string line;
    map<int, vector<string>> hints;
    while (getline(hintsInput, line))
    {
        istringstream iss(line);
        string idStr, hint;

        // Read ID and hint
        if (getline(iss, idStr, ',') && getline(iss, hint, ','))
        {
            int id = stoi(idStr);
            hint.erase(0, hint.find_first_not_of(" \""));
            hint.erase(hint.find_last_not_of(" \"") + 1); // Trim quotes and spaces
            hints[id].push_back(hint);
        }
        else
        {
            cerr << "Error parsing hint line: " << line << endl;
        }
    }
    hintsInput.close();


    ifstream wordsInput(WordsFile);
    if (!wordsInput)
    {
        cerr << "Error: Unable to open words file: " << WordsFile << endl;
        return dataMap;
    }

    while (getline(wordsInput, line))
    {
        istringstream iss(line);
        string idStr, word, levelStr;

        // Read ID, word, and level
        if (getline(iss, idStr, ',') && getline(iss, word, ',') && getline(iss, levelStr, ','))
        {
            int id = stoi(idStr);
            int level = stoi(levelStr);

            word.erase(0, word.find_first_not_of(" \""));
            word.erase(word.find_last_not_of(" \"") + 1); // Trim quotes and spaces

            if (hints.find(id) != hints.end())
            {
                dataMap[level].push_back({word, hints[id]});
            }
            else
            {
                cerr << "Warning: No hints found for word ID: " << id << endl;
            }
        }
        else
        {
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

map<int, vector<tuple<int, string, vector<string>>>> parseFileswithId()
{
    map<int, vector<tuple<int, string, vector<string>>>> dataMap;
    ifstream hintsInput(HintsFile);
    if (!hintsInput)
    {
        cerr << "Error: Unable to open hints file: " << HintsFile << endl;
        return dataMap;
    }
    string line;
    map<int, vector<string>> hints;
    while (getline(hintsInput, line))
    {
        istringstream iss(line);
        string idStr, hint;
        if (getline(iss, idStr, ',') && getline(iss, hint, ','))
        {
            int id = stoi(idStr);
            hint.erase(0, hint.find_first_not_of(" \""));
            hint.erase(hint.find_last_not_of(" \"") + 1); 
            hints[id].push_back(hint);
        }
        else
        {
            cerr << "Error parsing hint line: " << line << endl;
        }
    }
    hintsInput.close();
    ifstream wordsInput(WordsFile);
    if (!wordsInput)
    {
        cerr << "Error: Unable to open words file: " << WordsFile << endl;
        return dataMap;
    }
    while (getline(wordsInput, line))
    {
        istringstream iss(line);
        string idStr, word, levelStr;
        if (getline(iss, idStr, ',') && getline(iss, word, ',') && getline(iss, levelStr, ','))
        {
            int id = stoi(idStr);
            int level = stoi(levelStr);

            word.erase(0, word.find_first_not_of(" \""));
            word.erase(word.find_last_not_of(" \"") + 1); 

            if (hints.find(id) != hints.end())
            {
                dataMap[level].push_back(make_tuple(id, word, hints[id]));
            }
            else
            {
                cerr << "Warning: No hints found for word ID: " << id << endl;
            }
        }
        else
        {
            cerr << "Error parsing word line: " << line << endl;
        }
    }
    wordsInput.close();

    return dataMap;
}

void appendWordToFile(int id, const string &word, int level)
{
    ofstream wordsOutput(WordsFile, ios::app);
    if (!wordsOutput)
    {
        cerr << "Error: Unable to open words file for appending: " << WordsFile << endl;
        return;
    }
    wordsOutput << id << ", " << word << ", " << level << endl;
    wordsOutput.close();
}

void appendHintToFile(int wordId, const vector<string> &hintsList)
{
    ofstream hintsOutput(HintsFile, ios::app);
    if (!hintsOutput)
    {
        cerr << "Error: Unable to open hints file for appending: " << HintsFile << endl;
        return;
    }

    for (const auto &hint : hintsList)
    {
        hintsOutput << wordId << ", \"" << hint << "\"" << endl;
    }
    hintsOutput.close();
}

void printVocabulary(const map<int, vector<pair<string, vector<string>>>> &vocabulary)
{
    for (const auto &levelEntry : vocabulary)
    {
        int level = levelEntry.first;
        cout << "Level: " << level << "\n";

        for (const auto &wordHintsPair : levelEntry.second)
        {
            const string &word = wordHintsPair.first;
            const vector<string> &hints = wordHintsPair.second;

            cout << "  Word: " << word << "\n";
            cout << "  Word Length (letters): " << word.length() << "\n";
            cout << "  Total Hints: " << hints.size() << "\n";
            cout << "  Hints:\n";
            for (size_t i = 0; i < hints.size(); ++i)
            {
                cout << "    " << i + 1 << ". " << hints[i] << "\n";
            }
        }
        cout << "\n";
    }
    cout << "Data not found";
}

void printDataMap(const map<int, vector<tuple<int, string, vector<string>>>> &dataMap)
{
    string separator = " -  - ";
    size_t maxLevelWidth = 5; // Default width for Level column
    size_t maxIdWidth = 3;    // Default width for ID column
    size_t maxWordWidth = 0;  // To find the maximum word length
    size_t maxHintsWidth = 0; // To find the maximum hints length

    // Iterate over the map to calculate the maximum widths
    for (const auto &levelEntry : dataMap)
    {
        for (const auto &wordHintsTuple : levelEntry.second)
        {
            int id;
            string word;
            vector<string> hints;

            // Unpack the tuple
            tie(id, word, hints) = wordHintsTuple;

            string hintsConcatenated;
            for (const string &hint : hints)
            {
                hintsConcatenated += hint + separator;
            }
            if (!hintsConcatenated.empty())
                hintsConcatenated.pop_back(), hintsConcatenated.pop_back();

            maxIdWidth = max(maxIdWidth, to_string(id).length());
            maxWordWidth = max(maxWordWidth, word.length());
            maxHintsWidth = max(maxHintsWidth, hintsConcatenated.length());
        }
    }

    // Add extra space for the headers
    maxIdWidth = max(maxIdWidth, string("ID").length());
    maxWordWidth = max(maxWordWidth, string("Words").length());
    maxHintsWidth = max(maxHintsWidth, string("Hints").length());

    // Calculate the total width and height of the table
    size_t totalWidth = maxLevelWidth + 2 + maxIdWidth + 2 + maxWordWidth + 2 + maxHintsWidth + 2;
    size_t totalHeight = dataMap.size() * 2 + 4; // 2 lines per row (one for data and one for separator)

    // Print the header with dynamic column width
    cout << "+" << string(maxLevelWidth + 2, '-')
         << "+" << string(maxIdWidth + 2, '-')
         << "+" << string(maxWordWidth + 2, '-')
         << "+" << string(maxHintsWidth + 2, '-')
         << "+" << endl;

    cout << "| " << setw(maxLevelWidth) << "Level"
         << " | " << setw(maxIdWidth) << "ID"
         << " | " << setw(maxWordWidth) << "Words"
         << " | " << setw(maxHintsWidth) << "Hints"
         << " |" << endl;

    cout << "+" << string(maxLevelWidth + 2, '-')
         << "+" << string(maxIdWidth + 2, '-')
         << "+" << string(maxWordWidth + 2, '-')
         << "+" << string(maxHintsWidth + 2, '-')
         << "+" << endl;

    // Iterate through the dataMap and print each entry dynamically
    for (const auto &levelEntry : dataMap)
    {
        for (const auto &wordHintsTuple : levelEntry.second)
        {
            int id;
            string word;
            vector<string> hints;

            // Unpack the tuple
            tie(id, word, hints) = wordHintsTuple;

            string hintsConcatenated;
            for (const string &hint : hints)
            {
                hintsConcatenated += hint + separator;
            }
            if (!hintsConcatenated.empty())
                hintsConcatenated.pop_back(), hintsConcatenated.pop_back();

            // Print each row dynamically based on the calculated widths
            cout << "| " << setw(maxLevelWidth) << levelEntry.first
                 << " | " << setw(maxIdWidth) << id
                 << " | " << setw(maxWordWidth) << word
                 << " | " << setw(maxHintsWidth) << hintsConcatenated
                 << " |" << endl;
        }
        cout << "+" << string(maxLevelWidth + 2, '-')
             << "+" << string(maxIdWidth + 2, '-')
             << "+" << string(maxWordWidth + 2, '-')
             << "+" << string(maxHintsWidth + 2, '-')
             << "+" << endl;
    }

    // cout << "+" << string(maxLevelWidth + 2, '-')
    //      << "+" << string(maxIdWidth + 2, '-')
    //      << "+" << string(maxWordWidth + 2, '-')
    //      << "+" << string(maxHintsWidth + 2, '-')
    //      << "+" << endl;
}

int getLastWordId()
{
    ifstream wordsInput(WordsFile);
    if (!wordsInput)
    {
        cerr << "Error: Unable to open words file: " << WordsFile << endl;
        return 0;
    }

    string line;
    int lastId = 0;

    while (getline(wordsInput, line))
    {
        istringstream iss(line);
        string idStr;
        if (getline(iss, idStr, ','))
        {
            lastId = stoi(idStr); // Update lastId with the latest ID
        }
    }
    wordsInput.close();
    return lastId;
}

bool addNewWord(const WordDetails &wordDetails) {
    ofstream wordsOutput(WordsFile, ios::app);
    if (!wordsOutput)     {
        cerr << "Error: Unable to open words file for writing: " << WordsFile << endl;
        return false;
    }
    wordsOutput << wordDetails.id << ", \"" << wordDetails.word << "\", " << wordDetails.level << "\n";
    wordsOutput.close();
    ofstream hintsOutput(HintsFile, ios::app);
    if (!hintsOutput)     {
        cerr << "Error: Unable to open hints file for writing: " << HintsFile << endl;
        return false;
    }
    for (const auto &hint : wordDetails.hints)     {
        hintsOutput << wordDetails.id << ", \"" << hint << "\"\n";
    }
    hintsOutput.close();
    return true;
}

void updateFilesWithId(int wordId, const string &newWord, const vector<string> &newHints, int newLevel) {
    map<int, vector<string>> hints;
    ifstream hintsInput(HintsFile);
    if (!hintsInput)     {
        cerr << "Error: Unable to open hints file: " << HintsFile << endl;
        return;
    }
    string line;
    while (getline(hintsInput, line))     {
        istringstream iss(line);
        string idStr, hint;
        if (getline(iss, idStr, ',') && getline(iss, hint, ','))  {
            int id = stoi(idStr);
            hint.erase(0, hint.find_first_not_of(" \""));
            hint.erase(hint.find_last_not_of(" \"") + 1);
            hints[id].push_back(hint);
        }else {
            cerr << "Error parsing hint line: " << line << endl;
        }   }
    hintsInput.close();
    map<int, pair<string, int>> words;
    ifstream wordsInput(WordsFile);
    if (!wordsInput) {
        cerr << "Error: Unable to open words file: " << WordsFile << endl;
        return;
    }
    while (getline(wordsInput, line)) {
        istringstream iss(line);
        string idStr, word, levelStr;
        if (getline(iss, idStr, ',') && getline(iss, word, ',') && getline(iss, levelStr, ',')) {
            int id = stoi(idStr);
            int level = stoi(levelStr);
            word.erase(0, word.find_first_not_of(" \""));
            word.erase(word.find_last_not_of(" \"") + 1); 
            words[id] = make_pair(word, level);
        } else {
            cerr << "Error parsing word line: " << line << endl;
        }     }
    wordsInput.close();
    if (hints.find(wordId) != hints.end() && words.find(wordId) != words.end()) {
        hints[wordId] = newHints;
        words[wordId] = make_pair(newWord, newLevel);
    } else {
        cerr << "Error: Word ID not found in both files: " << wordId << endl;
        return;
    }
    ofstream hintsOutput(HintsFile);
    if (!hintsOutput) {
        cerr << "Error: Unable to open hints file for writing: " << HintsFile << endl;
        return;
    }
    for (map<int, vector<string>>::iterator it = hints.begin(); it != hints.end(); ++it) {
        for (const string &hint : it->second) {
            hintsOutput << it->first << ",\"" << hint << "\"" << endl;
        }     }
    hintsOutput.close();
    ofstream wordsOutput(WordsFile);
    if (!wordsOutput) {
        cerr << "Error: Unable to open words file for writing: " << WordsFile << endl;
        return;
    }
    for (map<int, pair<string, int>>::iterator it = words.begin(); it != words.end(); ++it) {
        wordsOutput << it->first << ",\"" << it->second.first << "\"," << it->second.second << endl;
    }
    wordsOutput.close();
}

// demo

int searchButtons(int row)
{
    const int LEFT_ARROW = 75;
    const int RIGHT_ARROW = 77;
    const int ENTER_KEY = 13;
    int G_columns, G_rows;
    consoleRowAndColumn(G_rows, G_columns);
    // Calculate button positions based on G_columns
    int firstColumn = G_columns / 8;            // Updated for 4 buttons
    int secondColumn = 3 * (G_columns / 8) - 6; // Adjusted column spacing
    int thirdColumn = 5 * (G_columns / 8) - 9;
    int fourthColumn = 7 * (G_columns / 8) - 12; // fourth button

    int currentSelection = 0; // 0 -> Hint, 1 -> Retry, 2 -> Exit, 3 -> Help
    while (true)
    {
        // Draw the buttons, highlighting the selected one

        // Button 1: Hint
        moveCursorToPosition(firstColumn, row);
        if (currentSelection == 0)
        {
            cout << Color_Yellow << "***********" << Color_Reset;
        }
        else
        {
            cout << "-----------";
        }
        moveCursorToPosition(firstColumn, row + 1);
        cout << "|   EDIT  |";
        moveCursorToPosition(firstColumn, row + 2);
        if (currentSelection == 0)
        {
            cout << Color_Yellow << "***********" << Color_Reset;
        }
        else
        {
            cout << "-----------";
        }

        // Button 2: Retry
        moveCursorToPosition(secondColumn, row);
        if (currentSelection == 1)
        {
            cout << Color_Red << "************" << Color_Reset;
        }
        else
        {
            cout << "------------";
        }
        moveCursorToPosition(secondColumn, row + 1);
        cout << "|  DELETE  |";
        moveCursorToPosition(secondColumn, row + 2);
        if (currentSelection == 1)
        {
            cout << Color_Red << "************" << Color_Reset;
        }
        else
        {
            cout << "------------";
        }

        // Button 3: Exit
        moveCursorToPosition(thirdColumn, row);
        if (currentSelection == 2)
        {
            cout << Color_Blue << "***********" << Color_Reset;
        }
        else
        {
            cout << "-----------";
        }
        moveCursorToPosition(thirdColumn, row + 1);
        cout << "|   NEXT  |";
        moveCursorToPosition(thirdColumn, row + 2);
        if (currentSelection == 2)
        {
            cout << Color_Blue << "***********" << Color_Reset;
        }
        else
        {
            cout << "-----------";
        }

        // Button 4: Help (New Button)
        moveCursorToPosition(fourthColumn, row);
        if (currentSelection == 3)
        {
            cout << Color_Cyan << "***********" << Color_Reset;
        }
        else
        {
            cout << "-----------";
        }
        moveCursorToPosition(fourthColumn, row + 1);
        cout << "|   Back  |";
        moveCursorToPosition(fourthColumn, row + 2);
        if (currentSelection == 3)
        {
            cout << Color_Cyan << "***********" << Color_Reset;
        }
        else
        {
            cout << "-----------";
        }

        // Footer instructions
        string footer = "Use Side Arrow Keys to Navigate Buttons";
        moveCursorToPosition((G_columns - footer.length()) / 2, row + 4);
        cout << Color_Green << footer << Color_Reset;

        // Wait for user input
        int key = _getch();

        // Arrow key handling
        if (key == 224)
        {
            key = _getch(); // Get the actual key code
            if (key == LEFT_ARROW)
            {
                currentSelection = (currentSelection + 3) % 4; // Move left, wrap around
            }
            else if (key == RIGHT_ARROW)
            {
                currentSelection = (currentSelection + 1) % 4; // Move right, wrap around
            }
        }

        // Enter key to confirm selection
        if (key == ENTER_KEY)
        {
            return currentSelection; // Return the selected button
        }
    }
}

void printCentered(const string &text, int width)
{
    if (width <= 0)
    {
        throw invalid_argument("Width must be a positive integer");
    }

    if (text.length() >= width)
    {
        cout << text << endl; // Print the text as is if it's too long for centering
    }
    else
    {
        size_t padding = (width - text.length()) / 2;
        string paddedText = string(min(padding, static_cast<size_t>(1000)), ' ') + text + string(min(static_cast<size_t>(width - text.length() - padding), static_cast<size_t>(1000)), ' ');
        cout << paddedText;
    }
}

int searchWordAndPrint(const map<int, vector<tuple<int, string, vector<string>>>> &dataMap, const string &searchWord)
{
    const int WIDTH = 60; // Width of the table for formatting
    int rows, columns;
    consoleRowAndColumn(rows, columns);

    for (const auto &levelEntry : dataMap)
    {
        for (const auto &wordHintsTuple : levelEntry.second)
        {
            int id;
            string word;
            vector<string> hints;

            // Unpack the tuple
            tie(id, word, hints) = wordHintsTuple;

            // Search for the word
            if (word == searchWord)
            {
                int wordLength = word.length();
                int level = levelEntry.first;
                int totalHints = hints.size();
                clearLines(rows + 20, rows - 20);
                // Print the word details in a dynamic layout
                moveCursorToPosition((columns - WIDTH - 4) / 2, (rows - 2) / 2);
                cout << Color_Bright_Blue << "+=============================================================+" << endl;
                moveCursorToPosition((columns - WIDTH - 4) / 2, (rows) / 2);
                cout << "|" << Color_Yellow;
                printCentered("[ WORD: " + word + " ]", WIDTH);
                cout << Color_Bright_Blue << " |" << endl;
                moveCursorToPosition((columns - WIDTH - 4) / 2, (rows + 3) / 2);
                cout << "+-------------------------------------------------------------+" << endl;
                moveCursorToPosition((columns - WIDTH - 4) / 2, (rows + 5) / 2);
                cout << "|" << Color_Bright_Green;
                printCentered("Word Information", WIDTH);
                cout << Color_Bright_Blue << " |" << endl;
                moveCursorToPosition((columns - WIDTH - 4) / 2, (rows + 7) / 2);
                cout << "+-------------------------------------------------------------+" << endl;
                moveCursorToPosition((columns - WIDTH - 4) / 2, (rows + 9) / 2);
                cout << "| " << left << Color_Magenta << setw(10) << "Word ID:" << Color_Bright_Blue << setw(18) << id
                     << "| " << left << Color_Magenta << setw(17) << "Word Length:" << Color_Bright_Blue << setw(12) << wordLength << " |" << endl;
                moveCursorToPosition((columns - WIDTH - 4) / 2, (rows + 11) / 2);
                cout << "| " << left << Color_Magenta << setw(10) << "Level:" << Color_Bright_Blue << setw(18) << level
                     << "| " << left << Color_Magenta << setw(17) << "Total Hints:" << Color_Bright_Blue << setw(12) << totalHints << " |" << endl;
                moveCursorToPosition((columns - WIDTH - 4) / 2, (rows + 13) / 2);
                cout << "+-------------------------------------------------------------+" << endl;

                // Display hints in a dynamically adjusted format
                moveCursorToPosition((columns - WIDTH - 4) / 2, (rows + 15) / 2);
                cout << "|" << Color_Green;
                printCentered("*** HINTS FOR " + word + " ***", WIDTH);
                cout << Color_Bright_Blue << " |" << endl;
                // cout << "|            *** HINTS FOR " << word << " ***" << "               |" << endl;
                moveCursorToPosition((columns - WIDTH - 4) / 2, (rows + 17) / 2);
                cout << "+-------------------------------------------------------------+" << endl;
                int ij = 19;
                for (size_t i = 0; i < hints.size(); ++i)
                {
                    // Print each hint in a nice format
                    moveCursorToPosition((columns - WIDTH - 4) / 2, (rows + ij) / 2);
                    cout << "| " << left << Color_Magenta << (i + 1) << ". " << setw(56) << hints[i] << Color_Bright_Blue << " |" << endl;
                    ij = ij + 2;
                }
                moveCursorToPosition((columns - WIDTH - 4) / 2, (rows + ij) / 2);
                cout << "+-------------------------------------------------------------+" << Color_Reset << endl;

                return searchButtons((rows + ij + 4) / 2); // Adjust row position for buttons
            }
        }
    }
    clearLines(rows, rows - 20);
    moveCursorToPosition((columns - WIDTH - 4) / 2, (rows - 2) / 2);
    cout << Color_Red << "+=============================================================+" << endl;
    moveCursorToPosition((columns - WIDTH - 4) / 2, (rows) / 2);
    cout << "|" << Color_White;
    printCentered("Word '" + searchWord + "' not found.", WIDTH);
    cout << Color_Red << " |";
    moveCursorToPosition((columns - WIDTH - 4) / 2, (rows + 3) / 2);
    cout << "+=============================================================+" << Color_Reset << endl;
    _getch();
    return 2;
}

string deleteWordById(int wordId)
{
    map<int, vector<string>> updatedHints;
    vector<string> updatedWords;
    string deletedWord; 
    ifstream hintsInput(HintsFile);
    if (!hintsInput) {
        cerr << "Error: Unable to open hints file: " << HintsFile << endl;
        return "";
    }
    string line;
    while (getline(hintsInput, line)) {
        istringstream iss(line);
        string idStr, hint;
        if (getline(iss, idStr, ',') && getline(iss, hint, ',')) {
            int id = stoi(idStr);
            if (id != wordId) {
                hint.erase(0, hint.find_first_not_of(" \""));
                hint.erase(hint.find_last_not_of(" \"") + 1); 
                updatedHints[id].push_back(hint);
            }
        }     }
    hintsInput.close();
    ofstream hintsOutput(HintsFile);
    if (!hintsOutput){
        cerr << "Error: Unable to write to hints file: " << HintsFile << endl;
        return "";
    }
    for (const auto &entry : updatedHints) {
        for (const auto &hint : entry.second) {
            hintsOutput << entry.first << ", " << hint << endl;
        }
    }
    hintsOutput.close();
    ifstream wordsInput(WordsFile);
    if (!wordsInput) {
        cerr << "Error: Unable to open words file: " << WordsFile << endl;
        return "";
    }
    while (getline(wordsInput, line)) {
        istringstream iss(line);
        string idStr, word, levelStr;
        if (getline(iss, idStr, ',') && getline(iss, word, ',') && getline(iss, levelStr, ','))
        {
            int id = stoi(idStr);
            if (id != wordId) {
                updatedWords.push_back(line); 
            } else {
                word.erase(0, word.find_first_not_of(" \""));
                word.erase(word.find_last_not_of(" \"") + 1); 
                deletedWord = word;                           
            }
        }     }
    wordsInput.close();
    ofstream wordsOutput(WordsFile);
    if (!wordsOutput) {
        cerr << "Error: Unable to write to words file: " << WordsFile << endl;
        return "";
    }
    for (const auto &entry : updatedWords) {
        wordsOutput << entry << endl;
    }
    wordsOutput.close();
    return deletedWord;
}

// my cifef

WordDetails searchWord(const map<int, vector<tuple<int, string, vector<string>>>> &dataMap, const string &searchWord)
{
    for (const auto &levelEntry : dataMap)
    {
        for (const auto &wordHintsTuple : levelEntry.second)
        {
            int id;
            string word;
            vector<string> hints;

            // Unpack the tuple
            tie(id, word, hints) = wordHintsTuple;

            // Search for the word
            if (word == searchWord)
            {
                int wordLength = word.length();
                int level = levelEntry.first;

                // Create the WordDetails object with fetched data
                WordDetails details;
                details.id = id;
                details.word = word;
                details.level = level;
                details.wordLength = wordLength;
                details.hints = hints;

                return details; // Return the fetched data
            }
        }
    }

    // If the word is not found, throw an exception or handle it gracefully
    throw std::runtime_error("Word '" + searchWord + "' not found.");
}

bool isWordAvailable(const map<int, vector<tuple<int, string, vector<string>>>> &dataMap, const string &searchWord)
{
    for (const auto &levelEntry : dataMap)
    {
        for (const auto &wordHintsTuple : levelEntry.second)
        {
            const string &word = get<1>(wordHintsTuple); // Access the word (2nd element of the tuple)
            if (word == searchWord)
            {
                return true; // Word found
            }
        }
    }
    return false; // Word not found
}

// map<int, vector<pair<string, vector<string>>>> vocabulary = {
//     {1, {{"apple", {"A fruit", "Red or green", "Keeps the doctor away", "Can be eaten raw", "Used in pies"}}, {"table", {"Furniture", "Has legs", "Used for eating", "Can be round or rectangular", "Often found in dining rooms"}}, {"car", {"Has four wheels", "Used for transportation", "Runs on fuel", "Can be electric", "Can be driven"}}, {"house", {"Where people live", "Has a roof", "Can have many rooms", "Provides shelter", "Often found in neighborhoods"}}, {"computer", {"Used for processing data", "Has a screen", "Can connect to the internet", "Used for gaming", "Can be portable"}}, {"window", {"Opening in a wall", "Lets in light", "Can be opened", "Used for ventilation", "Often has glass"}}, {"bottle", {"Holds liquids", "Made of glass or plastic", "Can be recycled", "Often has a cap", "Used for storage"}}, {"phone", {"Used for communication", "Can be mobile", "Has a screen", "Can connect to the internet", "Used for calls"}}, {"chair", {"Furniture for sitting", "Has four legs", "Can be comfortable", "Used in homes and offices", "Can have arms"}}, {"book", {"Contains pages", "Used for reading", "Can be fiction or non-fiction", "Often has a cover", "Can be borrowed from libraries"}}, {"clock", {"Tells time", "Has hands or digital display", "Used for scheduling", "Can be wall-mounted", "Often has a ticking sound"}}, {"lamp", {"Provides light", "Has a bulb", "Can be used in homes", "Can be table or floor type", "Used for reading"}}, {"bag", {"Used for carrying items", "Can be made of fabric or plastic", "Often has handles", "Used for shopping", "Can be backpack-style"}}, {"wallet", {"Holds money", "Can store cards", "Used for personal items", "Often carried in pockets", "Made of leather or fabric"}}, {"keyboard", {"Used for typing", "Has keys", "Can be mechanical or membrane", "Connected to computers", "Used in gaming"}}, {"mouse", {"Used for navigating", "Has buttons", "Can be wired or wireless", "Used with computers", "Can be optical or laser"}}}},
//     {2, {{"guitar", {"Musical instrument", "Has six strings", "Used in bands", "Played with fingers or a pick", "Can be acoustic or electric"}}, {"piano", {"Musical instrument", "Has keys", "Used for playing music", "Can be grand or upright", "Often used in classical music"}}, {"drum", {"Percussion instrument", "Played with sticks", "Used in bands", "Can be acoustic or electronic", "Provides rhythm"}}, {"camera", {"Takes photographs", "Can be digital", "Used for capturing memories", "Has lenses", "Can record videos"}}, {"telescope", {"Used for viewing distant objects", "Has lenses", "Used in astronomy", "Can be refracting or reflecting", "Enables stargazing"}}, {"microphone", {"Captures sound", "Used in recordings", "Can be wired or wireless", "Used in concerts", "Enhances audio quality"}}, {"notebook", {"Used for writing", "Contains pages", "Can be spiral-bound", "Used by students", "Often carried in bags"}}, {"backpack", {"Used for carrying items", "Has straps", "Can be worn on the back", "Used for school", "Often has multiple compartments"}}, {"umbrella", {"Used for protection from rain", "Can be opened", "Often has a handle", "Can be portable", "Used in sunny weather too"}}, {"calculator", {"Used for calculations", "Can be scientific", "Has buttons", "Used in math", "Can be portable"}}, {"tablet", {"Portable device", "Has a touch screen", "Used for browsing", "Can run apps", "Often used for reading"}}, {"projector", {"Displays images or videos", "Used in presentations", "Projects onto a screen", "Can be portable", "Used in classrooms"}}, {"printer", {"Produces paper copies", "Can be inkjet or laser", "Used for documents", "Often connected to computers", "Used in offices"}}, {"scanner", {"Digitizes documents", "Used for archiving", "Can scan photos", "Often connected to computers", "Used in offices"}}, {"router", {"Connects devices to the internet", "Has antennas", "Can be wireless", "Used in networking", "Transmits data"}}}},
//     {3, {{"sofa", {"Furniture for sitting", "Can be comfortable", "Often found in living rooms", "Can seat multiple people", "Usually has cushions"}}, {"refrigerator", {"Appliance for cooling food", "Has shelves", "Used in kitchens", "Can be electric", "Keeps food fresh"}}, {"television", {"Used for watching shows", "Can be smart or traditional", "Displays video", "Can connect to the internet", "Used for entertainment"}}, {"microwave", {"Appliance for heating food", "Uses electromagnetic waves", "Can cook quickly", "Used in kitchens", "Often has a timer"}}, {"air conditioner", {"Cools indoor air", "Used in summer", "Can be window-mounted", "Improves comfort", "Can be central or portable"}}, {"vacuum", {"Cleans floors", "Uses suction", "Can be upright or handheld", "Used in homes", "Collects dust and debris"}}, {"washing machine", {"Cleans clothes", "Uses water and detergent", "Can be front or top-loading", "Used in homes", "Improves laundry efficiency"}}, {"dishwasher", {"Cleans dishes", "Uses water and detergent", "Can be built-in or portable", "Saves time", "Used in kitchens"}}, {"blender", {"Used for mixing", "Can puree ingredients", "Has blades", "Used in kitchens", "Can be electric"}}, {"toaster", {"Cooks bread", "Can be electric", "Produces toast", "Used in breakfasts", "Can have multiple slots"}}, {"stove", {"Cooks food", "Can be gas or electric", "Used in kitchens", "Has burners", "Essential for cooking"}}, {"frying pan", {"Used for cooking", "Has a flat bottom", "Often made of metal", "Used for frying", "Can have a non-stick surface"}}, {"cutting board", {"Used for food preparation", "Can be made of wood or plastic", "Protects surfaces", "Easy to clean", "Often found in kitchens"}}, {"pot", {"Used for cooking", "Has a handle", "Can be made of metal or ceramic", "Used for boiling", "Essential for soups"}}, {"pan", {"Used for cooking", "Flat and shallow", "Can be non-stick", "Used for frying", "Essential for meals"}}, {"kettle", {"Used for boiling water", "Can be electric", "Used for making tea", "Has a handle", "Common in kitchens"}}}},
//     {4, {{"battery", {"Stores energy", "Powers devices", "Can be recharged", "Comes in different sizes", "Used in electronics"}}, {"speaker", {"Produces sound", "Connected to devices", "Used for listening", "Can be wireless", "Amplifies audio"}}, {"laptop", {"Portable computer", "Has a screen", "Used for work or gaming", "Can be battery-powered", "Can connect to Wi-Fi"}}, {"engine", {"Powers vehicles", "Converts fuel to energy", "Found in cars", "Makes vehicles move", "Runs on gasoline or diesel"}}, {"network", {"Connects computers", "Transfers data", "Used for communication", "Can be wireless", "Part of the internet"}}, {"memory", {"Stores information", "Used in computers", "Can be RAM or storage", "Measured in GB or TB", "Temporary or permanent"}}, {"sensor", {"Detects changes", "Used in devices", "Measures physical quantities", "Converts to signals", "Can be thermal, motion, etc."}}, {"cable", {"Transmits power or data", "Connects devices", "Can be USB or HDMI", "Made of wires", "Used in electronics"}}, {"fan", {"Cools devices", "Has blades", "Rotates to produce airflow", "Used in computers", "Prevents overheating"}}, {"database", {"Stores structured data", "Used in programming", "Can be queried", "Organized in tables", "Contains records"}}, {"compiler", {"Transforms code", "Used in programming", "Produces executable files", "Ensures syntax correctness", "Essential for development"}}, {"algorithm", {"Step-by-step procedure", "Used in problem-solving", "Essential in programming", "Can be simple or complex", "Defines logic"}}, {"function", {"Reusable code block", "Performs specific tasks", "Can take inputs", "Returns outputs", "Fundamental in programming"}}, {"variable", {"Stores data", "Has a name", "Can change values", "Used in programming", "Essential for logic"}}, {"object", {"Instance of a class", "Encapsulates data", "Used in OOP", "Can have properties", "Supports methods"}}, {"class", {"Blueprint for objects", "Defines properties", "Used in OOP", "Can be inherited", "Encapsulates data"}}}},
//     {5, {{"robot", {"Automated machine", "Can perform tasks", "Used in manufacturing", "Can be programmed", "Can have sensors"}}, {"drone", {"Unmanned aerial vehicle", "Can fly", "Used for photography", "Can be controlled remotely", "Used in deliveries"}}, {"tablet", {"Portable touch device", "Used for browsing", "Has a screen", "Can run apps", "Used for reading"}}, {"browser", {"Used to access the internet", "Displays web pages", "Can be Chrome or Firefox", "Can save bookmarks", "Used for searching"}}, {"webcam", {"Camera for computers", "Used for video calls", "Can be integrated", "Used in streaming", "Connects to the internet"}}, {"algorithm", {"Set of rules", "Used for problem-solving", "Can be complex", "Implemented in programming", "Defines steps to follow"}}, {"encryption", {"Secures data", "Transforms information", "Used in cybersecurity", "Protects privacy", "Can be symmetric or asymmetric"}}, {"firewall", {"Protects networks", "Monitors traffic", "Blocks unauthorized access", "Used in security", "Can be hardware or software"}}, {"virus", {"Malicious software", "Can infect computers", "Spreads through networks", "Causes damage", "Can be removed with antivirus"}}, {"malware", {"Malicious software", "Can disrupt systems", "Used to steal data", "Includes viruses and spyware", "Can be harmful"}}, {"password", {"Secret word or phrase", "Used for authentication", "Protects accounts", "Should be strong", "Can be changed regularly"}}, {"account", {"User profile", "Used for accessing services", "Contains information", "Can be personal or business", "Requires password"}}, {"server", {"Provides resources", "Hosts websites", "Handles requests", "Used in networking", "Can be dedicated or shared"}}, {"cloud", {"Remote storage", "Accessed via the internet", "Used for backup", "Can be public or private", "Offers scalability"}}, {"website", {"Collection of web pages", "Accessed through browsers", "Used for information", "Can be personal or business", "Includes domains"}}, {"application", {"Software program", "Used for tasks", "Can be mobile or desktop", "Includes features", "Can be downloaded"}}, {"platform", {"Base for applications", "Supports development", "Can be software or hardware", "Enables functionality", "Can be cloud-based"}}, {"integration", {"Combines systems", "Ensures compatibility", "Used in software development", "Facilitates communication", "Enhances functionality"}}}}};

// int main() {

//     // File names
//     ofstream wordFile("WordScrumble_Words.txt");
//     ofstream hintFile("WordScrumble_Words_Hints.txt");

//     if (!wordFile.is_open() || !hintFile.is_open()) {
//         cerr << "Error: Unable to open files for writing." << endl;
//         return 1;
//     }

//     // Auto-incrementing primary key for words
//     int wordId = 1;

//     // Write data to files
//     for (const auto &level : vocabulary) {
//         int levelNumber = level.first;

//         for (const auto &entry : level.second) {
//             const string &word = entry.first;
//             const vector<string> &hints = entry.second;

//             // Write to WordScrumble_Words.txt (CSV Format)
//             wordFile << wordId << ", " << word << ", " << levelNumber << endl;

//             // Write each hint to WordScrumble_Words_Hints.txt
//             for (const auto &hint : hints) {
//                 hintFile << wordId << ", \"" << hint << "\"" << endl;
//             }

//             // Increment wordId for the next word
//             ++wordId;
//         }
//     }

//     wordFile.close();
//     hintFile.close();

//     cout << "Files generated successfully!" << endl;

//     return 0;
// }

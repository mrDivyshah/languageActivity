#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <random>

using namespace std;
#define FillingTheBlanks_DATABASE getCurrentDirectory() + "/src/game/gra.txt"


map<int, vector<pair<string, vector<string>>>> loadfillintheblanks()
{
    map<int, vector<pair<string, vector<string>>>> vocabulary;
    ifstream file(FillingTheBlanks_DATABASE);

    if (!file.is_open())
    {
        cerr << "Error: Unable to open file " << FillingTheBlanks_DATABASE << endl;
        return vocabulary;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string levelStr, question, op1, op2, op3, op4, answer;

        // Read level, question, options, and answer
        if (getline(ss, levelStr, ',') && getline(ss, question, ',') &&
            getline(ss, op1, ',') && getline(ss, op2, ',') &&
            getline(ss, op3, ',') && getline(ss, op4, ',') &&
            getline(ss, answer, ','))
        {

            int level = stoi(levelStr); // Convert level to integer
            string formattedQuestion = question + " (" + op1 + ", " + op2 + ", " + op3 + ", " + op4 + ")";
            vector<string> options = {answer, op1, op2, op3, op4};
            vocabulary[level].emplace_back(formattedQuestion, options);
        }
    }

    file.close();
    return vocabulary;
}


#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <random>

#define SentenceScramble_DATABASE getCurrentDirectory() + "/src/game/CrossWords.txt"

using namespace std;

map<int, vector<pair<string, vector<string>>>> loadVocabulary()
{
    map<int, vector<pair<string, vector<string>>>> vocabulary;
    ifstream file(SentenceScramble_DATABASE);

    if (!file.is_open())
    {
        cerr << "Error: Unable to open file " << SentenceScramble_DATABASE << endl;
        return vocabulary;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string levelStr, sentence, hint1, hint2;

        if (getline(ss, levelStr, ',') && getline(ss, sentence, ',') && getline(ss, hint1, ',') && getline(ss, hint2, ','))
        {
            int level = stoi(levelStr); // Convert level to integer
            vector<string> hints = {hint1, hint2};
            vocabulary[level].emplace_back(sentence, hints);
        }
    }

    file.close();
    return vocabulary;
}

string shuffleSentence(const string &sentence)
{
    vector<string> words;
    string word;
    istringstream stream(sentence);
    while (stream >> word)
    {
        words.push_back(word);
    }

    vector<string> originalWords = words;

    do
    {
        shuffle(words.begin(), words.end(), default_random_engine(rand()));
    } while (words == originalWords);

    stringstream shuffledSentence;
    for (const auto &w : words)
    {
        shuffledSentence << w << " ";
    }

    string result = shuffledSentence.str();
    if (!result.empty() && result.back() == ' ')
    {
        result.pop_back();
    }

    return result;
}

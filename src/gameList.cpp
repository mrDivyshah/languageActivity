#include <string>
#include <vector>

using namespace std;



struct Games
{
    int index;
    string name;
    string functionName;
};

vector<Games> gameList = {
    {1, "Cross Words", "Hangman"},
    {2, "Word Scramble", "wordScramble"},
    {3, "Fill in the blanks", "Blanks"}};
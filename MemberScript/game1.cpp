#include <iostream>
#include <windows.h>
#include <cstring>
#include <conio.h>
#include <cstdlib> //rand()
using namespace std;

void display();

int gamefunction();

int main()
{

    string name;
    cout << "Enter your name  :   ";
    getline(cin, name);
    cout << endl;

    // if user guess the word right the score of the user will store in ths variable.
    int score = 0;

    // take the input from the user wether the user want to play the re game or not.
    char input;
    do
    {

        // game code
        system("cls"); // this will clear the game after one game gets finished.
        display();
        score = score + gamefunction();
        cout << "would you like to play again (y/n) : ";
        cin >> input;
        cout << endl;

    } while (input != 'n');

    cout << name << "  " << "your score is = " << score << endl;

    cout << "**************************************************************************************" << endl;

    return 0;
}

void display()
{

    cout << "******************************** word searching game ********************************" << endl;
    cout << "A puzzle of words alphabets is shown on screen. you have to guess a hidden correct word" << endl;
    cout << "word from the puzzle. for each correct guessing you will get one score" << endl;
}

int gamefunction()
{

    string array[10] = {"java", "c++", "python", "scala", "php", "html", "c++", "kotlin", "android", "golang"};

    char matrix[10][10];

    int r;
    char c;

    for (int i = 0; i < 10; i++)
    {

        for (int j = 0; j < 10; j++)
        {

            r = rand() % 26; // this will take any random number from 0 to 26 an the it will convert it into alphabets.
            c = 'a' + r;     // r=0, c = 97+0=97='a';  r=1, c = 97+1=98='b'
            matrix[i][j] = c;
        }
        cout << endl;
    }

    int index = rand() % 10; // this sentence is to take random string from an array an then random string will place it into a matrix;
    string output = array[index];
    if (array[index].length() % 2 == 0)
    {

        // horizontally
        int row = rand() % 10;
        int col = rand() % 3;
        for (int i = 0; array[index][i] != '\0'; i++, col++)
        {
            matrix[row][col] = array[index][i];
        }
    }
    else
    {

        // vertically
        int row = rand() % 3;
        int col = rand() % 10;
        for (int i = 0; array[index][i] != '\0'; i++, row++)
        {
            matrix[row][col] = array[index][i];
        }
    }

    cout << "*****************puzzle**************************" << endl
         << endl;

    for (int i = 0; i < 10; i++)
    {

        for (int j = 0; j < 10; j++)
        {

            cout << matrix[i][j] << " ";
            Sleep(100);
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;

    string guess;
    int hint;
    cout << "press 1 for direct guess input : " << endl;
    cout << "press 2 for firstly see the hint and then enter guess input : " << endl;
a:
    cout << "Enter input : " << endl;
    cin >> hint;
    cout << endl;
    if (hint == 1)
    {

        cout << "Enter guessing word : ";
        cin >> guess;
        cout << endl;
    }
    else if (hint == 2)
    {

        cout << "the guessing word size is = " << output.length() << endl;
        cout << "Enter guessing word : ";
        cin >> guess;
        cout << endl;
    }
    else
    {

        cout << "Enter valid input : " << endl;
        goto a;
    }
    if (output == guess)
    {

        cout << "Congratulations ! you guessed the right word in the puzzle ! := " << endl
             << endl;
        return 1;
    }
    else
    {

        cout << "Sorry you guessed the wrong word : " << endl;
        return 0;
    }
}
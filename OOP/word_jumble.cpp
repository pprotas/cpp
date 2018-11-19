// word_jumble.cpp
// Compile with: g++ word_jumble.cpp -o word_jumble

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    int score = 0;
    enum fields
    {
        WORD,
        HINT,
        NUM_FIELDS
    };
    const int NUM_WORDS = 5;
    const string WORDS[NUM_WORDS][NUM_FIELDS] =
        {
            {"wall", "Do you feel you're banging your head against something?"},
            {"glasses", "These might help you see the answer."},
            {"labored", "Going slowly, is it?"},
            {"persistent", "Keep at it."},
            {"jumble", "It's what the game is all about."}};

    srand(static_cast<unsigned int>(time(0)));
    int choice = (rand() % NUM_WORDS);
    string theWord = WORDS[choice][WORD]; // word to guess
    string theHint = WORDS[choice][HINT]; // hint for word

    string jumble = theWord; // jumbled version of word
    int length = jumble.size();
    for (int i = 0; i < length; ++i)
    {
        int index1 = (rand() % length);
        int index2 = (rand() % length);
        char temp = jumble[index1];
        jumble[index1] = jumble[index2];
        jumble[index2] = temp;
    }

    cout << "\t\t\tWelcome to Word Jumble!\n\n";
    cout << "Unscramble the letters to make a word.\n";
    cout << "Enter 'hint' for a hint.\n";
    cout << "Enter 'quit' to quit the game.\n\n";
    cout << "The jumble is: " << jumble;

    string guess;
    cout << "\n\nYour guess: ";
    cin >> guess;

    while ((guess != theWord) && (guess != "quit"))
    {
        if (guess == "hint")
        {
            score -= 50;
            cout << theHint << "\n50 points deducted.";
        }
        else
        {
            score -=10;
            cout << "Sorry, that's not it.\n10 points deducted.";
        }

        cout << "\n\nYour guess: ";
        cin >> guess;
    }

    if (guess == theWord)
    {
        for (int i = 0; i < length; i++)
        {
            score += 30;
        }
        cout << "\nThat's it!  You guessed it!\n";
    }

    cout << "\nThanks for playing.\nScore: " << score << "\n";

    return 0;
}

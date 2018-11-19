// guess_my_number.cpp
// Compile with: g++ guess_my_number.cpp -o guess_my_number

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
    int tries = 0;
    int answer;
    int guess = 50;
    int previousGuess;

    srand(time(NULL));

    cout << "Enter your number: ";
    cin >> answer;

    while (guess != answer)
    {
        previousGuess = guess;
        while (previousGuess % 2 != 0)
        {
            previousGuess++;
        }
        cout << "The computer says: " << guess << ".\n";
        if (guess > answer)
        {
            if (tries > 20)
            {
                guess = rand() % guess + 1;
            }
            else
            {
                guess -= previousGuess / 2;
            }
            cout << "Too high.\n";
        }
        else if (guess < answer)
        {
            if (tries > 20)
            {
                guess = rand() % 100 + guess;
            }
            else
            {
                guess += previousGuess / 2;
            }
            cout << "Too low.\n";
        }
        tries++;
    }

    cout << "The computer guessed the right number in " << tries << " tries. The answer was: " << answer << "\n";
}
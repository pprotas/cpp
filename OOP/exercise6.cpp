#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

// Compile with g++ -std=c++11 exercise6.cpp -o exercie6
int main()
{
    enum OPTION
    {
        list,
        add,
        rem
    };
    int choice;

    vector<string> games;

    cout << "==========================\nWelcome to GameManager!\n==========================\nWhat would you like to do? Type in the number (1-3)\n";

    while (true)
    {
        cout << "Menu:\n0. List all game titles\n1. Add a game title\n2. Remove a game title\nPress Ctrl + C to exit.\nYour choice: ";
        cin >> choice;

        if (choice == list)
        {
            cout << "==========================\nYour games:\n";
            int index = 0;
            for (auto it = games.begin(); it != games.end(); ++it)
            {
                cout << "Game #" << index++ << ": " << *it << "\n";
            }
            cout << "==========================\n";
        }
        else if (choice == add)
        {
            cout << "Enter a game title (no spaces): ";
            string game;
            cin >> game;

            games.push_back(game);
        }
        else if (choice == rem)
        {
            cout << "At which index should i remove the game? (use \"list\" first)\n";
            int index;
            cin >> index;

            games.erase(games.begin() + index);
        }
        else
        {
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}

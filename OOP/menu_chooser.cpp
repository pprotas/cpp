// menu_chooser.cpp
// Compile with: g++ menu_chooser.cpp -o menu_chooser

#include <iostream>
using namespace std;

int main() 
{
        cout << "Difficulty Levels\n\n";
        cout << "1 - Easy\n";   
        cout << "2 - Normal\n";
        cout << "3 - Hard\n\n";

        int choice;
        cout << "Choice: ";
        cin >> choice;

        enum difficulty{easy, normal, hard};
        difficulty dif;
        
        switch (choice)
        {
        case 1:    
                cout << "You picked Easy.\n";
                dif=easy;
                break;
        case 2:    
                cout << "You picked Normal.\n";
                dif=normal;
                break;
        case 3:    
                cout << "You picked Hard.\n";
                dif=hard;
                break;
        default:
                cout << "You made an illegal choice.\n";
        }

        return 0;
}

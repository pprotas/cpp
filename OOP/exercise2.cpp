#include <iostream>
using namespace std;

int main()
{
    double first;
    double second;
    double third;
    double avg;

    cout << "Number 1: ";
    cin >> first;

    cout << "Number 2: ";
    cin >> second;

    cout << "Number 3: ";
    cin >> third;
    
    avg = (first+second+third)/3;

    cout << "Average: " << avg << endl;

    return 0;
}
#include <iostream>
using namespace std;

int getNum(string prompt = "Please specify a number: ");

int getNum2(string prompt);
int getNum2();

int main()
{
    int a = getNum("Enter number: ");
    int b = getNum();

    int c = getNum2("Enter number: ");
    int d = getNum2();

    return 0;
}

int getNum(string prompt)
{
    int n;
    cout << prompt;
    cin >> n;

    return n;
}

int getNum2(string prompt)
{
    int n;
    cout << prompt;
    cin >> n;

    return n;
}

int getNum2()
{
    int n;
    cout << "Please specify a number: ";
    cin >> n;

    return n;
}
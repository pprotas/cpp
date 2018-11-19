// twice.cpp
// Compile with: g++ twice.cpp -o twice

#include <iostream>

using namespace std;

template <class T>
T twice(T i)
{
    return i + i;
}

int main()
{
    cout << twice(5) << endl;
    cout << twice(5.3) << endl;

    return 0;
}

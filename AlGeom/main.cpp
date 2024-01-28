//written by Spitkovska
#include <iostream>
#include <random>
#include "funcs.h"

using namespace std;

int main()
{
    cout << "Calculate the Arithmetic–geometric mean of a and b" << endl;
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(1, 6);

    for (int iteration = 1; iteration <= 3; iteration++)
    {
        double a = dist(mt), b = dist(mt);
        cout << "when their values are: a=" << a << ", b=" << b << endl;
        cout << "M(" << a << "," << b << ")=" << AGM(a, b) << endl;
    }
}
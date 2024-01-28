//written by Spitkovska / tsaebst


#include <iostream>
using namespace std;
#include "funcs.h"

int main()
{
    int n = 6;
    cout << "n = " << n << endl;
    Vector2 result = fibo(n);
    cout << "F(" << n << ") = " << result._1 << endl;
    cout << "F(" << n - 1 << ") = " << result._2 << endl;

    return 0;
}

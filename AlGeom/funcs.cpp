//written by Spitkovska
#include "funcs.h"
#include <math.h>

double AGM(double a, double b)
{
    double aCurrent = a;
    double bCurrent = b;
    //    initialising a(1) and b(1)
    double An = sqrt(a * b);
    double Bn = (a + b) / 2;
    //    until they still keep the condition(an > bn) and each next element of 2 sequences is smaller
    //    than previous
    while (Bn < An && An < aCurrent && Bn < bCurrent)
    {
        //      changing values of current elements in seq. a and b from a/bn to a/bn+1
        aCurrent = An;
        bCurrent = Bn;
        //      finding a/b(n+2)
        An = sqrt(aCurrent * bCurrent);
        Bn = (aCurrent + bCurrent) / 2;
    }
    //    standart AGM value is being returned
    return An;
}


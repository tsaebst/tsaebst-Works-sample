//written by Spitovska Vladyslava
#include <cassert>
#include "funcs.h"
#include <random>
#define NDEBUG

using namespace std;



#ifdef NDEBUG
double sum(double* coeff, size_t size, int sign)
{
    double result = 0;
    if (sign + (-sign) == 0)
    {
        for (int k = 0; k < size; ++k)
        {
            if (k % 2 == 0)
            {
                result += coeff[k];
            }
            else
            {
                result -= coeff[k];
            }
        }
    }
    else
    {
        for (int k = 0; k < size; ++k)
        {
            result += coeff[k];
        }
    }
    return result;
}
#endif

double genDouble(double lower_p, double higher_p) {
    random_device rd;
    default_random_engine generator(rd());
    uniform_real_distribution<double> distribution(lower_p, higher_p);
    return distribution(generator);
}

void fillArray(double* coeff, size_t size)
{
    for (int n = 0; n < size; ++n) 
    {
        coeff[n] = genDouble(-10, 10);

    }
}

double Horner(double* coeff, size_t size, double x)
{
    double result = 0;
    double a_1 = coeff[0];
    double a_2 = 0;
    for (int  k = 1; k < size; ++k) 
    {
        a_2 = (a_1 * x)+ coeff[k];
        a_1 = a_2;
    }
    result = a_1;
    #ifdef NDEBUG
    if (x == 1 || x == -1)
    {
        result = sum(coeff, size, x);
    }
    assert(((x == 1) || (x == -1)) ? (result == sum(coeff, size, x)) : true);
    #endif

    return result;
}
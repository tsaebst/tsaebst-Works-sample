//written by Spitovska Vladyslava
#include <iostream>
#include "funcs.h"
using namespace std;


int main() 
{
	int size = 3;
	double x = 1;
	double* coef = new double[size];
	fillArray(coef, size);
	cout << "Horner`s polynomial calculation" << endl;
	cout << "x = " << x << endl;
	for (int n = 0; n < size; ++n) 
	{
		cout << "a(" << n << ") = " << *(coef + n) << endl;
	}
	cout << "Calculation result:" << Horner(coef, size, x) << endl;
}
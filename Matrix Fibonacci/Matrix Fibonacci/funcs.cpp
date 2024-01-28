#include "funcs.h"


Matrix2x2 multiplyM(Matrix2x2 F0, Matrix2x2 F1)
{
    Matrix2x2 result;
    result._11 = F0._11 * F1._11 + F0._12 * F1._21;
    result._12 = F0._11 * F1._12 + F0._12 * F1._22;
    result._21 = F0._21 * F1._11 + F0._22 * F1._21;
    result._22 = F0._21 * F1._12 + F0._22 * F1._22;
    return result;
}


Matrix2x2 QuickPower(Matrix2x2 matrix, int n)
{
    if (n == 1)
    {
        return matrix;
    }
    else if(n == 0)
    {
        return Matrix2x2{0,0,0,0};
    }
    else
    {
        Matrix2x2 SlicedMatrix = QuickPower(matrix, n / 2);
        if (n % 2 != 0)
        {
            return multiplyM(matrix, multiplyM(SlicedMatrix, SlicedMatrix));
        }

        return multiplyM(SlicedMatrix, SlicedMatrix);
    }
}

Vector2 multiVect(Vector2 V, Matrix2x2 M)
{
    Vector2 elements;
    elements._1 = M._11 * V._1 + M._12 * V._2;
    elements._2 = M._21 * V._1 + M._22 * V._2;
    return elements;
}

Vector2 fibo(int n)
{
    Matrix2x2 fibMatrix{ 1, 1, 1, 0 };
    Vector2 fibVector = { 0, 1 };

    if (n == 0)
    {
        return fibVector;
    }
    else if (n == 1)
    {
        return Vector2{ 1,1 };
    }
    Matrix2x2 MatrixQP = QuickPower(fibMatrix, n);
    Vector2 res = multiVect(fibVector, MatrixQP);
    return res;

}

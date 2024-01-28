//written by Spitkovska
struct Matrix2x2 { int _11, _12, _21, _22; };
struct Vector2 { int _1, _2; };
Matrix2x2 multiplyM(Matrix2x2 F0, Matrix2x2 F1);
Vector2 multiVect(Vector2 A, Matrix2x2 B);
Matrix2x2 QuickPower(Matrix2x2 a, int n);
Vector2 fibo(int n);

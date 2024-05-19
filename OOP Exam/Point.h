#pragma once
#include <iostream>
//Клас точки в тривимірному просторі
class Point
{
private:
    static int _freeID;
    const int _pointID;
    static int _counter;
    double _x;
    double _y;
    double _z;

public:
    Point(double x = 0, double y = 0, double z = 0);
    Point(const Point&);

    ~Point();

    Point& operator= (const Point&);

    double& x() { return _x; };
    double& y() { return _y; };
    double& z() { return _z; };
    const double& x() const { return _x; };
    const double& y() const { return _y; };
    const double& z() const { return _z; };

    const int getID() const { return _pointID; };
    static int amount() { return _counter; };

    Point middle(const Point& v) const;

    double pDistance(const Point& u, const Point& v);
    double distance(const Point& u);

};

std::ostream& operator<< (std::ostream&, const Point&);

const Point operator+ (const Point& u, const Point& v);

Point& operator+= (Point& u, const Point& v);

bool operator== (const Point& u, const Point& v);

bool operator!= (const Point& u, const Point& v);


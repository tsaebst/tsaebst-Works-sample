#pragma once
//#define NDEBUG
#include <iostream>
#include "Point.h"
//Клас тривимірних відрізків
class Segment 
{
private:
    friend class Point;
    static int _freeID;
    const int _myId;
    Point _a;
    Point _b;

public:
    Segment(double x1 = 0, double y1 = 0, double z1 = 0,
        double x2 = 1, double y2 = 0, double z2 = 0);
    Segment(const Point& start, const Point& end);
    Segment(const Segment&);

    ~Segment();

    Segment& operator=(const Segment&);

    const Point& start() const { return _a; };
    const Point& end() const { return _b; };
    Point& start();
    Point& end();

    const double& startX() const { return _a.x(); };
    const double& startY() const { return _a.y(); };
    const double& startZ() const { return _a.z(); };
    const double& endX() const { return _b.x(); };
    const double& endY() const { return _b.y(); };
    const double& endZ() const { return _b.z(); };
    double& startX() { return _a.x(); };
    double& startY() { return _a.y(); };
    double& startZ() { return _a.z(); };
    double& endX() { return _b.x(); };
    double& endY() { return _b.y(); };
    double& endZ() { return _b.z(); };

    double length() const;
    double distance(const Point&) const;
    const int getID() const { return _myId; };
};

std::ostream& operator<<(std::ostream&, const Segment&);

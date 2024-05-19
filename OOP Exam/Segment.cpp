//written by Spitkovska

#include "Segment.h"
#include"Point.h"
#include <cmath>
using std::cout;
#include <assert.h>
//#define NDEBUG

Segment::Segment(const double x1, const double y1, const double z1,
    const double x2, const double y2, const double z2) :
    _a(x1, y1, z1), _b(x2, y2, z2), _myId(_freeID++) {}

Segment::Segment(const Point& start, const Point& end) :
    _a(start), _b(end), _myId(_freeID++) {}

Segment::Segment(const Segment& a) :
    _a(a._a), _b(a._b), _myId(_freeID++) {}

Segment::~Segment() {}

Segment& Segment::operator=(const Segment& a) {
    if (this == &a) return *this;
    _a = a._a;
    _b = a._b;
    return *this;
}

double Segment::length() const {
    double dx = _b.x() - _a.x();
    double dy = _b.y() - _a.y();
    double dz = _b.z() - _a.z();
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

std::ostream& operator<<(std::ostream& os, const Segment& u) {
    os << "Segment ID: " << u.getID() << ", Start: (" << u.startX() << ", " << u.startY() << ", " << u.startZ()
        << "), End: (" << u.endX() << ", " << u.endY() << ", " << u.endZ() << ")";
    return os;
}


//calculating distance from segment[A;B] to the point C
double Segment::distance(const Point& C) const {
    // Координати точок A і B
    double x1 = _a.x();
    double y1 = _a.y();
    double z1 = _a.z();
    double x2 = _b.x();
    double y2 = _b.y();
    double z2 = _b.z();

    // Вектор відрізка AB
    double ABx = x2 - x1;
    double ABy = y2 - y1;
    double ABz = z2 - z1;

    // Вектор від точки A до точки C
    double ACx = C.x() - x1;
    double ACy = C.y() - y1;
    double ACz = C.z() - z1;

    // Скалярний добуток векторів AB та AC
    double dotProduct = ABx * ACx + ABy * ACy + ABz * ACz;

    // Квадрат довжини відрізка AB
    double AB_squaredLength = ABx * ABx + ABy * ABy + ABz * ABz;

    // Параметр t, який визначає положення точки на відрізку AB
    double t = dotProduct / AB_squaredLength;

    // Визначаємо точку, яка лежить на відрізку AB, найближче до точки C
    double nearestX, nearestY, nearestZ;
    if (t < 0) {
        // Точка C найближча до точки A
        nearestX = x1;
        nearestY = y1;
        nearestZ = z1;
    }
    else if (t > 1) {
        // Точка C найближча до точки B
        nearestX = x2;
        nearestY = y2;
        nearestZ = z2;
    }
    else {
        // Точка C найближча до відрізка AB, визначаємо її координати
        nearestX = x1 + t * ABx;
        nearestY = y1 + t * ABy;
        nearestZ = z1 + t * ABz;
    }

    // Обчислення відстані від точки C до найближчої точки на відрізку AB
    double distToSegment = std::sqrt((C.x() - nearestX) * (C.x() - nearestX) + (C.y() - nearestY) * (C.y() - nearestY) + (C.z() - nearestZ) * (C.z() - nearestZ));

    return distToSegment;
}



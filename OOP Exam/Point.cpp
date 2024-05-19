//written by Spitkovska
#include "Point.h"
using std::cout;

int Point::_freeID = 0;
int Point::_counter = 0;

Point::Point(double x, double y, double z) :
    _x(x), _y(y), _z(z), _pointID(_freeID++)
{
    _counter++;
#ifdef NDEBUG
    std::cout << "Created point: " << *this << " with ID: " << _pointID << "\n";
#endif
}

Point::Point(const Point& a) :
    _x(a._x), _y(a._y), _z(a._z), _pointID(_freeID++) 
{
    _counter++;
#ifdef NDEBUG
    std::cout << "Created copy of point: " << *this << " with ID: " << _pointID << "\n";
#endif
}

Point::~Point() 
{
    _counter--;
#ifdef NDEBUG
    std::cout << "Deleted point: " << *this << " with ID: " << _pointID << "\n";
#endif
}

std::ostream& operator<<(std::ostream& os, const Point& v)
{
    return os << '(' << v.x() << ", " << v.y() << ", " << v.z() << ')';
}

const Point operator+(const Point& u, const Point& v) 
{
    return { u.x() + v.x(), u.y() + v.y(), u.z() + v.z() };
}

Point& operator+=(Point& u, const Point& v) 
{
    u.x() += v.x();
    u.y() += v.y();
    u.z() += v.z();
    return u;
}

bool operator==(const Point& u, const Point& v)
{
    return (u.x() == v.x()) && (u.y() == v.y()) && (u.z() == v.z());
}

bool operator!=(const Point& u, const Point& v) 
{
    return !(u == v);
}

Point& Point::operator=(const Point& p) 
{
    _x = p.x();
    _y = p.y();
    _z = p.z();
    return *this;
}

double Point::pDistance(const Point& u, const Point& v)
{
    double x = v.x() - u.x();
    double y = v.y() - u.y();
    double z = v.z() - u.z();
    return std::sqrt(x * x + y * y + z * z);
}

double Point::distance(const Point& u)
{
    double x_diff = this->x() - u.x();
    double y_diff = this->y() - u.y();
    double z_diff = this->z() - u.z();
    double res = std::sqrt(x_diff * x_diff + y_diff * y_diff + z_diff * z_diff);
    return res;
}


Point Point::middle(const Point& v) const
{
    double midX = (x() + v.x()) / 2.0;
    double midY = (y() + v.y()) / 2.0;
    double midZ = (z() + v.z()) / 2.0;
    return Point(midX, midY, midZ);
}

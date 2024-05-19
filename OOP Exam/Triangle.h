#pragma once
//written by Spitkovska
#include "Point.h"
#include "Segment.h"
//#define NDEBUG

//Клас тривимірої трикутної площини
class Triangle
{
private:
    Point _a, _b, _c; 
    Segment* _ab, * _bc, * _ca;
    Point _aMiddle;
    Point _bMiddle;
    Point _cMiddle;
    mutable Segment* _median_a, * _median_b, * _median_c;

public:

    // Конструктор трикутника за координатами його вершин (зі значеннями за замовчуванням)
    Triangle(const double x1, const double y1, const double z1,
        const double x2, const double y2, const double z2,
        const double x3, const double y3, const double z3) :
        _a(x1, y1, z1), _b(x2, y2, z2), _c(x3, y3, z3),
        _cMiddle(_a.middle(_b)),
        _aMiddle(_b.middle(_c)),
        _bMiddle(_c.middle(_a)) {}


    // Конструктор трикутника за його вершинами
    Triangle(const Point& a, const Point& b, const Point& c) :
        _a(a), _b(b), _c(c),
        _cMiddle(_a.middle(_b)),
        _aMiddle(_b.middle(_c)),
        _bMiddle(_c.middle(_a)) {}

    // Конструктор трикутника за відрізком і точкою
    Triangle(const Segment& seg, const Point& c) :
        _a(seg.start()), _b(seg.end()), _c(c),
        _cMiddle(_a.middle(_b)),
        _aMiddle(_b.middle(_c)),
        _bMiddle(_c.middle(_a)) {}


    // Копіювальний конструктор
    Triangle(const Triangle& other) :
        _a(other._a), _b(other._b), _c(other._c),
        _cMiddle(other._cMiddle), _aMiddle(other._aMiddle), _bMiddle(other._bMiddle) {}


    // Конструктор трикутника за відрізком і координатами
    Triangle(const Segment& seg, double x, double y, double z) :
        _a(seg.start()), _b(seg.end()), _c(Point(x, y, z)),
        _cMiddle(_a.middle(_b)),
        _aMiddle(_b.middle(_c)),
        _bMiddle(_c.middle(_a)) {}


    //Triangle(const Segment&, const Point&);

    ~Triangle();

    Triangle& operator=(const Triangle& other);

    const Point& apexA() const { return _a; };
    const Point& apexB() const { return _b; };
    const Point& apexC() const { return _c; };

    const Segment side_a() const { return Segment(_b, _c); };
    const Segment side_b() const { return Segment(_a, _c); };
    const Segment side_c() const { return Segment(_a, _b); };

    //Перевірка правильності трикутника
    static bool checkTriangle(const Triangle& triangle) 
    {
        double a = triangle.side_a().length();
        double b = triangle.side_b().length();
        double c = triangle.side_c().length();
        return a > 0 && b > 0 && c > 0 && a + b > c && a + c > b && b + c > a;
    }

    double perimeter() const;
    double area() const;


    //so how it works: while creating the triangle we are setting/resetting value of 
    //the middle of the segment which is located in front of the current point(for each point or how i 
    // also call it here, "vert").
    //then we check the distance between the vert and the middle of the segment using new method 

    const Segment& medianA() const;
    const Segment& medianB() const;
    const Segment& medianC() const;

    // side re - setter
        const Segment & side_a(const Point & start, const Point & end)
    {
        if (start != end && start != _a && _a != end)
        {
            if (_bc) delete _bc;
            _bc = new Segment(start, end);
            _b = start;
            _c = end;
        }
        return *_bc;
    }

    const Segment& side_b(const Point& start, const Point& end)
    {
        if (start != end && start != _b && _b != end)
        {
            if (_ca) delete _ca;
            _ca = new Segment(start, end);
            _c = start;
            _a = end;
            return *_ca;
        }
    }

    const Segment& side_c(const Point& start, const Point& end)
    {
        if (start != end && start != _c && _c != end)
        {
            if (_ab) delete _ab;
            _ab = new Segment(start, end);
            _a = start;
            _b = end;
            return *_ab;
        }
    }


    const Segment& side_a(const Segment& seg)
    {
        if (seg.start() != seg.end() && seg.start() != _a && _a != seg.end())
        {
            if (_bc) delete _bc;
            _bc = new Segment(seg.start(), seg.end());
            _b = seg.start();
            _c = seg.end();
            return *_bc;
        }
    }

    const Segment& side_b(const Segment& seg)
    {
        if (seg.start() != seg.end() && seg.start() != _b && _b != seg.end())
        {
            if (_ca) delete _ca;
            _ca = new Segment(seg.start(), seg.end());
            _c = seg.start();
            _a = seg.end();
            return *_ca;
        }
    }

    const Segment& side_c(const Segment& seg)
    {
        if (seg.start() != seg.end() && seg.start() != _c && seg.end() != _c)
        {
            if (_ab) delete _ab;
            _ab = new Segment(seg.start(), seg.end());
            _a = seg.start();
            _b = seg.end();
            return *_ab;
        }
    }

    const Segment& side_a(double x1, double y1, double x2, double y2)
    {
        Point b(x1, y1);
        Point c(x2, y2);
        if (b != c && c != _a && b != _a)
        {
            delete _bc;
            _bc = new Segment(b, c);
            _b = b;
            _c = c;
            return *_bc;
        }
    }
    const Segment& side_b(double x1, double y1, double x2, double y2)
    {

        Point c(x1, y1);
        Point a(x2, y2);
        if (a != c && a != _b && c != _b)
        {
            delete _ca;
            _ca = new Segment(c, a);
            _a = a;
            _b = c;
        }
        return *_ca;
    }

    const Segment& side_c(double x1, double y1, double x2, double y2)
    {

        Point a(x1, y1);
        Point b(x2, y2);
        if (b != a && b != _c && a != _c)
        {
            delete _ab;
            _ca = new Segment(a, b);
            _a = a;
            _b = b;
        }
        return *_ab;
    }

    friend std::ostream& operator<<(std::ostream& os, const Triangle& triangle);

    //обрахування точки-центроїда (для основи піраміди)
    Point centroid() const
    {
        double centroidX = (apexA().x() + apexB().y() + apexC().z())/3;
        double centroidY = (apexA().y() + apexB().y() + apexC().y()) / 3;
        double centroidZ = (apexA().z() + apexB().z() + apexC().z()) / 3;
        return Point(centroidX, centroidY, centroidZ);
    }



};


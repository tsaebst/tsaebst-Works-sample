#pragma once
#include "Triangle.h"
#include"Point.h"
#include <iostream>

class Pyramide
{
private:
    Point _a, _b, _c, _s;
    mutable Segment* _ab, * _bc, * _ac, * _as, * _bs, * _cs;
    Triangle *_ABC, *_ASB, *_BSC, *_CSA; // чотири грані піраміди

public:


    Pyramide(const Point& a, const Point& b, const Point& c, const Point& s)
        : _a(a), _b(b), _c(c), _s(s), _ABC(nullptr), _ASB(nullptr), _BSC(nullptr), _CSA(nullptr)
    {   

        if (!checkPyramid(a, b, c, s)) 
        {
            throw std::invalid_argument("Invalid pyramid vertices. Ensure that all vertices form a valid pyramid.");
        }
    };

    
    ~Pyramide()
    {
        _ABC = nullptr;
        _ASB = nullptr;
        _BSC = nullptr;
        _CSA = nullptr;
    }

    Pyramide& operator=(const Pyramide&);

    //Селектори і модифікатори
    const Point& apexA() const { return _a; }
    const Point& apexB() const { return _b; }
    const Point& apexC() const { return _c; }
    const Point& apexS() const { return _s; }

    Point& apexA() { return _a; }
    Point& apexB() { return _b; }
    Point& apexC() { return _c; }
    Point& apexS() { return _s; }

    // Копіювальний конструктор
    Pyramide(const Pyramide& other)
        : _a(other._a), _b(other._b), _c(other._c), _s(other._s),
        _ABC(other._ABC), _ASB(other._ASB), _BSC(other._BSC), _CSA(other._CSA) {}

    //Створення граней - Task 7
    void createFaceABC() {_ABC = new Triangle(_a, _b, _c);}
    void createFaceASB() {_ASB = new Triangle(_a, _s, _b);}
    void createFaceBSC() {_BSC = new Triangle(_b, _s, _c); }
    void createFaceCSA() {_CSA = new Triangle(_c, _s, _a); }

    // Селектори для граней
    const Triangle& faceABC() const { return *_ABC; }
    const Triangle& faceBSC() const { return *_BSC; }
    const Triangle& faceASB() const { return *_ASB; }
    const Triangle& faceCSA() const { return *_CSA; }

    // Модифікатори для вершин
    void setVertexA(const Point& a);
    void setVertexB(const Point& b);
    void setVertexC(const Point& c);
    void setVertexS(const Point& s);

    // перевірка умови для побудови піраміди
    static bool checkPyramid(const Point& a, const Point& b, const Point& c, const Point& s);
    //Перевірка на валідність граней піраміди
    bool validFaces(const Triangle& abc, const Triangle& asb, const Triangle& csa) const;
    //Обрахування об'єму пірмаміди
    double volume();
    //Утиліта виводу
    friend std::ostream& operator<<(std::ostream& os, const Pyramide& triangle);
};


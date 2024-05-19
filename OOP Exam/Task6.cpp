#include "Task6.h"


bool Pyramide::validFaces(const Triangle& abc, const Triangle& asb, const Triangle& csa) const 
{
    return (checkPyramid(abc.apexA(), abc.apexB(), abc.apexC(), _s) &&
        checkPyramid(asb.apexA(), asb.apexB(), asb.apexC(), _s) &&
        checkPyramid(csa.apexA(), csa.apexB(), csa.apexC(), _s));
}

void Pyramide::setVertexA(const Point& a)
{
    std::unique_ptr<Triangle> tempABC(new Triangle(a, _b, _c));
    std::unique_ptr<Triangle> tempASB(new Triangle(a, _s, _b));
    std::unique_ptr<Triangle> tempCSA(new Triangle(_c, _s, a));

    if (validFaces(*tempABC, *tempASB, *tempCSA)) 
    {
        _a = a;
        _ABC = std::move(tempABC.release());
        _ASB = std::move(tempASB.release());
        _CSA = std::move(tempCSA.release());
    }
    else 
    {
        throw std::invalid_argument("Invalid pyramid vertices after modification.");
    }
}

void Pyramide::setVertexB(const Point& b) {
    std::unique_ptr<Triangle> tempABC(new Triangle(_a, b, _c));
    std::unique_ptr<Triangle> tempASB(new Triangle(_a, _s, b));
    std::unique_ptr<Triangle> tempBSC(new Triangle(b, _s, _c));

    if (validFaces(*tempABC, *tempASB, *tempBSC)) 
    {
        _b = b;
        _ABC = std::move(tempABC.release());
        _ASB = std::move(tempASB.release());
        _BSC = std::move(tempBSC.release());
    }
    else 
    {
        throw std::invalid_argument("Invalid pyramid vertices after modification.");
    }
}

void Pyramide::setVertexC(const Point& c) 
{
    std::unique_ptr<Triangle> tempABC(new Triangle(_a, _b, c));
    std::unique_ptr<Triangle> tempBSC(new Triangle(_b, _s, c));
    std::unique_ptr<Triangle> tempCSA(new Triangle(c, _s, _a));

    if (validFaces(*tempABC, *tempBSC, *tempCSA)) 
    {
        _c = c;
        _ABC = std::move(tempABC.release());
        _BSC = std::move(tempBSC.release());
        _CSA = std::move(tempCSA.release());
    }
    else 
    {
        throw std::invalid_argument("Invalid pyramid vertices after modification.");
    }
}

void Pyramide::setVertexS(const Point& s) {
    std::unique_ptr<Triangle> tempASB(new Triangle(_a, s, _b));
    std::unique_ptr<Triangle> tempBSC(new Triangle(_b, s, _c));
    std::unique_ptr<Triangle> tempCSA(new Triangle(_c, s, _a));

    if (validFaces(*tempASB, *tempBSC, *tempCSA)) 
    {
        _s = s;
        _ASB = std::move(tempASB.release());
        _BSC = std::move(tempBSC.release());
        _CSA = std::move(tempCSA.release());
    }
    else 
    {
        throw std::invalid_argument("Invalid pyramid vertices after modification.");
    }
}



bool Pyramide::checkPyramid(const Point& a, const Point& b, const Point& c, const Point& s)
{
    //  чи всі точки різні
    if ((a == b) || (a == c) || (a == s) || (b == c) || (b == s) || (c == s)) 
    {
        return false;
    }
    return true;
}

Pyramide& Pyramide::operator=(const Pyramide& other)
{
    if (this != &other)
    {
        _a = other._a;
        _b = other._b;
        _c = other._c;
        _s = other._s;
        
    }
    return *this;
}

double Pyramide::volume() 
{
    if (_ABC == nullptr)
    {
        createFaceABC();
    }
    double area = _ABC->area();
    //Тепер шукаємо висоту
    double x = _s.x(); 
    double y = _s.y(); 
    double z = _s.z();
    //за формулою площини знайдемо вільний член О
    // Ax+By+Cz+O = 0
    Point AB(_b.x() - _a.x(), _b.y() - _a.y(), _b.z() - _a.z());
    Point AC(_c.x() - _a.x(), _c.y() - _a.y(), _c.z() - _a.z());
    // Обчислюємо векторний добуток векторів AB і AC
    // і коефіцієнти площини з векторного добутку:
    double A = AB.y() * AC.z() - AB.z() * AC.y();
    double B = AB.z() * AC.x() - AB.x() * AC.z();
    double C = AB.x() * AC.y() - AB.y() * AC.x();
    double O = -1 * (_a.x() * A + _a.y() * B + _a.z() * C);
    //Тепер знаходимо висоту і за загальновідомою ф-лою отримуємо об'єм
    double height = abs(A * x + B * y + C * z + O) / (sqrt(pow(A, 2) + pow(B, 2) + pow(C, 2)));
    double volume = (area * height) / 3;

    return volume;
}



std::ostream& operator<<(std::ostream& os, const Pyramide& pyr) 
{
    os << "Pyramide  vertices:" << std::endl;
    os << "A: " << pyr.apexA() << std::endl;
    os << "B: " << pyr.apexB() << std::endl;
    os << "C: " << pyr.apexC() << std::endl;
    os << "S: " << pyr.apexS() << std::endl;
    return os;
}

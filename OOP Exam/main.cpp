
#include <iostream>
#include "Task1.h"
#include "Task2.h"
#include "Task3.h"
#include "Task4.h"
#include "Task6.h"
#include "Task8.h"

int Segment::_freeID = 0;


int main()
{
    std::cout << "Work of: Spitkovska Vladyslava" << '\n';
    //Task 1
    std::cout << "*************************** Powers of 2 ****************************" << '\n';
    constexpr int exponent = 10;
    std::cout << "Let's find a series of powers of 2 from 0 to " << exponent << " :) ==> ";
    power<exponent>::print();

    //Task 3-5
    std::cout << "*************************** Double Linked Cyclic List ****************************" << '\n';
    DoubleList<int>* DLlist = new DoubleList<int>();
    //Додамо елементи в список, перевіримо, які в списку останній елемент і зробимо перевірку на наявні значення
    DLlist->append(2);
    DLlist->append(3);
    DLlist->append(4);
    DLlist->append(5);
    std::cout << "Last elemetn: " << DLlist->last() << '\n';
    std::cout << (*DLlist) << '\n';
    std::cout << "Check if list contains 5: " << ((contains(DLlist, 5)) ? "True" : "False") << '\n';
    //Вилучимо значення і зробимо дещо схоже
    DLlist->pop();
    std::cout << (*DLlist) << '\n';
    std::cout << "Check if list contains 3: " << ((contains(DLlist, 3)) ? "True" : "False") << '\n';
    std::cout << "Check if list contains 5: " << ((contains(DLlist, 5)) ? "True" : "False") << '\n';
    std::cout << "Check if list contains 4: " << ((contains(DLlist, 4)) ? "True" : "False") << '\n';

    std::cout << "*************************** Double Linked Cyclic List ****************************" << '\n';
    //Тут робитимем дещо схоже. Перевірим лист на порожність до усього і спробуємо вилучити елемент з порожнього списку
    CyclicDoubleList<int> DLCycList1;
    std::cout << "DLCycList1: " << DLCycList1 << '\n';
    std::cout << "Is list empty after creation? " << (DLCycList1.isEmpty() ? "Yes" : "No") << '\n';
    try 
    {
        DLCycList1.pop();
    }
    catch (const std::logic_error& e)
    {
        std::cerr << "Caught exception: " << e.what() << '\n';
    }

    CyclicDoubleList<int> DLCycList2;
    DLCycList2.append(1);
    DLCycList2.append(2);
    std::cout << "DLCycList2: " << DLCycList2 << '\n';
    std::cout << "Is list empty after appending elements? " << (DLCycList2.isEmpty() ? "Yes" : "No") << '\n';
    CyclicDoubleList<int> DLCycList3;
    DLCycList3.append(10);
    DLCycList3.append(20);
    DLCycList3.append(30);
    std::cout << "DLCycList3: " << DLCycList3 << '\n';
    std::cout << "Last element in the list: " << DLCycList3.last() << '\n';
    CyclicDoubleList<int> DLCycList4;
    DLCycList4.append(100);
    DLCycList4.append(200);
    DLCycList4.append(300);
    DLCycList4.pop();
    std::cout << "DLCycList4: " << DLCycList4 << '\n';
    CyclicDoubleList<int> DLCycList5;
    Iterator<int>* it = DLCycList4.iterator();
    std::cout << "Is 10 in the list? " << (contains(&DLCycList4, 10) ? "Yes" : "No") << '\n';
    std::cout << "Is 20 in the list? " << (contains(&DLCycList4, 20) ? "Yes" : "No") << '\n';
    DLCycList4.pop();
    DLCycList4.pop();
    DLCycList4.pop();
    std::cout << "DLCycList4: " << DLCycList4 << '\n';
    std::cout << "Is list empty after dleeting? " << (DLCycList4.isEmpty() ? "Yes" : "No") << '\n';


    //Task 6-7
    std::cout << "*************************** Class Pyramide ****************************" << '\n';
    // Створюємо точки для піраміди
    Point a(0, 0,0);
    Point b(1, 0, 0);
    Point c(1, -1, 0);
    Point s(1, -1, 1); // Вершина піраміди

    // Створюємо піраміду з правильними точками
    Pyramide validPyramid(a, b, c, s);
    Pyramide invertedPyr(s, c, b, a);
    //// Виводимо піраміди
    std::cout << "Pyr 1:" << validPyramid << '\n';
    std::cout <<"Pyr 2: " << invertedPyr << '\n';
    //Перевизначаємо вершини однієї піраміді вершинами іншої
    validPyramid = invertedPyr;
    //Додаємо грані
    validPyramid.createFaceABC();
    validPyramid.createFaceASB();
    validPyramid.createFaceBSC();
    validPyramid.createFaceCSA();
    std::cout << "Pyr 1 after redefinition with Pyr 2:" << validPyramid << '\n';
    // Зайвою точкою буде точка, що збігається з вершиною піраміди
    Point invalidPoint(1, 0, 0); // Зайва точка
    std::cout << "Let's try to replace point S with point with coordinates: " << invalidPoint << '\n';
    try
    {
        Pyramide invalidPyramid(a, b, c, invalidPoint);
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << "INVALID aphex replacement! " << e.what() << '\n';
    }

    std::cout << "Volume of Pyr 1:" << validPyramid.volume() << '\n';

    Point newA(0, -1, 0);
    Point newS(0.5, -0.5, 3);
    std::cout << "Let's try to replace points A, S with points with coordinates: " << newA << " and " << newS << '\n';
    validPyramid.setVertexA(newA);
    validPyramid.setVertexS(newS);
    std::cout << validPyramid << '\n';

    std::cout << "New volume of Pyr 1:" << validPyramid.volume() << '\n';
    
    //Task 8-10
    std::cout << "*************************** Class Short String ****************************" << '\n';
    ShortString<5> s1("Yay");
    ShortString<5> s2(" yay!");
    try {
        // Намагаємось створити нову на основі конкату двох
        ShortString<5> result = s1 + s2;
        std::cout << "Concatenation result: " << result << '\n';
    } catch (const BadShortString<5>& e)
    {
        std::cerr << "BadShortString caught! ";
        e.error();

        // Перетворюємо стрічки на звичайні і конкатинуємо
        String newString1 = s1.operator String();
        String newString2 = s2.operator String();
        String newResult = newString1 + newString2;
        std::cout << "WRONG short string after covertion to string & concatenation: " << newResult << '\n';
    }
    //Створюємо 2 стрічки, які можна між собою сполучити
    ShortString<20> shortStr2("Let's start a "); 
    ShortString<20> shortStr3("test"); 

    std::cout << "Short String 2: " << shortStr2 <<  '\n'; 

    ShortString<20> shortStr(" checking long sentence");
    std::cout << "Let's concat setncences 2 and 3" << '\n';
    //Виводимо
    shortStr2 += shortStr3;
    std::cout << "Concatenated string: " << shortStr2 << '\n';
    std::cout << "Let's try the same wirth setncences 1 and 2" << '\n';
    //Намагаємось зробити те саме з несумісними
    try 
    {
        shortStr2 += shortStr;

    }
    catch (const BadShortString<20>&e)
    {
        std::cerr << "BadShortString caught! ";
        e.error();
    }

    return 0;
}



 
#pragma once

//Клас ітератор
template <typename t>
class Iterator {
public:
    virtual t next() = 0;
    virtual bool hasNext() = 0;
    virtual void reset() = 0;
};
//Клас ітерованого
template <typename t>
class Iterable 
{
public:
    virtual Iterator<t>* iterator() = 0;
};
//функція перевірки навності елемента у списку
template<typename t>
bool contains(Iterable<t>* iterable, t value) 
{
    auto iterator = iterable->iterator();

    while (iterator->hasNext()) 
    {
        if (value == iterator->next()) 
        {
            return true;
        }
    }

    return false;
}


//структура елемента двозв'язного масиву
template<typename t>
struct DLItem
{
    DLItem<t>* previous;
    DLItem<t>* next;
    t item;
    DLItem(t value, DLItem<t>* prev = nullptr, DLItem<t>* nxt = nullptr)
        : item(value), previous(prev), next(nxt) {}

};

//Бзаовий клас двозв'язного масиву 
template<typename t>
class IDoubleList : public Iterable<t>
{
protected:
    bool _isEmpty;

public:
    // true, якщо елемент є порожнім
    bool isEmpty() const {return _isEmpty;}
    //Останній елемент
    virtual t last() = 0;
    //Додавання елементу
    virtual void append(t item) = 0;
    //Вилучення(видалення) елемента
    virtual t pop() = 0;
};

//Утиліта виведення
template<typename t>
std::ostream& operator<<(std::ostream& os, IDoubleList<t>& list)
{
    Iterator<t>* iter = list.iterator();
    os << "[";
    while (iter->hasNext())
    {
        os << iter->next();
        if (iter->hasNext())
        {
          os << ", ";
        }
    }
    os << "]";
    delete iter;
    return os;
}


#pragma once
#include "task2.h"
#include "task5.h"

//Клас звичайного дозв'язного списку
template<typename t>
class DoubleList : public IDoubleList<t>
{
private:
    DLItem<t>* _first;
    DLItem<t>* _last;
    bool _isEmpty;

public:
    bool isEmpty() const {return _isEmpty;}

    DoubleList() : _first(nullptr), _last(nullptr), _isEmpty(true) {}
    ~DoubleList()
    {
    #ifdef NDEBUG
            std::cout << "Element was deleted" << std::endl;
    #endif
    }

    //Додавання елементу
    void append(t item) override
    {
        //залежно від індикатора порожньості, оновлюємо значення і сам індикатор
        if (isEmpty())
        {
            _last = new DLItem<t>(item, nullptr, nullptr);
            _first = _last;
            _isEmpty = false;
        }
        else
        {
            _last = new DLItem<t>(item, _last, nullptr);
            _last->previous->next = _last;
        }
    }

    //Видалення елементу, якщо елементи присутні
    t pop() override
    {
        if (isEmpty() || _last == nullptr)
        {
            throw std::logic_error("No item to remove.");
        }

        auto last = this->_last;
        auto lastItem = last->item;

        if (_last->previous == nullptr)
        {
            _last = nullptr;
            _first = nullptr;
        }
        else {
            _last = _last->previous;
            _last->next = nullptr;
        }

        delete last;
        return lastItem;
    }

    //Знаходження останнього елементу
    t last() override
    {
        DLItem<t>* lastNode = this->_last;
        t lastItem = lastNode->item;
        return lastItem;
    }

    //Створення ітератору
    Iterator<t>* iterator() override
    {
        return new DoublyLinkedListIterator<t>(_first);
    }

};
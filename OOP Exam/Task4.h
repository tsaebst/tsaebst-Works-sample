#pragma once
#include "Task2.h"
#include "Task5.h"

//Циклічний дабллінкед список
template<typename T>
class CyclicDoubleList : public IDoubleList<T>
{
private:
    DLItem<T>* _first;
    DLItem<T>* _last;
    bool _isEmpty;

public:
    CyclicDoubleList() :_first(nullptr), _last(nullptr), _isEmpty(true) {}
    ~CyclicDoubleList() {};

    bool isEmpty() const { return _isEmpty; }

    //Далі аналогічно

    void append(T item) override 
    {
        if (isEmpty())
        {
            _last = new DLItem<T>(item, nullptr, nullptr);
            _first = _last;
            _isEmpty = false;
        }
        if (_last == nullptr)
        {
            // тільки якщо _first == nullptr 
            _last = new DLItem<T>(item);
            _last->previous = _last;
            _last->next = _last;
            _first = _last;
        }
        else
        {
            _last = new DLItem<T>(item,_last,_first);

            _last->previous->next = _last;
            _first->previous = _last;
        }
    }

    T pop() override
    {
        if (isEmpty())
        {
            throw std::logic_error("No item to remove.");
        }
        if (_last == nullptr)
        {
            throw std::logic_error("No item to remove");
        }

        auto last = this->_last;
        auto lastItem = last->item;
        //Перевіряєм чи елемент єдиний в списку і тоді робимо указники налптр
        if (_last->previous == _last) 
        {
            _last = nullptr;
            _first = nullptr; 
            _isEmpty = true;
        }
        else 
        //Інакше оновлюємо значення
        {
            _last = _last->previous;
            _last->next = _first;
            _first->previous = _last;
        }
        return lastItem;
    }

    T last() override 
    {
        return _last->item;
    }

    Iterator<T>* iterator() override 
    {
        return new CyclicDoublyLinkedListIterator<T>(_first);
    }

};


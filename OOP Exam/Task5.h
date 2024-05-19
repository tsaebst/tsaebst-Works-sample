#pragma once
#include "task2.h"

//Базовий клас ітератора на базі Ітератора
template <typename t>
class BaseDoublyLinkedListIterator : public Iterator<t> 
{
public:
    //Конструктор і деструктор
    explicit BaseDoublyLinkedListIterator(DLItem<t>* first) : first(first), current(first) {};
    ~BaseDoublyLinkedListIterator() {};
    //перехід на наступний ел
    t next() override
    {
        if (!this->hasNext())
        {
            throw std::logic_error("there's no 'next'");
        }
        // Якщо перший елемент ще не досягнуто, повертаємо його
        if (!firstItemReached) 
        {
            firstItemReached = true;
            return current->item;
        }
        // повернення  значення наступного елемента
        current = current->next;
        return current->item;
    }
    // "Скидання' ітератора на початковий елемент
    void reset() override 
{
        current = first;
        firstItemReached = false;
    }

protected:
    //Індикатор проходження 1 ел і указівники на перший і поточний елементи
    DLItem<t>* first;
    DLItem<t>* current;
    bool firstItemReached = false;
};


//Наслідувані класи ітераторів для звичайного і циклічного двозв. списків:
template <typename t>
class CyclicDoublyLinkedListIterator : public BaseDoublyLinkedListIterator<t>
{
public:
    using BaseDoublyLinkedListIterator<t>::BaseDoublyLinkedListIterator;
    bool hasNext() override
    {
        if (this->current != nullptr)
        {
            if (this->current->next != this->first)
            {
                return true;
            }
            if (!this->firstItemReached)
            {
                return true;
            }
        }
        return false;
    }
};


template <typename t>
class DoublyLinkedListIterator : public BaseDoublyLinkedListIterator<t>
{
public:
    using BaseDoublyLinkedListIterator<t>::BaseDoublyLinkedListIterator;

    bool hasNext() override
    {
        if (this->current != nullptr)
        {
            if (this->current->next != nullptr)
            {
                return true;
            }
            else
            {
                if (!this->firstItemReached)
                {
                    return true;
                }
            }
        }
        // Якщо елемент є нульовим/ нема наступного елемента і вже досягнуто перший
        return false;
    }
};

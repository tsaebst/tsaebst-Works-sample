#pragma once
#include "String.h"
#include "Task10.h"

template <int n>
class ShortString : public String
{
private:
    size_t _len;
    char* _allocator; 
    String _string; // рядок, обмежений до довжини n
public:

    // Конструктор С-рядка
    ShortString(const char* str)
    {
        if (std::strlen(str) <= n)
        {
            _string = str;
        }
        else
        {
            // якщо рядок довший за n, обрізаємо його
            char temp[n + 1];
            strncpy_s(temp, sizeof(temp), str, n);
            temp[n] = '\0'; // правильне завершення рядка
            _string = temp;
        }
    }

    //селектори довжини і рядка
    const int length() { return _len; }
    operator String() const {return _string;}

    // Утиліта виводу
    friend std::ostream& operator<<(std::ostream& os, const ShortString& ss)
    {
        os << ss._string;
        return os;
    }


    // Конкатенація +=
    void operator+=(const ShortString& other)
    {
        properLength(other);
        _string += other.operator String() ;
    }


    // Конкатенація +
    ShortString operator+(const ShortString& other)
    {
        properLength(other);
        std::string concatenated = _string.c_str();
        concatenated += other.c_str();
        return ShortString(concatenated.c_str());
    }

private:
    // Перевірка, чи не перевищує загальна довжина n
    void properLength(const ShortString& other) const
    {
        int size = std::strlen(_string.c_str()) + std::strlen(other._string.c_str());
        if (size > n)
        {
            throw BadShortString<n>("The length is over limit: ", size);
        }
    }


};
#include "String.h"
#include <cstring>
#include <iostream>
#include <cstdlib>


// Конструктор порожнього рядка 
String::String() :_allocator(new char[1]), _len(0)
{
	_allocator[0] = '\0';
#ifdef NDEBUG
	std::cout << "Created empty string: " << *this << "\n";
#endif
	return;
}




// Копіювальний мультиплік. конструктор 
String::String(const String& s, const unsigned int multiplier)
{
	_len = s._len * multiplier;
	_allocator = new char[_len + 1];
	char* newPointer = _allocator;
	size_t totalLength = s._len * multiplier;
	for (size_t i = 0; i < totalLength; i += s._len)
	{
		copy(newPointer, s._allocator, s._len);
		newPointer += s._len;
	}
	_allocator[_len] = '\0';
#ifdef NDEBUG
	std::cout << "String via copying with multiplier: " << *this << '\n';
#endif
}


// Деструктор
String::~String()
{
	delete[] _allocator;
#ifdef NDEBUG
	std::cout << "Destroyed string: " << *this << std::endl;
#endif
}


//operators lower

String& String::operator=(const char* ps)
{
	if (ps == 0) // Якщо С-рядок невизначений,
		return *this; // то виходимо, не змінюючи this
	delete[] _allocator; // Видаляємо старий рядок
	for (_len = 0; ps[_len]; _len++); // Знаходимо нове значення довжини
	_allocator = new char[_len + 1]; // Виділяємо місце для нового значення
	copy(_allocator, ps, _len);
	return *this;
}


String& String::operator=(const String& ps)
{
	if (&ps == this)
		return *this;

	delete[] _allocator;

	_len = ps._len;

	_allocator = new char[_len + 1];
	copy(_allocator, ps.c_str(), _len);
	return *this;
}

String& String::operator=(const std::string& s)
{
	if (*this == s)
		return *this;

	delete[] _allocator;

	_len = s.length();

	_allocator = new char[_len + 1];
	copy(_allocator, s.c_str(), _len);
	return *this;
}


// Оператор присвоєння символу рядку 
String& String::operator=(const char c)
{
	delete[] _allocator; // Видаляємо старий рядок
	_len = 1; // Присвоюємо нове значення довжині
	_allocator = new char[2]; // Виділяємо місце для нового значення
	_allocator[0] = c; // Копіюємо рядок на нове місце
	_allocator[1] = '\0';
	return *this;
}


// Оператор індексування для модифікації символу 
char& String::operator[](const size_t i)
{
	if (_len <= i) throw BadString("Bad index: ", i);
	return _allocator[i];
};

const char& String::operator[](const size_t i) const
{
	if (_len <= i)
	{
		throw BadString("Bad index: ", i);
	}
	return _allocator[i];
}

bool String::operator==(const String& s) const
{
	// Якщо довжини не однакові, то рядки не рівні 
	bool equal = _len == s._len;
	for (int i = 0; (i < _len) && equal; i++)
		equal = *(_allocator + i) == *(s._allocator + i);
	return equal;
}
bool String::operator==(const std::string& s) const
{
	bool equal = _len == s.length();
	for (int i = 1; (i <= _len) && equal; i++)
		equal = *(_allocator + i) == s[i - 1];
	return equal;
}




//creating new method because strcpy didn't work for the specific tasks earlier (and _CRT_SECURE_NO_WARNINGS didn't help)

void String::copy(char* destination, const char* source, size_t length)
{
	for (size_t i = 0; i < length; i++)
	{
		*(destination + i) = *(source + i);
	}
	*(destination + length) = '\0';
}


// Оператор присвоєння з конкатенацією 
String& String::operator+=(const String& s)
{
	size_t len = _len + s._len;
	char* temp = new char[len + 1];
	copy(temp, _allocator, _len);
	delete[] _allocator;
	_allocator = temp;
	copy(_allocator + _len, s._allocator, s._len);
	_len = len;
	return *this;
}

String& String::operator+=(const std::string& s)
{
	size_t len = s.length() + _len;
	char* temp = new char[len + 1];
	copy(temp, _allocator, _len);
	delete[] _allocator;
	_allocator = temp;
	copy(_allocator + _len, s.c_str(), s.length());
	_len = len;
	return *this;
}

// Присвоєння конкатенації із С-рядком 
String& String::operator+=(const char* ps) {
	if (ps == 0)
		throw BadString("Bad string: null str");
	size_t len = strlen(ps);
	char* temp = new char[len + _len + 1];
	copy(temp, _allocator, _len);
	delete[] _allocator;
	_allocator = temp;
	copy(_allocator + _len, ps, len);
	_len += len;
	return *this;
}


// Оператор конкатенації, реалізація за допомогою 
// суміщеного присвоєння 
String String::operator+(const String& s) const
{
	String res(*this);
	return res += s;
}

String String::operator+(const std::string& s) const
{
	String res(*this);
	return res += s;
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
	os << str.c_str();
	return os;
}

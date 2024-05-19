#pragma once
#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>
//#include "Task8.h"

class String {
private:

	size_t _len; // Довжина рядка
	char* _allocator; // Сам рядок
public:
	class BadString; // Клас обробки аварійних ситуацій
	String(); // Конструктор порожнього рядка

	// Конструктор мультикопіювання
	String(const String&, const unsigned int multiplayer = 1);
	~String(); // Деструктор 

	void copy(char*, const char*, size_t);
	//convertors
	const char* c_str() const { return _allocator; };
	std::string stl_str() const { return std::string(_allocator, _len); };

	// Набір операторів присвоєння 
	String& operator=(const String&); // рядка рядку
	String& operator=(const char*); // С-рядка рядку
	String& operator=(const char); // символу – рядку
	String& operator=(const std::string&); // std::string – рядку

	size_t length() const { return _len; } // Селектор довжини рядка
	bool empty() const { return _len == 0; } // Перевірка, чи рядок порожній
	void clear() { *this = String(); } // Очищення рядка

	// Оператори індексування 
	char& operator[](const size_t); // для модифікації символу
	const char& operator[](const size_t) const; // для читання символу 

	// Оператори порівняння (рівність-нерівність) 
	bool operator==(const String&) const;
	bool operator==(const std::string&) const;

	bool operator!=(const String&) const;
	bool operator!=(const std::string&) const;

	// Оператори лексикографічного порівняння 
	bool operator<(const String&) const;
	bool operator<=(const String&) const;

	bool operator>(const String&) const;
	bool operator>=(const String&) const;

	// Оператори конкатенації 
	String operator+(const String&) const;
	String operator+(const std::string&) const;
	// Присвоєння конкатенації 
	String& operator+=(const String&);
	String& operator+=(const std::string&);
	// Присвоєння конкатенації із С-рядком 
	String& operator+=(const char*);
};
// Утиліта виведення 
std::ostream& operator<<(std::ostream&, const String&);

class String::BadString
{
private:
	const std::string _reason; // Причина аварійної ситуації
	const size_t _index; // Символ, на обробці якого вона виникла
public:
	BadString(std::string reason = "", const size_t index = 0) :
		_reason(reason), _index(index)
	{
		return;
	}
	~BadString() {}
	// Діагностичне повідомлення 
	void diagnose() const
	{
		std::cerr << _reason << std::endl;
		if (_index != 0)
			std::cerr << ' ' << _index << std::endl;
	}
};
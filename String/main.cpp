﻿#include<iostream>
using namespace std;



/*

1. В классе Fraction перегрузить оператор ввода:

istream& operator>>(istream& in, Fraction& other)
{
	int integer, numerator, denominator;
	in >> integer >> numerator >> denominator;
	other.setInteger(integer);
	other.setNumerator(numerator);
	other.setDenominator(denominator);
	return in;
}

*/



#define DEBUG

class String
{
	size_t size;
	char* str;

public:
	const char* get_str()const { return str; }
	const size_t get_size()const { return size; }

	explicit String(size_t size = 80)
	{
		this->size = size;
		this->str = new char[size] {};
		#ifdef DEBUG
		cout << "DefConstructor:\t" << this << endl;
		#endif // DEBUG
	}
	String(const char str[])
	{
		this->size = strlen(str) + 1;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)
			this->str[i] = str[i];
		#ifdef DEBUG
		cout << "Constructor:\t" << endl;
		#endif // DEBUG
	}
	String(const String& other)
	{
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		#ifdef DEBUG
		cout << "CopyConstructor:" << this << endl;
		#endif // DEBUG
	}
	~String()
	{
		delete[] this->str;
		#ifdef DEBUG
		cout << "Destructor:\t" << this << endl;
		#endif // DEBUG
	}

	String& operator=(const String& other)
	{
		if (this == &other)return *this;
		delete[] this->str;
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)
			this->str[i] = other.str[i];
		#ifdef DEBUG
		cout << "CopyAssignment:\t" << this << endl;
		#endif // DEBUG

		return *this;
	}

	void print()const
	{
		cout << "size:\t" << size << endl;
		cout << "str:\t" << str << endl;
	}
};

ostream& operator<<(ostream& os, const String& obj)
{
	return os << obj.get_str();
}

String operator+(const String& left, const String& right)
{
	size_t newSize = left.get_size() + right.get_size() - 1;
	char* result = new char[newSize];

	for (size_t i = 0, j = 0; i < newSize; i++)
	{
		if (i < left.get_size() - 1)
			result[i] = left.get_str()[i];
		else {
			result[i] = right.get_str()[j];
			j++;
		}
	}

	String str(result);
	delete[] result;
	return str;
}

void main()
{
	String str1 = "Hello";
	String str2 = "World";
	String str3 = str1 + str2;
	cout << str3 << endl;
}
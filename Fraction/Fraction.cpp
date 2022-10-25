#pragma once
#include <iostream>
using namespace std;

int* Push_front(int* arr, int& size, int value)
{
	int* bufArr = new int[++size]{};
	bufArr[0] = value;

	for (int i = 1; i < size; i++)
	{
		bufArr[i] = arr[i - 1];
	}
	delete[] arr;
	return bufArr;
}



class Fraction
{
	int _integer = 0, _numerator = 0, _denominator = 1;

	char _IntToChar(int value) {
		return value + 48;
	}

	void PrintInt(int value) {

		if (value >= 10) {

			int size = 0;
			int* buf = new int[size];
			while (value)
			{
				buf = Push_front(buf, size, value % 10);
				value /= 10;
			}

			for (int i = 0; i < size; i++)
			{
				cout << _IntToChar(buf[i]);
			}
			delete[]buf;
		}
		else if (value >= 0)
			cout << _IntToChar(value);
	}

	void _CalculateInteger() {

		if (_numerator >= _denominator) {
			_integer += _numerator / _denominator;

			if (_numerator == _denominator) {
				_numerator = 0; _denominator = 1;
			}
			else
				_numerator = _numerator % _denominator;
		}
	}

public:

	Fraction(int numerator = 0, int denominator = 1) {
		setFractionalPart(numerator, denominator);
		_CalculateInteger();
	}

	Fraction(int integer, int numerator, int denominator) {
		setIntegerPart(integer);
		setFractionalPart(numerator, denominator);
		_CalculateInteger();
	}

	void setIntegerPart(int value) {
		_integer = value;
	}

	void setFractionalPart(int numerator, int denominator) {

		if (numerator > 0 && denominator > 0)
		{
			_numerator = numerator;
			_denominator = denominator;
			_CalculateInteger();
		}
	}

	int getInteger() const { return _integer; }
	int getNumerator() const { return _numerator; }
	int getDenominator() const { return _denominator; }

	Fraction& operator=(const Fraction& other) {
		this->_integer = other._integer;
		this->_numerator = other._numerator;
		this->_denominator = other._denominator;
		return *this;
	}

	void Print() {
		if (_integer != 0) {
			PrintInt(getInteger());
			cout << " ";
		}

		if (_numerator != 0) {
			PrintInt(getNumerator());
			cout << "/";
			PrintInt(getDenominator());
		}

		cout << endl;
	}
};

Fraction operator+(const Fraction& left, const Fraction& right) {
	Fraction result;
	result.setIntegerPart(left.getInteger() + right.getInteger());

	if (left.getDenominator() == right.getDenominator())
	{
		result.setFractionalPart(left.getNumerator() + right.getNumerator(), left.getDenominator());
	}

	return result;
}


int main()
{
	Fraction A(12, 2, 5);
	Fraction B(4, 5);
	Fraction C = A + B;
	A.Print();
	B.Print();
	C.Print();
}

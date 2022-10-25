#include<iostream>
using namespace std;

class Fraction
{
	int integer, numerator, denominator;

public:
#pragma region Get/Set

	int getInteger()const
	{
		return integer;
	}
	int getNumerator()const
	{
		return numerator;
	}
	int getDenominator()const
	{
		return denominator;
	}
	void setInteger(int integer)
	{
		this->integer = integer;
	}
	void setNumerator(int numerator)
	{
		this->numerator = numerator;
	}
	void setDenominator(int denominator)
	{
		if (denominator == 0)denominator = 1;
		this->denominator = denominator;
	}

#pragma endregion

#pragma region Constructor

	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "DefConstructor:\t" << this << endl;
	}
	Fraction(int integer)
	{
		setInteger(integer);
		this->numerator = 0;
		this->denominator = 1;
		cout << "1ArgConstructor:" << this << endl;
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		setNumerator(numerator);
		setDenominator(denominator);
		cout << "Constructor:\t" << this << endl;
	}
	Fraction(int integer, int numerator, int denominator)
	{
		setInteger(integer);
		setNumerator(numerator);
		setDenominator(denominator);
		cout << "Constructor:\t" << this << endl;
	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyConstructor:" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor:\t" << this << endl;
	}

#pragma endregion

#pragma region OperatorsOld

	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}

	Fraction& operator++()
	{
		integer++;
		return *this;
	}
	Fraction operator++(int)
	{
		Fraction old = *this;
		integer++;
		return old;
	}

#pragma endregion

#pragma region FunctionsOld

	Fraction& ToImproper()
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction& ToProper()
	{
		integer = numerator / denominator;
		numerator %= denominator;
		return *this;
	}
	Fraction Inverted()const
	{
		Fraction Inverted = *this;
		Inverted.ToImproper();
		swap(Inverted.numerator, Inverted.denominator);
		return Inverted;
	}
#pragma endregion

};

#pragma region operatorsOld

ostream& operator<<(ostream& os, const Fraction& obj)
{
	if (obj.getInteger())os << obj.getInteger();
	if (obj.getNumerator())
	{
		if (obj.getInteger())os << "(";
		os << obj.getNumerator() << "/" << obj.getDenominator();
		if (obj.getInteger())os << ")";
	}
	else if (obj.getInteger() == 0) os << 0;
	return os;
}
Fraction operator*(Fraction left, Fraction right)
{
	left.ToImproper();
	right.ToImproper();
	return Fraction
	(
		left.getNumerator() * right.getNumerator(),
		left.getDenominator() * right.getDenominator()
	).ToProper();
}
Fraction operator/(const Fraction& left, const Fraction& right)
{
	return left * right.Inverted();
}
Fraction operator+(Fraction left, Fraction right)
{
	left.ToImproper();
	right.ToImproper();
	return Fraction
	(
		left.getNumerator() * right.getDenominator() + right.getNumerator() * left.getDenominator(),
		left.getDenominator() * right.getDenominator()
	).ToProper();
}

#pragma endregion


void main()
{
	Fraction A(1, 2, 3);
	Fraction B(3, 4, 5);
	Fraction C = A * B;
	cout << C << endl;
	cout << A / B << endl;
	cout << A + B << endl;

	for (Fraction i(3, 4); i.getInteger() < 10; ++i)
	{
		cout << i << "\t";
	}
	cout << endl;
}
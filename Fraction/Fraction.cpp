#include<iostream>
#include<cmath>
using namespace std;
//#define DEBUG

class Fraction;
Fraction operator*(Fraction left, Fraction right);
Fraction operator/(const Fraction& left, const Fraction& right);
Fraction operator+(Fraction left, Fraction right);
Fraction operator-(Fraction left, Fraction right);
int CommonDivisor(int left, int right);

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
#ifdef DEBUG
		cout << "DefConstructor:\t" << this << endl;
#endif // DEBUG
	}
	Fraction(int integer)
	{
		setInteger(integer);
		this->numerator = 0;
		this->denominator = 1;
#ifdef DEBUG
		cout << "1ArgConstructor:" << this << endl;
#endif // DEBUG
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		setNumerator(numerator);
		setDenominator(denominator);
#ifdef DEBUG
		cout << "Constructor:\t" << this << endl;
#endif // DEBUG
	}
	Fraction(int integer, int numerator, int denominator)
	{
		setInteger(integer);
		setNumerator(numerator);
		setDenominator(denominator);
#ifdef DEBUG
		cout << "Constructor:\t" << this << endl;
#endif // DEBUG
	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
#ifdef DEBUG
		cout << "CopyConstructor:" << this << endl;
#endif // DEBUG
	}
	~Fraction()
	{
#ifdef DEBUG
		cout << "Destructor:\t" << this << endl;
#endif // DEBUG
	}

#pragma endregion

#pragma region Operators

	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
#ifdef DEBUG
		cout << "CopyAssignment:\t" << this << endl;
#endif // DEBUG
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
	Fraction& operator--()
	{
		integer--;
		return *this;
	}
	Fraction& operator()(int integer = 0, int numerator = 0, int denominator = 1)
	{
		setInteger(integer);
		setNumerator(numerator);
		setDenominator(denominator);
		return *this;
	}
	Fraction& operator*=(const Fraction& right)
	{
		return *this = *this * right;
	}
	Fraction& operator+=(const Fraction& right)
	{
		return *this = *this + right;
	}
	Fraction& operator-=(const Fraction& right)
	{
		return *this = *this - right;
	}
	Fraction& operator/=(const Fraction& right)
	{
		return *this = *this / right;
	}

#pragma endregion

#pragma region Functions

	Fraction& ToImproper()
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction Inverted()const
	{
		Fraction Inverted = *this;
		Inverted.ToImproper();
		swap(Inverted.numerator, Inverted.denominator);
		return Inverted;
	}
	Fraction& ToProper()
	{
		integer = numerator / denominator;
		numerator %= denominator;

		while (numerator < 1)
		{
			numerator += denominator;
			integer--;
		}

		if (numerator == denominator) {
			integer++;
			numerator = 0; denominator = 1;
		}

		return *this;
	}
	void Reduce()
	{
		this->ToImproper();
		int divisor = CommonDivisor(numerator, denominator);
		if (divisor > 1)
		{
			numerator /= divisor;
			denominator /= divisor;
		}
		this->ToProper();
	}
#pragma endregion

	//       =========================== Home Work ================================================

	Fraction(double value)
	{
		double integer, numerator, rounding = 100;
		numerator = modf(value, &integer);

		setInteger(value);
		setNumerator(numerator * rounding);
		setDenominator(rounding);
		ToImproper();
		Reduce();
	}
	operator int()
	{
		return this->integer;
	}

	operator double()
	{
		ToImproper();
		double answer = (double)numerator / denominator;
		ToProper();
		return answer;
	}
};

#pragma region operators

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
Fraction operator-(Fraction left, Fraction right)
{
	left.ToImproper();
	right.ToImproper();

	return Fraction
	(
		left.getNumerator() * right.getDenominator() - right.getNumerator() * left.getDenominator(),
		left.getDenominator() * right.getDenominator()
	).ToProper();
}
bool operator==(Fraction left, Fraction right)
{
	left.ToImproper(); 
	right.ToImproper();
	return left.getNumerator() * right.getDenominator() == right.getNumerator() * left.getDenominator();
}
bool operator!=(const Fraction& left, const Fraction& right)
{
	return !(left == right);
}
bool operator>(const Fraction& left, const Fraction& right)
{
	Fraction ans = left / right;
	return ans.getInteger() >= 1 && ans.getNumerator() != 0;
}
bool operator<(const Fraction& left, const Fraction& right)
{
	return !(left > right) && left != right;
}
bool operator>=(const Fraction& left, const Fraction& right)
{
	return left == right || left > right;
}
bool operator<=(const Fraction& left, const Fraction& right)
{
	return left == right || left < right;
}

#pragma endregion

int CommonDivisor(int left,int right) 
{
	if (left % right == 0) return right;

	int max = left < right ? left : right;
	for (int i = max / 2; i >= 2; i--)
	{
		if (left % i == 0 && right % i == 0) return i;
	}
	return 1;
}


void main()
{
	Fraction A(2, 3, 4);
	int a = A;
	cout << a << endl;

	double b = A;
	cout << b << endl;

	Fraction B = 2.75;
	cout << B << endl;
}
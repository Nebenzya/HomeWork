#include<iostream>
#include<Windows.h>
#include<math.h>
using namespace std;

namespace Geometry
{
	enum Color
	{
		console_default = 0x07,
		console_blue = 0x99,
		console_green = 0xAA,
		console_red = 0xCC,
		console_yellow = 0xEE,
	};

	class Shape
	{
	protected:
		Color color;
	public:
		Shape(Color color) :color(color) {}
		virtual ~Shape() {}
		virtual double area()const = 0;
		virtual double perimeter()const = 0;
		virtual void draw()const = 0;
		virtual void info()const
		{
			cout << "Площадь фигуры: " << area() << endl;
			cout << "Периметр фигуры:" << perimeter() << endl;
			draw();
		}
	};

	class Square :public Shape
	{
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			if (side < 5)side = 5;
			if (side > 20)side = 20;
			this->side = side;
		}
		//				Constructors:
		Square(double side, Color color) :Shape(color)
		{
			set_side(side);
		}
		~Square() {}
		double area()const override
		{
			return side * side;
		}
		double perimeter()const override
		{
			return side * 4;
		}
		void draw()const override
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < side; i++)
			{
				for (int j = 0; j < side; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::console_default);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны квадрата: " << side << endl;
			Shape::info();
		}
	};

	class Rectangle :public Shape
	{
		double width;
		double length;
	public:
		double get_width()const
		{
			return width;
		}
		double get_length()const
		{
			return length;
		}
		void set_width(double width)
		{
			if (width < 8)width = 8;
			if (width > 30)width = 30;
			this->width = width;
		}
		void set_length(double length)
		{
			if (length < 3)length = 3;
			if (length > 20) length = 20;
			this->length = length;
		}
		Rectangle(double width, double length, Color color) :Shape(color)
		{
			set_width(width);
			set_length(length);
		}
		~Rectangle() {}
		double area()const override
		{
			return width * length;
		}
		double perimeter()const override
		{
			return (width + length) * 2;
		}
		void draw()const
		{
			//1) Получаем окно консоли:
			HWND hwnd = GetConsoleWindow();
			//2) Получаем контекст устройства для окна консоли:
			HDC hdc = GetDC(hwnd);	//это то, на чем мы будем рисовать

			//3) Создаем карандаш - это то, чем мы будем рисорвать (карандаш рисует линии):
			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			//4) Создаем кисть. Кисть рисует заливку в замкнутой фигуре
			HBRUSH hBrush = CreateSolidBrush(color);
			//5) Выбираем чем, и на чем мы будем рисорвать:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//6) Рисуем прямоугольник:
			::Rectangle(hdc, 100, 100, 500, 300);

			//Удаляем карандаш:
			DeleteObject(hPen);

			//Освобождаем контекст устройства:
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Ширина: " << width << endl;
			cout << "Длина:  " << length << endl;
			Shape::info();
		}
	};

	class Triangle : public Shape 
	{
		double sideA;
		double sideB;
		double sideC;
	public:

		void set_AllSide(double A, double B, double C)
		{
			this->sideA = A;
			this->sideB = B;
			this->sideC = C;
		}

		Triangle(double A, double B, double C, Color color) :Shape(color)
		{
			set_AllSide(A,B,C);
		}

		double area()const override
		{
			double half_perimeter = perimeter() / 2;
			return sqrt(half_perimeter * (half_perimeter - sideA) * (half_perimeter - sideB) * (half_perimeter - sideC));
		}

		double perimeter()const override
		{
			return sideA + sideB + sideC;
		}
		void draw()const override
		{
			//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			//SetConsoleTextAttribute(hConsole, color);

			int maxSide = sideB > sideC ? sideB : sideC;
			maxSide = sideA > maxSide ? sideA : maxSide;

			double height = 2 * area() / maxSide;

			double unitOfPointers = maxSide / height;

			for (int i = 1; i < height+1; i++)
			{
				int countPointers = unitOfPointers * i;
				for (int j = 0; j < maxSide; j++)
				{
					int startPoint = (maxSide - countPointers)* (sideA / (sideA + sideB));
					if (j >= startPoint && j <= startPoint + countPointers)
						cout << "*";
					else
						cout << " ";
				}
				cout << endl;
			}
			//SetConsoleTextAttribute(hConsole, Color::console_default);
		}


		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона А: " << sideA << endl;	
			cout << "Сторона B: " << sideB << endl;
			cout << "Сторона C: " << sideC << endl;
			Shape::info();
		}
	};
}

void main()
{
	setlocale(LC_ALL, "");
	Geometry::Triangle tri(30, 40, 60, Geometry::Color::console_green);
	cout << tri.area() << endl;
	tri.draw();
}
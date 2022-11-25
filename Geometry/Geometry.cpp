#define _USE_MATH_DEFINES
#include<iostream>
#include<Windows.h>
using namespace std;

namespace Geometry
{
	enum Color
	{
		red = 0x000000FF,
		green = 0x0000FF00,
		blue = 0x00FF0000,
		yellow = 0x0000AAFF,
		white = 0x00FFFFFF,
		grey = 0x00AAAAAA,

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

		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw(int x, int y, int cWidth)const = 0;
		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры:" << get_perimeter() << endl;
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
			this->width = width;
		}
		void set_length(double length)
		{
			this->length = length;
		}

		Rectangle(double width, Color color) :Shape(color)
		{
			set_width(width);
			set_length(width);
		}

		Rectangle(double width, double length, Color color) :Shape(color)
		{
			set_width(width);
			set_length(length);
		}

		double get_area()const override
		{
			return width * length;
		}
		double get_perimeter()const override
		{
			return (width + length) * 2;
		}
		void draw(int x, int y, int cWidth)const override
		{
			//1) Получаем окно консоли:
			HWND hwnd = GetConsoleWindow();
			//2) Получаем контекст устройства для окна консоли:
			HDC hdc = GetDC(hwnd);	//это то, на чем мы будем рисовать

			//3) Создаем карандаш - это то, чем мы будем рисорвать (карандаш рисует линии):
			HPEN hPen = CreatePen(PS_SOLID, cWidth, color);
			//4) Создаем кисть. Кисть рисует заливку в замкнутой фигуре
			HBRUSH hBrush = CreateSolidBrush(color);
			//5) Выбираем чем, и на чем мы будем рисорвать:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//6) Рисуем прямоугольник:
			::Rectangle(hdc, x, y, x + width, y + length);

			//Удаляем карандаш:
			DeleteObject(hPen);
			DeleteObject(hBrush);

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
	class Circle :public Shape
	{
		double radius;
	public:
		double get_radius()const
		{
			return radius;
		}
		void set_radius(double radius)
		{
			this->radius = radius;
		}
		Circle(double radius, Color color) :Shape( color)
		{
			set_radius(radius);
		}

		double get_area()const override
		{
			return M_PI * radius * radius;
		}
		double get_perimeter()const override
		{
			return 2 * M_PI * radius;
		}
		void draw(int x, int y, int cWidth)const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, cWidth, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Ellipse(hdc, x, y, x + radius * 2, y + radius * 2);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Radius:\t" << radius << endl;
			Shape::info();
		}
	};

	class Triangle :public Shape
	{
		const static int COUNT_SIDES = 3;

		enum TriangleType
		{
			Ordinary,
			Equilateral,
			Rectangular
		};

		double sideA, sideB, sideC;
		TriangleType type;
	public:

		void set_side(double a, double b, double c)
		{
			sideA = a; sideB = b; sideC = c;
		}

		Triangle(double side, Color color) :Shape(color)
		{
			set_side(side, side, side);
			type = TriangleType::Equilateral;
		}

		Triangle(double a, double b, double c, Color color) :Shape(color)
		{
			if (a * a + b * b == c * c) type = TriangleType::Rectangular;
			else type = TriangleType::Ordinary;

			set_side(a, b, c);
		}

		double get_height()const { return 2 * get_area() / sideA; }
		double get_area()const override { return sideA * sideB * sqrt(3) / 4; }
		double get_perimeter()const override { return sideA + sideB + sideC; }

		void draw(int x, int y, int cWidth)const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, cWidth, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT vert[COUNT_SIDES]{};

			switch (type)
			{
			case Geometry::Triangle::Ordinary:
				break;
			case Geometry::Triangle::Equilateral:
				vert[0] = POINT{x, long(y + sideA)};
				vert[1] = POINT{ long(x + sideA), long(y + sideA) };
				vert[2] = POINT{ long(x + sideA / 2), long(y + sideA - get_height()) };
				break;
			case Geometry::Triangle::Rectangular:
				vert[0] = POINT{ x, y };
				vert[1] = POINT{ long(x + sideB), y};
				vert[2] = POINT{ x, long(y + sideA) };
				break;
			default:
				break;
			}

			::Polygon(hdc, vert, COUNT_SIDES);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}

		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Side A:\t" << sideA << endl;
			cout << "Side B:\t" << sideB << endl;
			cout << "Side C:\t" << sideC << endl;
			cout << "Height:\t" << get_height() << endl;
			Shape::info();
		}
	};
}

void main()
{
	setlocale(LC_ALL, "");
	//Shape shape;
	Geometry::Rectangle square(100, Geometry::Color::console_red);
	square.draw(100, 100, 1);

	Geometry::Rectangle rect(150, 70, Geometry::Color::grey);
	rect.draw(300, 100, 1);

	Geometry::Circle circle(80, Geometry::Color::yellow);
	circle.draw(500, 100, 1);

	Geometry::Triangle e_try(170, Geometry::Color::green);
	e_try.draw(350, 200, 1);

	Geometry::Triangle triangular(150, 200, 250, Geometry::Color::blue);
	triangular.draw(100, 220, 1);
}
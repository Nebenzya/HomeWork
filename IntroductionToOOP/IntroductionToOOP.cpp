#include <iostream>
#include <cmath>
using namespace std;

class Point
{
private:

    double x, y;

    bool CheckValue(double value) { return value >= 0 && value <= 100; }

public:

    Point() { x = y = 0; }
    Point(double x, double y) { setX(x); setY(y); }

    double getX() { return x; }
    double getY() { return y; }

    void setX(double value) 
    {
        if (CheckValue(value))
            x = value;
    }

    void setY(double value)
    {
        if (CheckValue(value))
            y = value;
    }

    double Distance(Point obj) 
    {
        return pow(pow(x - obj.x, 2) + pow(y - obj.y, 2), 0.5);
    }
};

double Distance(Point A, Point B) 
{
    // pow(pow(A.getX() - B.getX(), 2) + pow(A.getY() - B.getY(), 2), 0.5);
    return A.Distance(B);
}

int main()
{
    Point A(1.72, 3.12);
    Point B(5.91, 0.39);
    
    cout << A.Distance(B) << endl;

    cout << Distance(A, B) << endl;
}

#include <iostream>
using namespace std;

class Point
{
private:

    double x = 0;
    double y = 0;

    bool CheckValue(double value) 
    {
        return value >= 0 && value <= 100;
    }

public:
    
    double GetX() 
    { 
        return x; 
    }
    double GetY()
    {
        return y;
    }

    void SetX(double value) 
    {
        if (CheckValue(value))
            x = value;
    }

    void SetY(double value)
    {
        if (CheckValue(value))
            y = value;
    }

    void Print() 
    {
        cout << x << "\t" << y << endl;
    }
};


int main()
{
    Point A;

    A.SetX(13.41);
    A.SetY(1.73);
    
    cout << A.GetX() << "\t" << A.GetY() << endl;
    A.Print();

    return 0;
}

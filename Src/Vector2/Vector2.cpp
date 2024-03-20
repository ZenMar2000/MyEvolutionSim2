#include "../../Headers/Vector2/Vector2.hpp"

// Constructors
Vector2::Vector2()
{
    x = 0;
    y = 0;
}

Vector2::Vector2(int xValue, int yValue)
{
    x = xValue;
    y = yValue;
}

// Functions
double Vector2::Length() 
{
    return abs(sqrt(x * x + y * y));
}

double Vector2::Distance(Vector2 v) 
{
    return abs(sqrt(pow(v.x - x, 2) + pow(v.y - y, 2)));
}

int Vector2::Dot(Vector2 v) 
{
    return x * v.x + y * v.y;
}

void Vector2::Sum(Vector2 v)
{
    x += v.x;
    y += v.y;
}

Vector2 Vector2::GetSum(Vector2 v)
{
    return Vector2(x + v.x, y + v.y);
}

void Vector2::Print()
{
    cout << "X: " + to_string(x) + " Y: " + to_string(y) << endl;
}

Vector2 Zero(0, 0);

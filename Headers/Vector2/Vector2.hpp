#ifndef VECTOR2_H
#define VECTOR2_H

#include <math.h>
#include <iostream>
using namespace std;

class Vector2
{
public:
    // Variables
    int x;
    int y;

    // Constructors
    Vector2();
    Vector2(int xValue, int yValue);

    // Functions
    int Length() const;
    int Distance(const Vector2 &v) const;
    int Dot(const Vector2 &v) const;
    Vector2 Sum(const Vector2 &v) const;
    void Print();
};

#endif
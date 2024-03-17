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

    //Sum the vector2 passed to the current vector2
    void Sum(Vector2 v);

    //Get the sum between current vector2 and the vector passed. Performs NO operations to the current Vector2
    Vector2 GetSum(Vector2 v);

    void Print();
};

#endif
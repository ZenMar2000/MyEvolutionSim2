#include "../../Headers/Vector2/Vector2.hpp"

//Constructors
Vector2::Vector2(){
    x = 0;
    y = 0;
}

Vector2::Vector2(int xValue, int yValue){
    x = xValue;
    y = yValue;
}


//Functions
int Vector2::Length() const{
    return sqrt(x * x + y * y);
}

int Vector2::Distance(const Vector2 &v) const{
    return sqrt(pow(x - v.x, 2) + pow(y - v.y, 2));
}

int Vector2::Dot(const Vector2 &v) const{
    return x * v.x + y * v.y;
}

Vector2 Vector2::Sum(const Vector2 &v) const {
    return Vector2(x + v.x, y + v.y);
}

void Vector2::Print(){
    cout << "X: " + to_string(x) + " Y: " + to_string(y) << endl;
}


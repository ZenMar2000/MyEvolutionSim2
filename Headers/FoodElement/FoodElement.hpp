#ifndef FOODELEMENT_H
#define FOODELEMENT_H

#include <iostream>
#include <vector>

#include "../Utils.hpp"

using namespace std;

class FoodElement
{
public:
#pragma region "Public Variables"
    Vector2 FoodPosition;

#pragma endregion

#pragma region "Constructors"
    FoodElement(Vector2 FoodPosition, bool foodRespawnable = true);

#pragma endregion

#pragma region "Public Functions"
    void RespawnFood(Vector2 newPosition);
    bool IsFoodEnabled();
    bool IsfoodRespawnable();

#pragma endregion

protected:
#pragma region "Protected Variables"
    bool foodRespawnable;
    bool foodEnabled;

#pragma endregion
};

#endif
#include "../../Headers/FoodElement/FoodElement.hpp"

#pragma region "Constructors"

FoodElement::FoodElement(Vector2 FoodPosition, bool foodRespawnable)
{
    this->FoodPosition = FoodPosition;
    this->foodRespawnable = foodRespawnable;
    foodEnabled = true;
}

#pragma endregion

#pragma region "Public Functions"
void FoodElement::RespawnFood(Vector2 newPosition)
{
    if (foodRespawnable)
    {
        FoodPosition = newPosition;
    }
    else
    {
        FoodPosition = Vector2(-1, -1);
        foodEnabled = false;
    }
}

bool FoodElement::IsFoodEnabled()
{
    return foodEnabled;
}

bool FoodElement::IsfoodRespawnable()
{
    return foodRespawnable;
}

#pragma endregion
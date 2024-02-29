#define WindowWidth 800
#define WindowHeight 600
#define CellPixelsDimension 5

#include "../Headers/Vector2/Vector2.hpp"

#pragma region "Directions"
int DirectionsAmount = 8;
Vector2 Directions[DirectionsAmount]{Vector2(-1,-1), Vector2(0,-1), Vector2(1,-1), Vector2(1,0), Vector2(1,1), Vector2(0,1), Vector2(-1,1), Vector2(-1,0)};

/* 
Directions indexes
    0	1	2
    7		3
  	6	5	4
*/

Vector2 GetDirection(int DirectionIndex){
    return Directions[DirectionIndex];
}
#pragma endregion

// enum Coordinate {
//     X,
//     Y
// };

// static const double NormalizeToWindowDimension(Vector2 position, Coordinate coordinate){

// };


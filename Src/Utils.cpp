#include "../Headers/Utils.hpp"

#pragma region "Constructors"
Utils::Utils(){
    Directions = new Vector2[8]{Vector2(-1,-1), Vector2(0,-1), Vector2(1,-1), Vector2(1,0), Vector2(1,1), Vector2(0,1), Vector2(-1,1), Vector2(-1,0)};
}
#pragma endregion


#pragma region "Functions"
Vector2 Utils::GetDirection(int DirectionIndex){
    return Directions[DirectionIndex];
}

double Utils::NormalizeToGridimention(Vector2 position, Coordinate coordinate){
  std::cout << "Not implemented yet" << endl;
  return 0;
}
#pragma endregion

// /* 
//  Directions indexes
//  0   1   2
//  7       3
//  6   5   4
// */
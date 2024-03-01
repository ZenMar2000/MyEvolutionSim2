#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include "Vector2/Vector2.hpp"

class Utils{
  public:
  //Variables
  static const int DirectionsAmount = 8;
  static const int CellPixelsDimension = 5;
  static const int WindowWidth = 800;
  static const int WindowHeight = 600;
  Vector2* Directions;

  enum Coordinate{x,y};

#pragma region "Constructors"
Utils(); // Declaration only, no definition here

#pragma endregion

#pragma region "Functions"
  //Return a normalized vector corresponding to the direction index passed
  Vector2 GetDirection(int DirectionIndex);

  //return a number between 0 and 1, where 0 is coordinate 0 and 1 is the max width or height of the grid
  double NormalizeToGridimention(Vector2 position, Coordinate coordinate);
#pragma endregion
};

#endif
  
/* 
Directions indexes
    0	1	2
    7		3
  	6	5	4
*/

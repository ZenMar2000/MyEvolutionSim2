#include "../Headers/Utils.hpp"

#pragma region "Constructors"
Utils::Utils()
{
  Directions = new Vector2[8]{Vector2(-1, -1), Vector2(0, -1), Vector2(1, -1), Vector2(1, 0), Vector2(1, 1), Vector2(0, 1), Vector2(-1, 1), Vector2(-1, 0)};
  InstantiateNodesArrays();
}
#pragma endregion

#pragma region "Functions"
Vector2 Utils::GetDirection(int DirectionIndex)
{
  return Directions[DirectionIndex];
}

double Utils::NormalizeToGridimention(Vector2 position, Coordinate coordinate)
{
  std::cout << "Not implemented yet" << endl;
  return 0;
}

NodeType Utils::GetRandom_InputNode(){

};

NodeType Utils::GetRandom_NeuronNode(){

};

NodeType Utils::GetRandom_ActionNode(){

};

void Utils::InstantiateNodesArrays(){
  //TODO For each NodeType enum, check left most 2 bits and 
  //Divide them in the 3 arrays InputNodes, NeuronNodes or ActionNodes
}
#pragma endregion

// /*
//  Directions indexes
//  0   1   2
//  7       3
//  6   5   4
// */
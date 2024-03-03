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

double Utils::NormalizeToGridDimention(Vector2 position, Coordinate coordinate)
{
  // TODO
  std::cout << "Not implemented yet" << endl;
  return 0;
}

NodeType Utils::GetRandom_InputNode()
{
  // TODO
}

NodeType Utils::GetRandom_NeuronNode()
{
  // TODO
}

NodeType Utils::GetRandom_ActionNode()
{
  // TODO
}

void Utils::InstantiateNodesArrays()
{
  // TODO For each NodeType enum, check left most 2 bits and
  // Divide them in the 3 arrays InputNodes, NeuronNodes or ActionNodes
}

string Utils::bin_to_hex(string binary)
{
  binary = string(binary.length() % 4 ? 4 - binary.length() % 4 : 0, '0') + binary;

  string hexadecimal;
  for (size_t i = 0; i < binary.length(); i += 4)
  {
    string group = binary.substr(i, 4);
    hexadecimal += hex_dict[group];
  }
  return hexadecimal;
}

string Utils::hex_to_bin(string str)
{
  string binary;

  char arr[str.length() + 1];
  strcpy(arr, str.c_str());

  for (int i = 0; i < str.length(); i++)
  {
    binary += bin_dict.at(toupper(arr[i]));
  }

  return binary;
}

#pragma endregion

// /*
//  Directions indexes
//  0   1   2
//  7       3
//  6   5   4
// */
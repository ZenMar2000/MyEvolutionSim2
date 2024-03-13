#include "../Headers/Utils.hpp"

#pragma region "Constructors"
Utils::Utils()
{
  Directions = new Vector2[DirectionsAmount]{Vector2(-1, -1), Vector2(0, -1), Vector2(1, -1), Vector2(1, 0), Vector2(1, 1), Vector2(0, 1), Vector2(-1, 1), Vector2(-1, 0)};
  // InstantiateNodesArrays();
}
#pragma endregion

#pragma region "Functions"
Vector2 Utils::GetDirection(int directionIndex)
{
  directionIndex %= DirectionsAmount;

  return Directions[directionIndex];
}

int Utils::GetDirectionIndex(Vector2 direction)
{
  for (int i = 0; i < DirectionsAmount; i++)
  {
    if (Directions[i].x == direction.x && Directions[i].y == direction.y)
    {
      return i;
    }
  }
  return -1;
}

int Utils::GetDirectionIndex(int directionIndex)
{
  return directionIndex%DirectionsAmount;
}

double Utils::NormalizeToGridDimention(Vector2 position, Coordinate coordinate)
{
  // TODO
  std::cout << "Not implemented yet" << endl;
  return 0;
}

NodeId Utils::GetRandom_InputNode()
{
  // TODO
}

NodeId Utils::GetRandom_NeuronNode()
{
  // TODO
}

NodeId Utils::GetRandom_ActionNode()
{
  // TODO
}

int Utils::GetNodeType(NodeId id)
{
  // string binary = bitset<8>(id).to_string();
  return bin_to_int(bitset<8>(id).to_string().substr(0, 2));
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

string Utils::hex_to_bin(string hexadecimal)
{
  string binary;

  char arr[hexadecimal.length() + 1];
  strcpy(arr, hexadecimal.c_str());

  for (int i = 0; i < hexadecimal.length(); i++)
  {
    binary += bin_dict.at(toupper(arr[i]));
  }

  return binary;
}

int Utils::bin_to_int(string binary)
{
  return stoi(binary, nullptr, 2);
}

#pragma endregion

#pragma region "Protected Functions"

// void Utils::InstantiateNodesArrays()
// {
//   NodeId currentNodeId;
//   int currentNodeType;

//   for (int i = 0; i < LAST; i++)
//   {
//     try
//     {
//       currentNodeId = static_cast<NodeId>(i); // static_cast<NodeId>(i)
//       // if(currentNodeId.to_string().size() > 3){

//       // }
//       currentNodeType = GetNodeType(currentNodeId);
//       NodeTypeList[currentNodeType].push_back(currentNodeId);
//     }
//     catch (const std::exception &e)
//     {
//       continue;
//     }
//   }
// }
#pragma endregion
// /*
//  Directions indexes
//  0   1   2
//  7       3
//  6   5   4
// */
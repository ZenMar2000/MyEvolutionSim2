#include "../Headers/Utils.hpp"

#pragma region "Constructors"
Utils::Utils()
{
}
#pragma endregion

#pragma region "Functions"
Vector2 Utils::GetDirection(DirectionsIndex directionIndex)
{
  directionIndex = (DirectionsIndex)(directionIndex % DirectionsAmount);

  return Directions[(int)directionIndex];
}

DirectionsIndex Utils::GetDirectionIndex(Vector2 direction)
{
  for (int i = 0; i < DirectionsAmount; i++)
  {
    if (Directions[i].x == direction.x && Directions[i].y == direction.y)
    {
      return (DirectionsIndex)i;
    }
  }
  return DIRECTION_NULL;
}

DirectionsIndex Utils::GetDirectionIndex(DirectionsIndex directionIndex)
{
  return (DirectionsIndex)(directionIndex % DirectionsAmount);
}

double Utils::NormalizeToGridDimention(Vector2 position, Coordinate coordinate)
{
  // TODO
  std::cout << "Not implemented yet" << endl;
  return 0;
}

NodeId Utils::GetRandomNode(NodeType nodeType)
{
  return NodeTypeList[nodeType][GetRandomInt(0, NodeTypeList[nodeType].size())];
}

NodeType Utils::GetNodeType(NodeId id)
{
  // string binary = bitset<8>(id).to_string();
  return (NodeType)bin_to_int(bitset<8>(id).to_string().substr(0, 2));
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

NodeType Utils::GetNodeType(string id)
{
  // string binary = bitset<8>(id).to_string();
  return (NodeType)bin_to_int(bitset<8>(id).to_string().substr(0, 2));
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

int Utils::GetRandomInt(int min, int max)
{
  return (rand() + min) % max;
}
double Utils::GetRandomPercent()
{
  uniform_real_distribution<double> unif(0, 1);
  default_random_engine re;
  return unif(re);
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
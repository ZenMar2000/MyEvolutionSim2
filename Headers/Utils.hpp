#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <unordered_map>
#include <bits/stdc++.h>
#include <random>
#include <time.h>

#include "Vector2/Vector2.hpp"
class Cell;
/*Directions indexes
    0	1	2
    7		3
    6	5	4
*/
enum DirectionsIndex
{
  DIRECTION_NW = 0,
  DIRECTION_N = 1,
  DIRECTION_NE = 2,
  DIRECTION_E = 3,
  DIRECTION_SE = 4,
  DIRECTION_S = 5,
  DIRECTION_SW = 6,
  DIRECTION_W = 7,
  DIRECTION_NULL = 8
};

enum NodeId
{
  // Input from 0 to 63
  INPUT_HDP = 0,  // (Implemented) Normalized Horizontal distance from left border
  INPUT_VDP = 1,  // (Implemented) Normalized Vertical distance from top border
  INPUT_HDO = 2,  // (Implemented) Normalized Horizontal distance from left border, opposite value
  INPUT_VDO = 3,  // (Implemented) Normalized Vertical distance from top border, opposite value
  INPUT_FPD = 4,  // Forward population density
  INPUT_LPD = 5,  // Left population density
  INPUT_RPD = 6,  // Right population density
  INPUT_FRC = 7,  // (Implemented) Food reserve counter
  INPUT_FRO = 8,  // (Implemented) Food reserve counter, opposite value
  INPUT_FSD = 9,  // Closest food source Normalized distance
  INPUT_FSA = 10, // Closest food source angle, relative to forward direction. Return (Food position relative DirectionIndex angle) - (CellDirection index)
  INPUT_CCD = 11, // Closest cell Normalized distance
  INPUT_CCA = 12, // Closest cell angle, relative to forward direction. Return (Other cell position relative DirectionIndex angle) - (CellDirection index)
  INPUT_CCC = 13, // Closest cell compatibility (how similar their genome is)
  INPUT_OSC = 14, // Oscilloscope. Sin function between 0 and 1.
  INPUT_RND = 15, // (Implemented) Random valuse
  INPUT_BLK = 16, // (Implemented) Next forward space is blocked

  // Neurons from 64 to 127
  NEURON = 64, // Neuron

  // Actions from 128 to 191
  ACTION_TCW = 128, // (Implemented) Turn clockwise
  ACTION_TCC = 129, // (Implemented) Turn counterclockwise
  ACTION_MFW = 130, // (Implemented) Move forward
  ACTION_MBW = 131, // (Implemented) Move backward
  ACTION_CXP = 132, // (Implemented) Cartesian movement on X axis, positive
  ACTION_CXN = 133, // (Implemented) Cartesian movement on X axis, negative
  ACTION_CYP = 134, // (Implemented) Cartesian movement on Y axis, positive
  ACTION_CYN = 135, // (Implemented) Cartesian movement on Y axis, negative
  ACTION_PRM = 136, // Release pheromones.
  ACTION_TGL = 137, // Trigger level. usually set to 0. It increase or reduce the % needed to trigger all action nodes.
  ACTION_SOC = 138, // Set oscilloscope frequency

  // Free range from 192 to 255
  FREE = 192,
  LAST = 256
};

enum NodeType
{
  TYPE_INPUT = 0,
  TYPE_NEURON = 1,
  TYPE_ACTION = 2,
  TYPE_FREE = 3
};

static const Vector2 Directions[8]{Vector2(-1, -1), Vector2(0, -1), Vector2(1, -1), Vector2(1, 0), Vector2(1, 1), Vector2(0, 1), Vector2(-1, 1), Vector2(-1, 0)};

class Utils
{
public:
#pragma region "Simulation Variables"
  // Speed of the simulation. Lower number = faster simulation
  static const int UpdateDelay = 100;

  //Cells data
  static const int baseGenomeLength = 5;
  static const int StartingFood = 100;

  // Dimension of the cell in pixels
  static const int CellPixelsDimension = 10;

  // width and height of the window. Pick 2 numbers divisible by CellPixelsDimension
  static const int WindowWidth = 800;
  static const int WindowHeight = 600;

  // If food is enabled during the simulation. When a cell reach 0 food, it dies
  bool foodEnabled = true;

#pragma endregion

  // No. Don't touch this variable
  static const int DirectionsAmount = 8;

  unordered_map<string, char> hex_dict = {
      {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'}, {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'}, {"1000", '8'}, {"1001", '9'}, {"1010", 'A'}, {"1011", 'B'}, {"1100", 'C'}, {"1101", 'D'}, {"1110", 'E'}, {"1111", 'F'}};

  unordered_map<char, string> bin_dict = {
      {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"}, {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"}, {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"}, {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}};

#pragma region "Constructors"
  Utils();

#pragma endregion

#pragma region "Functions"
  // Return a normalized vector corresponding to the direction index passed
  Vector2 GetDirection(DirectionsIndex directionIndex);
  DirectionsIndex GetDirectionIndex(Vector2 direction);
  DirectionsIndex GetDirectionIndex(DirectionsIndex directionIndex);

  // return a number between 0 and 1, where 0 is coordinate 0 and 1 is the max width or height of the grid

  NodeId GetRandomNode(NodeType nodeType);

  NodeType GetNodeType(NodeId id);
  NodeType GetNodeType(string id);

  string bin_to_hex(string binary);
  string hex_to_bin(string hexadecimal);
  int bin_to_int(string binary);

  // Get random int between min (included) and max(not included)
  int GetRandomInt(int min = 0, int max = 100);

  // Get random double between 0 and 1
  double GetRandomPercent();

  double GetWindowNormalizedDistance(Vector2 targetPosition, Vector2 startingPosition = Vector2());

  int GetNodeTypeListSize(NodeType type);

#pragma endregion

protected:
#pragma region "Protected Variables"
  // Arrays of NodeTypes used for subdividing the Enum. Used for random generation
  // Use the GetNodeType() function to get the correct vector:
  // 0 = Input, 1 = Neuron, 2 = Action, 3 = Free
  vector<NodeId> NodeTypeList[4] = {
      // Input Nodes
      {INPUT_HDP, INPUT_VDP, INPUT_HDO, INPUT_VDO, /* INPUT_FPD, INPUT_FPD, INPUT_RPD,*/
       INPUT_FRC, INPUT_FRO,                       /* INPUT_FSD, INPUT_FSA, INPUT_CCD, INPUT_CCA,INPUT_CCC, INPUT_OSC,  */
       INPUT_RND, INPUT_BLK},

      // Neuron
      {NEURON},

      // Action Nodes
      {
          ACTION_TCW, ACTION_TCC, ACTION_MFW, ACTION_MBW, ACTION_CXP,
          ACTION_CXN, ACTION_CYP, ACTION_CYN /* , ACTION_PRM, ACTION_TGL,
           ACTION_SOC */
      },

      // Free
      {FREE, LAST}};

#pragma endregion

#pragma region
  // void InstantiateNodesArrays();

#pragma endregion
};

struct Color
{
  int r; // red component
  int g; // green component
  int b; // blue component
  int a; // alpha

  Color(int red, int green, int blue)
  {
    r = red;
    g = green;
    b = blue;
  }
};
#endif
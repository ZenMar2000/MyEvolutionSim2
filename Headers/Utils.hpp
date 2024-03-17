#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <unordered_map>
#include <bits/stdc++.h>
#include <random>

#include "Vector2/Vector2.hpp"

/*
Directions indexes
    0	1	2
    7		3
    6	5	4
*/

enum NodeId
{
  // Input from 0 to 63
  INPUT_HDC = 0,  // Normalized Horizontal distance from left border
  INPUT_VDC = 1,  // Normalized Vertical distance from top border
  INPUT_FPD = 2,  // Forward population density
  INPUT_LPD = 3,  // Left population density
  INPUT_RPD = 4,  // Right population density
  INPUT_FRC = 5,  // Food reserve counter
  INPUT_FSD = 6,  // Closest food source distance
  INPUT_FSA = 7,  // Closest food source angle, relative to forward direction
  INPUT_CCD = 8,  // Closest cell distance
  INPUT_CCA = 9,  // Closest cell angle, relative to forward direction
  INPUT_CCC = 10, // Closest cell compatibility (how similar their genome is)
  INPUT_OSC = 11, // Oscilloscope
  INPUT_RND = 12, // Random valuse
  INPUT_BLK = 13, // Next forward space is blocked

  // Neurons from 64 to 127
  NEURON = 64, // Neuron

  // Actions from 128 to 191
  ACTION_TCW = 128, // Turn clockwise
  ACTION_TCC = 129, // Turn counterclockwise
  ACTION_MFW = 130, // Move forward
  ACTION_MBW = 131, // Move backward
  ACTION_CXM = 132, // Cartesian movement on X axis
  ACTION_CYM = 133, // Cartesian movement on Y axis
  ACTION_PRM = 134, // Release pheromones.
  ACTION_TGL = 135, // Trigger level. usually set to 0.5. It increase or reduce the % needed to trigger all action nodes.
  ACTION_SOC = 136, // Set oscilloscope frequency

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

class Utils
{
public:
  // Variables
  static const int DirectionsAmount = 8;
  static const int CellPixelsDimension = 10;
  static const int WindowWidth = 800;
  static const int WindowHeight = 600;

  static const int UpdateDelay = 100;

  Vector2 *Directions;

  unordered_map<string, char> hex_dict = {
      {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'}, {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'}, {"1000", '8'}, {"1001", '9'}, {"1010", 'A'}, {"1011", 'B'}, {"1100", 'C'}, {"1101", 'D'}, {"1110", 'E'}, {"1111", 'F'}};

  unordered_map<char, string> bin_dict = {
      {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"}, {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"}, {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"}, {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}};

  enum Coordinate
  {
    x,
    y
  };

#pragma region "Constructors"
  Utils();

#pragma endregion

#pragma region "Functions"
  // Return a normalized vector corresponding to the direction index passed
  Vector2 GetDirection(int directionIndex);
  int GetDirectionIndex(Vector2 direction);
  int GetDirectionIndex(int directionIndex);

  // return a number between 0 and 1, where 0 is coordinate 0 and 1 is the max width or height of the grid
  double NormalizeToGridDimention(Vector2 position, Coordinate coordinate);

  NodeId GetRandomNode(NodeType nodeType);

  NodeType GetNodeType(NodeId id);

  string bin_to_hex(string binary);
  string hex_to_bin(string hexadecimal);
  int bin_to_int(string binary);

  //Get a value between 0 and 1
  double GetRandomPercent();

  int GetRandomInt(int min = 0, int max = 100);

#pragma endregion

protected:
#pragma region "Protected Variables"
  // Arrays of NodeTypes used for subdividing the Enum. Used for random generation
  // Use the GetNodeType() function to get the correct vector:
  // 0 = Input, 1 = Neuron, 2 = Action, 3 = Free
  vector<NodeId> NodeTypeList[4] = {
      // Input Nodes
      {INPUT_HDC, INPUT_VDC, INPUT_FPD, INPUT_FPD, INPUT_RPD,
       INPUT_FRC, INPUT_FSD, INPUT_FSA, INPUT_CCD, INPUT_CCA,
       INPUT_CCC, INPUT_OSC, INPUT_RND, INPUT_BLK},

      // Neuron
      {NEURON},

      // Action Nodes
      {ACTION_TCW, ACTION_TCC, ACTION_MFW, ACTION_MBW, ACTION_CXM,
       ACTION_CYM, ACTION_PRM, ACTION_TGL, ACTION_SOC},

      // Free
      {FREE, LAST}};

  double lower_bound = 0;
  double upper_bound = 1;
  default_random_engine re;

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
};
#endif
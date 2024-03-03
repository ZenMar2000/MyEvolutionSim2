#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <unordered_map>
#include <bits/stdc++.h>

#include "Vector2/Vector2.hpp"

/*
Directions indexes
    0	1	2
    7		3
    6	5	4
*/

enum NodeType
{
  // Input from 0 to 63
  INPUT_HDC = 0, // Horizontal distance from left border
  INPUT_VDC = 1, // Vertical distance from top border
  INPUT_FPD = 2, // Forward population density
  INPUT_FRC = 3, // Food reserve counter
  INPUT_FSD = 4, // Closest food source distance
  INPUT_FSA = 5, // Closest food source angle, relative to forward direction
  INPUT_CCD = 6, // Closest cell distance
  INPUT_CCA = 7, // Closest cell angle, relative to forward direction
  INPUT_CCC = 8, // Closest cell compatibility (how similar their genome is)

  // Neurons from 64 to 127
  NEURON = 64, // Neuron

  // Actions from 128 to 191
  ACTION_TCW = 128, // Turn clockwise
  ACTION_TCC = 129, // Turn counterclockwise
  ACTION_ADV = 130, // Advance forth
  ACTION_PRM = 131  // Release pheromones

  // Free range from 192 to 255
};

class Utils
{
public:
  // Variables
  static const int DirectionsAmount = 8;
  static const int CellPixelsDimension = 5;
  static const int WindowWidth = 800;
  static const int WindowHeight = 600;

  Vector2 *Directions;

  unordered_map<std::string, char> hex_dict = {
      {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'}, 
      {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'}, 
      {"1000", '8'}, {"1001", '9'}, {"1010", 'A'}, {"1011", 'B'}, 
      {"1100", 'C'}, {"1101", 'D'}, {"1110", 'E'}, {"1111", 'F'}};

  unordered_map<char, string> bin_dict = {
      {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
      {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
      {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
      {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}};

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
  Vector2 GetDirection(int DirectionIndex);

  // return a number between 0 and 1, where 0 is coordinate 0 and 1 is the max width or height of the grid
  double NormalizeToGridimention(Vector2 position, Coordinate coordinate);

  NodeType GetRandom_InputNode();
  NodeType GetRandom_NeuronNode();
  NodeType GetRandom_ActionNode();

  string bin_to_hex(string binary);
  string hex_to_bin(string hexadecimal);

#pragma endregion

private:
  // Arrays of NodeTypes used for subdividing the Enum. Used for random generation
  NodeType *InputNodes;
  NodeType *NeuronNodes;
  NodeType *ActionNodes;

  void InstantiateNodesArrays();
};

#endif

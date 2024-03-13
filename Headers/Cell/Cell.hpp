#ifndef CELL_H
#define CELL_H

#include <vector>

#include "../Utils.hpp"
#include "../Nodes/Node.hpp"

using namespace std;

class Node;

class Cell
{
public:
    Vector2 cellPosition;

#pragma region "Constructors"
    Cell();
    Cell(int genomeLength, Vector2 spawnPosition, Utils *util, int startingFood = 10);

#pragma endregion

#pragma region "Public Functions"
    void GenerateGenome();
    bool IsAlive();
    Color GetCellColor();

    void PerformAction();

#pragma endregion

protected:
#pragma region "Protected Variables"
    // Max length of the genome array
    int genomeLength;

    // Node *Genome;

    // Array containing all nodes. Positions inside the array corresponds to the first 2 binary values of enum NodeType
    vector<Node> GenomeArray[3];

    // Food counter. When reaching 0, the cell dies.
    int foodReserve;

    // If the cell is alive
    bool isAlive = true;

    // Which direction the cell is facing
    Vector2 direction;

    // Pointer to the Util instance
    Utils *util;

    Color cellColor;

#pragma endregion

#pragma region "Protected Functions"

#pragma endregion
};

#endif
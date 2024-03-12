#ifndef CELL_H
#define CELL_H

#include "../Utils.hpp"
#include "../Nodes/Node.hpp"
class Node;

class Cell
{
public:
    Vector2 cellPosition;

#pragma region "Constructors"
    Cell();
    Cell(int genomeLength, Vector2 spawnPosition, Utils *util);

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

    // Array containing all nodes
    Node *Genome;

    // Food counter. When reaching 0, the cell dies.
    int foodReserve;

    //If the cell is alive
    bool isAlive = true;

    // Which direction the cell is facing
    Vector2 direction;

    // Pointer to the Util instance
    Utils *util;

    Color cellColor;

#pragma endregion
};

#endif
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
#pragma region "Public Variables"
    Vector2 cellPosition;

    // if this cell should move in the next step. Used for passing data to Grid.cpp
    bool WantToMove = false;
#pragma endregion

#pragma region "Constructors"
    Cell();
    Cell(int genomeLength, Vector2 spawnPosition, Utils *util, int direction, int startingFood = 10);

#pragma endregion

#pragma region "Public Functions"
    // Generate a random sequence of nodes and link between them.
    // Use LoadGenome() to use a specific Genome sequence.
    void GenerateCellGenome();

    // Load the full cell genome from hex values.
    // Use GenerateGenome() to get a random sequence.
    void LoadCellGenome(vector<string> cellGenome);

    // Load a single Genome into the cell from hex values.
    void LoadSingleCellGenome(string singleCellGenome);

    // Reset the cell genome, removing all nodes and links between them.
    void ClearCellGenome();

    vector<string> GetCellGenome();

    bool IsAlive();
    Color GetCellColor();

    // Perform 1 step, signal to all nodes to elaborate data.
    // Nodes are elaborated in order: Input nodes, Neuron nodes, Action nodes
    void PerformAction();

    // Move cell forward by 1 square. Called from Grid.cpp after collision checking.
    void MoveTo(Vector2 newPos);

    // Turn cell facing direction clockwise or counterclockwise. 1 = -45deg, -1 = +45deg.
    // Positive values are clockwise rotations, while negative values are counter clockwise.
    // Usually rotated by 1 or -1
    void Turn(int rotation);

    int GetDirectionIndex();

    int GetFoodReserve();

#pragma endregion

protected:
#pragma region "Protected Variables"
    // Max length of the genome array
    int genomeLength;
    int currentGenomeLength = 0;

    // Node *Genome;

    // Array containing all nodes. 
    //Positions inside the array corresponds to the first 2 binary values of enum NodeType
    vector<Node> GenomeArray[3];

    // Food counter. When reaching 0, the cell dies.
    int foodReserve;

    // If the cell is alive
    bool isAlive = true;

    // Which direction the cell is facing
    int directionIndex;


    // Pointer to the Util instance
    Utils *util;

    Color cellColor;

#pragma endregion

#pragma region "Protected Functions"
    // Use the generated or loaded genome to create and physically link nodes.
    void LinkAllNodes(vector<string> cellGenome);

#pragma endregion
};

#endif
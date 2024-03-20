#ifndef CELL_H
#define CELL_H

#include <vector>

#include "../Utils.hpp"
#include "../Nodes/Node.hpp"
#include "../Grid/Grid.hpp"

using namespace std;
class Node;
class Grid;

class Cell
{
public:
#pragma region "Public Variables"
    Vector2 cellPosition = Vector2(-1, -1);
    Grid *grid;
    vector<Node> GenomeArray[3];
    bool ignoreCell = false;

#pragma endregion

#pragma region "Constructors"
    Cell();
    Cell(int genomeLength, Vector2 spawnPosition, Utils *util, DirectionsIndex direction, Grid *grid, int startingFood = 10);

#pragma endregion

#pragma region "Public Functions"
    // Generate a random sequence of nodes and link between them.
    // Use LoadGenome() to use a specific Genome sequence.
    void GenerateCellGenome();

    // Load the full cell genome from hex values.
    // Use GenerateGenome() to get a random sequence.
    void LoadCellGenome(vector<string> cellGenome);

    // Reset the cell genome, removing all nodes and links between them.
    void ClearCellGenome();

    vector<string> GetCellGenome();

    void LoadSingleCellGenome(string singleCellGenome);
    
    bool IsAlive();
    Color GetCellColor();

    // Signal to all nodes to elaborate data.
    // Nodes are elaborated in order: Input nodes, Neuron nodes, Action nodes
    void PerformAction();

    // Move forward or backward, relative to the facing direction of the cell
    void DirectionalMove(bool isBackward = false);

    // Move dictated by cartesian logic and not by direction. Move Up, down, left or right.
    void CartesianMove(DirectionsIndex directionIndex);

    // Turn cell facing direction clockwise or counterclockwise. 1 = -45deg, -1 = +45deg.
    // Positive values are clockwise rotations, while negative values are counter clockwise.
    // Usually rotated by 1 or -1
    void Turn(int rotation);

    DirectionsIndex GetDirectionIndex(int offset = 0);

    int GetFoodReserve();
    int GetGenomeLength();

#pragma endregion

protected:
#pragma region "Protected Variables"
    // Max length of the genome array
    int genomeLength = 0;
    int currentGenomeLength = 0;

    // Node *Genome;

    // Array containing all nodes.
    // Positions inside the array corresponds to the first 2 binary values of enum NodeType

    // Food counter. When reaching 0, the cell dies.
    int foodReserve = 0;

    // If the cell is alive
    bool isAlive = true;

    // Which direction the cell is facing
    DirectionsIndex directionIndex = DIRECTION_NULL;

    // Pointer to the Util instance
    Utils *util = NULL;

    Color cellColor = Color(255, 0, 0);

#pragma endregion

#pragma region "Protected Functions"
    // Use the generated or loaded genome to create and physically link nodes.
    // void LinkAllNodes(vector<string> cellGenome);
    
    //Check if a node is already existing in the GenomeArray. Return -1 if nothing is found
    int CheckIfNodeExists(NodeId nodeId, NodeType nodeType);


    void ReduceFood();

    //Pass all nodes in the GenomeArray specified by the type and activate each one, performing all relative instructions 
    void ActivateNodes(NodeType type);
#pragma endregion
};

#endif
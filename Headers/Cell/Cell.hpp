#ifndef CELL_H
#define CELL_H

#include "../Nodes/Node.hpp"
#include "../Utils.hpp"

class Cell{
    public:
    Cell();
    Cell(Vector2 spawnPosition);
    
    Vector2 cellPosition;
};

#endif
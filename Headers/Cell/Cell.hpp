#ifndef CELL_H
#define CELL_H
#include "../Nodes/Node.hpp"

class Cell{
    protected:
   

    public:
    Cell(Vector2 pos){
        position = pos;
    };
    
     Vector2 position;
};

#endif
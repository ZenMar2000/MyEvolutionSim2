#ifndef HDC_H
#define HDC_H

#include "../Node.hpp"

class InputNode_HDC: public Node{
    public:
    InputNode_HDC() : Node() {
    }

    InputNode_HDC(Cell* parentCell) : Node (parentCell){
        this-> nodeId = nodeId;
        this-> nodeName = nodeName;
        this-> parentCell = parentCell;
    }

    void Activate() override{

    }
    
    int GenerateNodeGenome() override {
        
    }
};

#endif
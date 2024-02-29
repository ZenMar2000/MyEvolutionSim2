#include <iostream>
#include "../../Headers/Nodes/Node.hpp"

int Node::GetNodeId(){
    return nodeId;
}

 char* Node::GetNodeName(){
    return nodeName;
}


void Node::AddLinkedNode(Node* node){
    linkedNodes.push_back(node);
}

void Node::RemoveLinkedNode(int index){
    int len = linkedNodes.size();

    if(len < 0){
        cout << "'linkedNodes' list is empty" << endl;
        return;
    }
    else if(index < len -1){
        cout << "The given index is greater than linkedNodes list size" << endl;
        return;
    }

    list<Node*>::iterator it = linkedNodes.begin();
    advance(it, index);
    linkedNodes.erase(it);
}

void Node::Activate(){  
    throw std::logic_error("Function 'Activate()' in Node.cpp is not implemented. Please use derived classes instead.");
}

int Node::GenerateNodeGenome(){  
    throw std::logic_error("Function 'GenerateNodeGenome()' in Node.cpp is not implemented. Please use derived classes instead.");
}

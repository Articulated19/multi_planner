//
//  Node.cpp
//  path_finder
//
//  Created by Aleksandar Babunovic on 2018-03-03.
//  Copyright © 2018 Aleksandar Babunovic. All rights reserved.
//

#include "Node.h"



Node::Node(Point2D** neighbours, Point2D* pos){
    this->neighbours = neighbours;
    this->pos = pos;
}

Node::~Node(){
    delete neighbours;
}

Point2D** Node::getNeighbours(){
    return neighbours;
}

Point2D* Node::getPosition(){
    return pos;
}

bool Node::equals(Node* target){
    return this->pos->equals(target->getPosition());
}



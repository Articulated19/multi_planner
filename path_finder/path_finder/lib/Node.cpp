//
//  Node.cpp
//  path_finder
//
//  Created by Aleksandar Babunovic on 2018-03-03.
//  Copyright © 2018 Aleksandar Babunovic. All rights reserved.
//

#include "Node.h"



Node::Node(Node** neighbours, Point2D* pos){
    this->neighbours = neighbours;
    this->pos = pos;
}

Node::~Node(){
    delete neighbours;
}

Node** Node::getNeighbours(){
    return neighbours;
}

Point2D* Node::getPosition(){
    return pos;
}



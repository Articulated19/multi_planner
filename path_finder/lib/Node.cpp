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
    taken = 0;
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

int Node::isTaken(int id){
    if(taken == 0 || taken == id) {
      return 0;
    } else {
      return 1;
    }
}

void Node::take(int id){
    if(taken != 0){

    } else{
      taken = id;
    }
}

void Node::setParent(Node* parent){
	this->parent = parent;
}

bool Node::equals(Node* target){
    return this->pos->equals(target->getPosition());
}

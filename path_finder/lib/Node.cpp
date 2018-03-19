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
    this->capacity = sizeof(neighbours);
    this->size = capacity;
}

Node::Node(int nrOfNeighbours, Point2D* pos){
  Point2D* neighbours[nrOfNeighbours];
  this->neighbours = neighbours;
  this->pos = pos;
  this->capacity = 0;
  this->size = nrOfNeighbours;
}

Node::~Node(){
    delete neighbours;
}

Point2D** Node::getNeighbours(){
    return neighbours;
}

Point2D* Node::getNeighbour(int index){
  return neighbours[index];
}

Point2D* Node::getPosition(){
    return pos;
}

Node* Node::addNeighbour(Point2D* neighbour){
  if(capacity != size){
    this->neighbours[capacity] = neighbour;
  }
  return this;
}

bool Node::equals(Node* target){
    return this->pos->equals(target->getPosition());
}

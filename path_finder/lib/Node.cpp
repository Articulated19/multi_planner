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
    takenAgents = new map<int,double>;
    taken = 0;
    treeSize = 1;
    isEndNode = false;
}

Node::~Node(){
    delete neighbours;
    delete takenAgents;
}

Point2D** Node::getNeighbours(){
    return neighbours;
}

Point2D* Node::getPosition(){
    return pos;
}

int Node::isTaken(int id){
    if(taken == 0/* || taken == id*/) {
      return 0;
    } else {
      return 1;
    }
}

int Node::getTaken(){
  return taken;
}

int Node::getTreeSize(){
  return treeSize;
}

void Node::take(int id){
    if(taken != 0){

    } else{
      //taken = id;
      take(id,0,0);
    }
}

void Node::take(int id, int nodeNr, double nodePerHour){
  takenAgents->insert(pair<int,double>(id,time(nullptr) + (nodeNr/nodePerHour)*60*60));
  taken = id;
}

void Node::remove(int id){
  takenAgents->erase(id);
}

void Node::setParent(Node* parent){
	this->parent = parent;
  treeSize += parent->treeSize;
}

Node* Node::popParent(){
  Node* ret;
  if(parent){
    ret = parent;
    parent = NULL;
    treeSize = 1;
  }
  return ret;
}

Node* Node::getParent(){
  return parent;
}

void Node::setCurrentFvalue(double value){
  currentFvalue = value;
}

double Node::getCurrentFvalue(){
  return currentFvalue;
}

map<int,double>* Node::getTakenAgents(){
  return takenAgents;
}

bool Node::hasParent(){
  return parent;
}

bool Node::is_end_node(){
  return isEndNode;
}

void Node::enableEndNode(){
  isEndNode = true;
}

void Node::disableEndNode(){
  isEndNode = false;
}

bool Node::equals(Node* target){
    return this->pos->equals(target->getPosition());
}

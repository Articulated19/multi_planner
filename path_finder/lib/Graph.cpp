//
//  Graph.cpp
//  path_finder
//
//  Created by Aleksandar Babunovic on 2018-03-14.
//  Copyright © 2018 Aleksandar Babunovic. All rights reserved.
//

#include <stdio.h>
#include <cmath>
#include "Graph.h"

Graph::Graph(int nrNodes,int nrEdges){
    //this->edgeCosts = new std::tuple<Node*,Node*,int>*[nrEdges];
    this->edgeCosts = new std::map<Node*, std::tuple<Node*,int>**>();
    this->nodes = new Node*[nrNodes];
    this->nrEdges = nrEdges;
    this->nrNodes = nrNodes;
}

Graph::~Graph(){
    delete edgeCosts;
    delete nodes;
}

int Graph::getCost(Node* from,Node* to){
    for(int i = 0; i < sizeof((*this->edgeCosts)[from]); i++){
        std::tuple<Node*, int>* elem = (*this->edgeCosts)[from][i];
        if(std::get<0>(*elem)->equals(to)){
            return std::get<1>(*elem);
        }
        delete elem;
    }
    return 0;
}

//TODO: This function should calculate for each neighbour the cost.
void Graph::addNode(Node* node, Node** neighbours){
    std::tuple<Node*,int>* arr[sizeof(neighbours)];
    for(int i = 0; i < sizeof(neighbours); i++){
      Node* dest = *(neighbours + i);
      int distance = calcDistance(node,dest);
      *arr[i] = std::make_tuple(dest,distance);
    }
    (*this->edgeCosts)[node] = arr;
}

/**
This just returns a straight line distance from those two nodes.
TODO: implement a counter that counts the amount of nodes between those two nodes.
**/
int Graph::calcDistance(Node* from, Node* to){
  Point2D* fromPoint = from->getPosition();
  Point2D* toPoint = to->getPosition();
  return sqrt(pow(fromPoint->getX() - toPoint->getX(),2) +
  pow(fromPoint->getY() - toPoint->getY(),2));
}

int Graph::getNrEdges(){
  return this->nrEdges;
}

int Graph::getNrNodes(){
  return this->nrNodes;
}

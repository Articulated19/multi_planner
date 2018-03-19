//
//  Graph.cpp
//  path_finder
//
//  Created by Aleksandar Babunovic on 2018-03-14.
//  Copyright © 2018 Aleksandar Babunovic. All rights reserved.
//

#include <stdio.h>
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

void Graph::addNode(Node* node,std::tuple<Node*, int>** neighbours){
    (*this->edgeCosts)[node] = neighbours;
}

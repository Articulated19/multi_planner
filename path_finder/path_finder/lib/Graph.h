//
//  Graph.h
//  path_finder
//
//  Created by Aleksandar Babunovic on 2018-03-14.
//  Copyright © 2018 Aleksandar Babunovic. All rights reserved.
//

#ifndef Graph_h
#define Graph_h
#include <tuple>
#include <map>
#include "Point2D.h"
#include "Node.h"

class Graph{
private:
    std::map<Node*,std::tuple<Node*,int>**>* edgeCosts;
    Node** nodes;
    int nrEdges;
    int nrNodes;
    
public:
    Graph(int,int);
    ~Graph();
    int getCost(Node*,Node*);
    void addNode(Node*,std::tuple<Node*, int>**);
};

#endif /* Graph_h */

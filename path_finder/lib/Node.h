//
//  Node.h
//  path_finder
//
//  Created by Aleksandar Babunovic on 2018-03-05.
//  Copyright © 2018 Aleksandar Babunovic. All rights reserved.
//

#ifndef Node_h
#define Node_h

#include "Point2D.h"
#include <stdlib.h>
#include <vector>
#include <map>

using namespace std;

class Node {
private:
    Point2D** neighbours;
    map<int,int>* takenAgents;
    Point2D* pos;
    Node* parent;
    int treeSize;
    double currentFvalue;
    int taken;


public:
    Node(Point2D**, Point2D*);
    ~Node();
    Point2D** getNeighbours();
    Point2D* getPosition();

    int isTaken(int);
    int getTreeSize();
    void take(int);
    void take(int,int,double);
    void remove(int);
    void setCurrentFvalue(double);
    double getCurrentFvalue();

    bool equals(Node*);
    void setParent(Node*);
    Node* getParent();
};

#endif /* Node_h */

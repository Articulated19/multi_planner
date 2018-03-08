//
//  Path.h
//  path_finder
//
//  Created by Aleksandar Babunovic on 2018-03-05.
//  Copyright © 2018 Aleksandar Babunovic. All rights reserved.
//

#ifndef Path_h
#define Path_h
#include "Node.h"

class Path{
private:
    /*
     The path starting node at 0
     */
    Path(int);
    Node** path;
    double cost;
    int length;
    
public:
    Path();
    ~Path();
    int path_length();
    double getCost();
    void addNode(Node*);
    Path addNodeAndClone(Node*);
    bool equals(Path*);
};

#endif /* Path_h */

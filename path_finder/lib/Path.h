//
//  Path.h
//  path_finder
//
//  Created by Aleksandar Babunovic on 2018-03-05.
//  Copyright © 2018 Aleksandar Babunovic. All rights reserved.
//

#ifndef Path_h
#define Path_h
#include <stdlib.h>
#include <vector>
#include "Node.h"

using namespace std;

class Path{
private:
    /*
     The path starting node at 0
     */
    Path(int);
    vector<Node*>* path;
    int length;
    
public:
    Path(vector<Node*>);
    Path();
    ~Path();
    int path_length();
    Node* fst();
    void addNode(Node*);
    Path addNodeAndClone(Node*);
    bool equals(Path*);
};

#endif /* Path_h */

//
//  StateMatrix.h
//  path_finder
//
//  Created by Aleksandar Babunovic on 2018-03-08.
//  Copyright © 2018 Aleksandar Babunovic. All rights reserved.
//

#ifndef StateMatrix_h
#define StateMatrix_h
#include "Node.h"
#include <vector>

class StateMatrix{
private:
    Node*** states;
    //std::vector<Node**>* states;
    int rowCapacity;
    int columnCapacity;
    int rowSize;
    int columnSize;
    
public:
    StateMatrix();
    StateMatrix(int,int);
    ~StateMatrix();
    bool sendRequest(Node*,int,int);
    void deleteState(int,int);
    void deleteAll(Node*);
};


#endif /* StateMatrix_h */

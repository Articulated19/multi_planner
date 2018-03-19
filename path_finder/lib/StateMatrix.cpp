//
//  StateMatrix.cpp
//  path_finder
//
//  Created by Aleksandar Babunovic on 2018-03-08.
//  Copyright © 2018 Aleksandar Babunovic. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "StateMatrix.h"

/*
 TODO: fix the State matrix. Can't have multi array right now.
 */
StateMatrix::StateMatrix(int rowSize, int columnSize){
    //states->insert(0, new Node*[columnSize]);
    //*states = (Node**) malloc(rowSize);
    //states = new Node**[rowSize*columnSize];
    //for(int i = 0; i < rowSize; ++i)
      //  states[i] = new Node*[columnSize];
    //*states = new Node[columnSize];
    //**states = (Node*) malloc(columnSize);
}

StateMatrix::StateMatrix(){
    StateMatrix(100,100);
}

StateMatrix::~StateMatrix(){
    //delete states;
}

bool StateMatrix::sendRequest(Node* node,int row,int col){
    if(states[row][col] == NULL){
        states[row][col] = node;
        return true;
    }
    return false;
}

void StateMatrix::deleteState(int row, int col){
    states[row][col] = NULL;
}

void StateMatrix::deleteAll(Node* node){
    for (int i = 0; i < rowCapacity; i++){
        for (int o = 0; o < columnCapacity; o++){
            if(states[i][o] == node){
                deleteState(i,o);
            }
        }
    }
}

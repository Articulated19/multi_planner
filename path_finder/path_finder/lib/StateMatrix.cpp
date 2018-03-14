//
//  StateMatrix.cpp
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
    int rowSize;
    int columnSize;
    
public:
    StateMatrix(){
        StateMatrix(100,100);
    }
    StateMatrix(int rowSize,int columnSize){
        states = new Node**[rowSize*columnSize];
        for(int i = 0; i < rowSize; ++i)
            states[i] = new Node*[columnSize];
        this->rowSize = rowSize;
        this->columnSize = columnSize;
    }
    ~StateMatrix(){
        
    }
    bool sendRequest(Node* node,int row,int col){
        if(states[row][col] == NULL){
            states[row][col] = node;
            return true;
        }
        return false;
    }
    void deleteState(int row,int col){
        states[row][col] = NULL;
    }
    void deleteAll(Node* node){
        for (int i = 0; i < rowSize; i++){
            for (int o = 0; o < columnSize; o++){
                if(states[i][o] == node){
                    deleteState(i,o);
                }
            }
        }
    }
};


#endif /* StateMatrix_h */

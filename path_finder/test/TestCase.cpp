//
//  TestCase.cpp
//  path_finder
//
//  Created by Aleksandar Babunovic on 2018-03-08.
//  Copyright © 2018 Aleksandar Babunovic. All rights reserved.
//

#include <stdio.h>
#include "TestCase.h"

TestCase::TestCase(Path* expected, Node* startNode, Node* endNode, StateMatrix* matrix, Pathfinder* action){
    this->expected = expected;
    this->startNode = startNode;
    this->endNode = endNode;
    this->matrix = matrix;
    this->action = action;
}

TestCase::~TestCase(){
    delete expected;
    delete startNode;
    delete endNode;
    delete result;
}

bool TestCase::runTest(){
    //result = action->planPath(startNode, endNode, matrix);
    if(expected->equals(result)){
        return true;
    }
    return false;
}

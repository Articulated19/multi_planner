//
//  TestCase.h
//  path_finder
//
//  Created by Aleksandar Babunovic on 2018-03-08.
//  Copyright © 2018 Aleksandar Babunovic. All rights reserved.
//

#ifndef TestCase_h
#define TestCase_h
#include "Pathfinder.h"
#include "Node.h"
#include "StateMatrix.h"

class TestCase{
private:
    Pathfinder* action;
    StateMatrix* matrix;
    Node* startNode;
    Node* endNode;
    Path* result;
    Path* expected;
public:
    TestCase(Path*, Node*, Node*, StateMatrix*, Pathfinder*);
    ~TestCase();
    bool runTest();
};

#endif /* TestCase_h */

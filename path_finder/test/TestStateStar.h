//
//  TestStateStar.h
//  path_finder
//
//  Created by Aleksandar Babunovic on 2018-03-05.
//  Copyright © 2018 Aleksandar Babunovic. All rights reserved.
//

#ifndef TestStateStar_h
#define TestStateStar_h

#include "TestCase.h"
//#include "lib/StateMatrix.h"
#include <stdlib.h>
#include "../lib/Graph.h"
#include <vector>

class TestStateStar{
private:
    TestCase** cases;
    Graph* testGraph;
    void initTests();
    void addNode(Node**,int,Point2D**,Point2D*);

public:
    TestStateStar();
    ~TestStateStar();
    void createGraph(Graph*);
    void runAllTests();
    void runTest(int);
};


#endif /* TestStateStar_h */

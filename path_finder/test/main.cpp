//
//  main.cpp
//  path_finder
//
//  Created by Aleksandar Babunovic on 2018-03-03.
//  Copyright © 2018 Aleksandar Babunovic. All rights reserved.
//
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>


using namespace std;


#include "lib/Node.h"
#include "lib/Point2D.h"
#include "TestStateStar.h"
#include "lib/StateMatrix.cpp"
#include "lib/Graph.h"


void toCharArray(string, char*);

int main(int argc, const char * argv[]) {
    Point2D* pos = new Point2D(1,4);
    Node* n = new Node(NULL, pos);
    TestStateStar* test = new TestStateStar();
    StateMatrix* state = new StateMatrix(30,40);
    Graph* g = new Graph(10,3);
    std::cout << n->getPosition()->getY();
    return 0;
}

void toCharArray(string str, char* result){
    strcpy(result, str.c_str());
}

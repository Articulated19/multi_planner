//
//  TestStateStar.cpp
//  path_finder
//
//  Created by Aleksandar Babunovic on 2018-03-05.
//  Copyright © 2018 Aleksandar Babunovic. All rights reserved.
//

#include "TestStateStar.h"

TestStateStar::TestStateStar(){
    cases = new TestCase*[20];

    //*cases = (TestCase*) malloc(sizeof(TestCase)*20);
    this->testGraph = new Graph(22,32);
    createGraph(this->testGraph);
    initTests();
}

TestStateStar::~TestStateStar(){

}

void TestStateStar::createGraph(Graph* g){
  //create all nodes in the Graph
  Node* nodes[]{
    (new Node(1,new Point2D(1,2)))->addNeighbour(new Point2D(4,1)),
    (new Node(1,new Point2D(1,6)))->addNeighbour(new Point2D(2,4)),
    (new Node(1,new Point2D(1,10)))->addNeighbour(new Point2D(2,8)),
    (((new Node(3,new Point2D(2,4)))->addNeighbour(new Point2D(1,2)))->addNeighbour(new Point2D(4,3)))->addNeighbour(new Point2D(3,6)),
    (((new Node(3,new Point2D(2,8)))->addNeighbour(new Point2D(1,6)))->addNeighbour(new Point2D(4,7)))->addNeighbour(new Point2D(3,10)),
    (new Node(1,new Point2D(3,2)))->addNeighbour(new Point2D(2,4)),
    (new Node(1,new Point2D(3,6)))->addNeighbour(new Point2D(2,8)),
    (new Node(1,new Point2D(3,10)))->addNeighbour(new Point2D(4,11)),
    ((new Node(2,new Point2D(4,1)))->addNeighbour(new Point2D(3,2)))->addNeighbour(new Point2D(7,2)),
    (new Node(1,new Point2D(4,3)))->addNeighbour(new Point2D(6,4)),
    (new Node(1,new Point2D(4,5)))->addNeighbour(new Point2D(2,4)),
    (new Node(1,new Point2D(4,7)))->addNeighbour(new Point2D(6,8)),
    (new Node(1,new Point2D(4,9)))->addNeighbour(new Point2D(2,8)),
    ((new Node(2,new Point2D(4,11)))->addNeighbour(new Point2D(1,10)))->addNeighbour(new Point2D(5,10)),
    (new Node(1,new Point2D(5,2)))->addNeighbour(new Point2D(4,1)),
    (new Node(1,new Point2D(5,6)))->addNeighbour(new Point2D(6,4)),
    (new Node(1,new Point2D(5,10)))->addNeighbour(new Point2D(6,8)),
    (((new Node(3,new Point2D(6,4)))->addNeighbour(new Point2D(5,2)))->addNeighbour(new Point2D(4,5)))->addNeighbour(new Point2D(7,6)),
    (((new Node(3,new Point2D(6,8)))->addNeighbour(new Point2D(5,6)))->addNeighbour(new Point2D(4,9)))->addNeighbour(new Point2D(7,10)),
    (new Node(1,new Point2D(7,2)))->addNeighbour(new Point2D(6,4)),
    (new Node(1,new Point2D(7,6)))->addNeighbour(new Point2D(6,8)),
    (new Node(1,new Point2D(7,10)))->addNeighbour(new Point2D(4,11))
  };

  //Now add the nodes to the Graph


}

void TestStateStar::addNode(Node** arr, int index, Point2D** neighbours, Point2D* pos){
}

void TestStateStar::runAllTests(){

}

void TestStateStar::runTest(int){

}

void TestStateStar::initTests(){
    *(cases) = new TestCase(NULL,NULL,NULL,NULL,NULL,NULL);
    //*(cases+1) = new TestCase(NULL,NULL,NULL,NULL,NULL);
}

//
//  TestStateStar.cpp
//  path_finder
//
//  Created by Aleksandar Babunovic on 2018-03-05.
//  Copyright © 2018 Aleksandar Babunovic. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>


using namespace std;

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
  //Node** nodes = createNodes();
  //initNeighbours(nodes);
  /*Node* nodes[]{
    //new Node(1,new Point2D(1,2))





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
  };*/
  //Point2D* p = new Point2D(2,4);
  //nodes[0]->addNeighbour(p);
  //std::cout << (*nodes)->getNeighbour(0)->toString() << '\n';
  //Add them in a map


  Node** nodes = (Node**) std::malloc(22);
    //new Node(1,new Point2D(1,2))
    *nodes = new Node(1,*new Point2D(1,2));
    /*(*(nodes+1)) = new Node(1,new &Point2D(1,6));
    (*(nodes+2)) = new Node(1,new Point2D(1,10));
    (*(nodes+3)) = new Node(3,new Point2D(2,4));
    (*(nodes+4)) = new Node(3,new Point2D(2,8));
    (*(nodes+5)) = new Node(1,new Point2D(3,2));
    (*(nodes+6)) = new Node(1,new Point2D(3,6));
    (*(nodes+7)) = new Node(1,new Point2D(3,10));
    (*(nodes+8)) = new Node(2,new Point2D(4,1));
    (*(nodes+9)) = new Node(1,new Point2D(4,3));
    (*(nodes+10)) = new Node(1,new Point2D(4,5));
    (*(nodes+11)) = new Node(1,new Point2D(4,7));
    (*(nodes+12)) = new Node(1,new Point2D(4,9));
    (*(nodes+13)) = new Node(2,new Point2D(4,11));
    (*(nodes+14)) = new Node(1,new Point2D(5,2));
    (*(nodes+15)) = new Node(1,new Point2D(5,6));
    (*(nodes+16)) = new Node(1,new Point2D(5,10));
    (*(nodes+17)) = new Node(3,new Point2D(6,4));
    (*(nodes+18)) = new Node(3,new Point2D(6,8));
    (*(nodes+19)) = new Node(1,new Point2D(7,2));
    (*(nodes+20)) = new Node(1,new Point2D(7,6));
    (*(nodes+21)) = new Node(1,new Point2D(7,10));
    std::cout << (*nodes)->getPosition()->toString() << '\n';

    (*(nodes + 0))->addNeighbour(new Point2D(4,1));
    (*(nodes + 1))->addNeighbour(new Point2D(2,4));
    (*(nodes + 2))->addNeighbour(new Point2D(2,8));
    (*(nodes + 3))->addNeighbour(new Point2D(1,2));
    (*(nodes + 3))->addNeighbour(new Point2D(4,3));
    (*(nodes + 3))->addNeighbour(new Point2D(3,6));
    (*(nodes + 4))->addNeighbour(new Point2D(1,6));
    (*(nodes + 4))->addNeighbour(new Point2D(4,7));
    (*(nodes + 4))->addNeighbour(new Point2D(3,10));
    (*(nodes + 5))->addNeighbour(new Point2D(2,4));
    (*(nodes + 6))->addNeighbour(new Point2D(2,8));
    (*(nodes + 7))->addNeighbour(new Point2D(4,11));
    (*(nodes + 8))->addNeighbour(new Point2D(3,2));
    (*(nodes + 8))->addNeighbour(new Point2D(7,2));
    (*(nodes + 9))->addNeighbour(new Point2D(6,4));
    (*(nodes + 10))->addNeighbour(new Point2D(2,4));
    (*(nodes + 11))->addNeighbour(new Point2D(6,8));
    (*(nodes + 12))->addNeighbour(new Point2D(2,8));
    (*(nodes + 13))->addNeighbour(new Point2D(1,10));
    (*(nodes + 13))->addNeighbour(new Point2D(5,10));
    (*(nodes + 14))->addNeighbour(new Point2D(4,1));
    (*(nodes + 15))->addNeighbour(new Point2D(6,4));
    (*(nodes + 16))->addNeighbour(new Point2D(6,8));
    (*(nodes + 17))->addNeighbour(new Point2D(5,2));
    (*(nodes + 17))->addNeighbour(new Point2D(7,6));
    (*(nodes + 18))->addNeighbour(new Point2D(5,6));
    (*(nodes + 18))->addNeighbour(new Point2D(4,9));
    (*(nodes + 18))->addNeighbour(new Point2D(7,10));
    (*(nodes + 19))->addNeighbour(new Point2D(6,4));
    (*(nodes + 20))->addNeighbour(new Point2D(6,8));
    (*(nodes + 21))->addNeighbour(new Point2D(4,11));

*/
  //std::cout<< (*(nodes+3))->getNeighbour(0)->toString();

  std::map<string,Node*>* list = new std::map<string, Node*>();
  //list->insert(std::pair<string,Node*>(nodes[0]->getPosition()->toString(),nodes[0]));
  //Node* n = (*list)["(1,2)"];
  /*
  for(int i = 0; i < sizeof(nodes)/sizeof(*nodes); i++){
    (*list)[nodes[i]->getPosition()->toString()] = nodes[i];
  }
  for(int i = 0; i < sizeof(nodes)/sizeof(*nodes); i++){
    Point2D** neighbours = (*(nodes + i))->getNeighbours();
    Node** nodeNeighbours = (Node**) std::malloc(sizeof(Node)*((*(nodes + i))->getNrNeighbours()));
    for(int j = 0; j < (*(nodes + i))->getNrNeighbours(); j++){
      std::cout << "Yeeees" + (*(nodes + i))->getNeighbour(j)->toString() << '\n';
    }
  }*/

  delete list;
}

/*Node** TestStateStar::createNodes(){
  Node** nodes = (Node**) std::malloc(sizeof(Node)*22);
    //new Node(1,new Point2D(1,2))
    (*(nodes)) = new Node(1,new Point2D(1,2));
    (*(nodes+1)) = new Node(1,new Point2D(1,6));
    (*(nodes+2)) = new Node(1,new Point2D(1,10));
    (*(nodes+3)) = new Node(3,new Point2D(2,4));
    (*(nodes+4)) = new Node(3,new Point2D(2,8));
    (*(nodes+5)) = new Node(1,new Point2D(3,2));
    (*(nodes+6)) = new Node(1,new Point2D(3,6));
    (*(nodes+7)) = new Node(1,new Point2D(3,10));
    (*(nodes+8)) = new Node(2,new Point2D(4,1));
    (*(nodes+9)) = new Node(1,new Point2D(4,3));
    (*(nodes+10)) = new Node(1,new Point2D(4,5));
    (*(nodes+11)) = new Node(1,new Point2D(4,7));
    (*(nodes+12)) = new Node(1,new Point2D(4,9));
    (*(nodes+13)) = new Node(2,new Point2D(4,11));
    (*(nodes+14)) = new Node(1,new Point2D(5,2));
    (*(nodes+15)) = new Node(1,new Point2D(5,6));
    (*(nodes+16)) = new Node(1,new Point2D(5,10));
    (*(nodes+17)) = new Node(3,new Point2D(6,4));
    (*(nodes+18)) = new Node(3,new Point2D(6,8));
    (*(nodes+19)) = new Node(1,new Point2D(7,2));
    (*(nodes+20)) = new Node(1,new Point2D(7,6));
    (*(nodes+21)) = new Node(1,new Point2D(7,10));
  return nodes;
}

void TestStateStar::initNeighbours(Node** nodes){
  (*(nodes + 0))->addNeighbour(new Point2D(4,1));
  (*(nodes + 1))->addNeighbour(new Point2D(2,4));
  (*(nodes + 2))->addNeighbour(new Point2D(2,8));
  (*(nodes + 3))->addNeighbour(new Point2D(1,2));
  (*(nodes + 3))->addNeighbour(new Point2D(4,3));
  (*(nodes + 3))->addNeighbour(new Point2D(3,6));
  (*(nodes + 4))->addNeighbour(new Point2D(1,6));
  (*(nodes + 4))->addNeighbour(new Point2D(4,7));
  (*(nodes + 4))->addNeighbour(new Point2D(3,10));
  (*(nodes + 5))->addNeighbour(new Point2D(2,4));
  (*(nodes + 6))->addNeighbour(new Point2D(2,8));
  (*(nodes + 7))->addNeighbour(new Point2D(4,11));
  (*(nodes + 8))->addNeighbour(new Point2D(3,2));
  (*(nodes + 8))->addNeighbour(new Point2D(7,2));
  (*(nodes + 9))->addNeighbour(new Point2D(6,4));
  (*(nodes + 10))->addNeighbour(new Point2D(2,4));
  (*(nodes + 11))->addNeighbour(new Point2D(6,8));
  (*(nodes + 12))->addNeighbour(new Point2D(2,8));
  (*(nodes + 13))->addNeighbour(new Point2D(1,10));
  (*(nodes + 13))->addNeighbour(new Point2D(5,10));
  (*(nodes + 14))->addNeighbour(new Point2D(4,1));
  (*(nodes + 15))->addNeighbour(new Point2D(6,4));
  (*(nodes + 16))->addNeighbour(new Point2D(6,8));
  (*(nodes + 17))->addNeighbour(new Point2D(5,2));
  (*(nodes + 17))->addNeighbour(new Point2D(7,6));
  (*(nodes + 18))->addNeighbour(new Point2D(5,6));
  (*(nodes + 18))->addNeighbour(new Point2D(4,9));
  (*(nodes + 18))->addNeighbour(new Point2D(7,10));
  (*(nodes + 19))->addNeighbour(new Point2D(6,4));
  (*(nodes + 20))->addNeighbour(new Point2D(6,8));
  (*(nodes + 21))->addNeighbour(new Point2D(4,11));
}*/

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

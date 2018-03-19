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
    initTests();
}

TestStateStar::~TestStateStar(){
    
}

void TestStateStar::runAllTests(){
    
}

void TestStateStar::runTest(int){
    
}

void TestStateStar::initTests(){
    *(cases) = new TestCase(NULL,NULL,NULL,NULL,NULL);
    *(cases+1) = new TestCase(NULL,NULL,NULL,NULL,NULL);
}

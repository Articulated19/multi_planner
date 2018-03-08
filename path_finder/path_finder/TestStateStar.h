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
#include "lib/StateMatrix.h"
#include <stdlib.h>

class TestStateStar{
private:
    TestCase** cases;
    void initTests();
    
public:
    TestStateStar();
    ~TestStateStar();
    void runAllTests();
    void runTest(int);
};


#endif /* TestStateStar_h */

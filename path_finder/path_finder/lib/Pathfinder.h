//
//  Pathfinder.h
//  path_finder
//
//  Created by Aleksandar Babunovic on 2018-03-08.
//  Copyright © 2018 Aleksandar Babunovic. All rights reserved.
//

#ifndef Pathfinder_h
#define Pathfinder_h

#include "Path.h"
#include "Node.h"
#include "StateMatrix.h"

class Pathfinder{
public:
    /*
     First arg: start node
     Second arg: end node
     */
    virtual Path* planPath(Node*, Node*, StateMatrix*);
};

#endif /* Pathfinder_h */

//
//  Path.cpp
//  path_finder
//
//  Created by Aleksandar Babunovic on 2018-03-05.
//  Copyright © 2018 Aleksandar Babunovic. All rights reserved.
//

#include <stdio.h>
#include "Path.h"

Path::Path(){

}

Path::~Path(){

}

Path::Path(int capacity){

}

int Path::path_length(){
    return length;
}

double Path::getCost(){
    return cost;
}

void Path::addNode(Node*){

}

Path Path::addNodeAndClone(Node*){

    return (*this);
}

bool Path::equals(Path* path){
    if(path->path_length() == this->path_length()){
        for(int i = 0; i < this->path_length(); i++){
            if(path->path[i] != this->path[i]){
                return false;
            }
        }
        return true;
    }
    return false;
}

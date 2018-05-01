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

Path::Path(){
    path = new vector<Node*>()
}

Path::Path(vector<Node*> v){
  (*path) = v;
}

int Path::path_length(){
    return length;
}


void Path::addNode(Node* n){
    path->push_back(n);
}

Path Path::addNodeAndClone(Node* n){
  vector<Node*> cloned(path);
  cloned.push_back(n);
  return new Path(cloned);
}

Node* Path::fst(){
  return path->peek();
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

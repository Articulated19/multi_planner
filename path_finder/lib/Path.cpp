//
//  Path.cpp
//  path_finder
//
//  Created by Aleksandar Babunovic on 2018-03-05.
//  Copyright © 2018 Aleksandar Babunovic. All rights reserved.
//

#include <stdio.h>
#include "Path.h"

Path::~Path(){
    
}

Path::Path(){
    path = new vector<Node*>();
}

Path::Path(vector<Node*>* v){
  path = v;
}

int Path::path_length(){
    return path->size();
}


void Path::addNode(Node* n){
    path->push_back(n);
}

//TODO This function sucks so fix it
Path* Path::addNodeAndClone(Node* n){
  Path* newPath = new Path(); //Here it might be a bugg
  for(unsigned int i = 0; i < path->size(); i++){
    newPath->addNode(path->at(i));
  }
  newPath->addNode(n);
  return newPath;
}

void Path::printPath(vector<Node*>* v){
  cout<<"[";
  for(unsigned int i = 0; i < v->size(); i++){
    cout<<"("<<v->at(i)->getPosition()->getX()<<","<<v->at(i)->getPosition()->getY()<<") , ";
  }
  cout<<"]"<<endl;
}

void Path::print(){
  printPath(path);
}

Node* Path::fst(){
  return path->back();
}

double Path::getCost(){
  return cost;
}


void Path::setCost(double cost){
  this->cost = cost;
}

vector<Node*>* Path::getPath(){
  return path;
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

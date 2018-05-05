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
    meeting_risk_lvl = 1;
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

Path* Path::addNodeAndClone(Node* n){
  Path* newPath = new Path();
  newPath->meeting_risk_lvl = meeting_risk_lvl;
  for(unsigned int i = 0; i < path->size(); i++){
    newPath->addNode(path->at(i));
  }
  newPath->addNode(n);
  newPath->cost = cost;
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

void Path::increaseCost(double cost){
  this->cost += cost;
}

vector<Node*>* Path::getPath(){
  return path;
}

void Path::increase_meeting_risk_lvl(){
  meeting_risk_lvl++;
}

int Path::get_meeting_risk_lvl(){
  return meeting_risk_lvl;
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

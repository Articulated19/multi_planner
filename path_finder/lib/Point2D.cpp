//
//  Point.cpp
//  path_finder
//
//  Created by Aleksandar Babunovic on 2018-03-03.
//  Copyright © 2018 Aleksandar Babunovic. All rights reserved.
//

#include "Point2D.h"

Point2D::Point2D(){
    Point2D(0,0);
}

Point2D::Point2D(double x,double y){
    this->x = x;
    this->y = y;
}
Point2D::~Point2D(){
    
}

double Point2D::getX(){
    return x;
}

double Point2D::getY(){
    return y;
}

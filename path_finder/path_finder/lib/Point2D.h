//
//  Point2D.h
//  path_finder
//
//  Created by Aleksandar Babunovic on 2018-03-05.
//  Copyright © 2018 Aleksandar Babunovic. All rights reserved.
//

#ifndef Point2D_h
#define Point2D_h

class Point2D{
private:
    double x;
    double y;
    
public:
    Point2D();
    Point2D(double,double);
    ~Point2D();
    double getX();
    double getY();
};


#endif /* Point2D_h */

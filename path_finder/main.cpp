#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include "multi_planner.cpp"
#include <thread>

using namespace std;

#include "lib/Node.h"
#include "lib/Point2D.h"
#include <SFML/Graphics.hpp>

#include "Gui.cpp"

int main(int argc, const char * argv[]) {

  multi_planner* planner = new multi_planner();

  planner->createGraph();

  Gui* gui = new Gui();
  std::thread windowthread(&gui->createWindow);

  planner->getGraphAsPath();

  while(1){
    cout<<"Start x >> ";
    double startx;
    cin >> startx;

    cout<<"Start y >> ";
    double starty;
    cin >> starty;

    cout<<"Goal x >> ";
    double goalx;
    cin >> goalx;

    cout<<"Goal y >> ";
    double goaly;
    cin >> goaly;

    Point2D* startpoint = new Point2D(startx, starty);
    Point2D* endpoint   = new Point2D(goalx, goaly);

    Point2D** path = planner->getPath(startpoint, endpoint);

    //Point2D** path = planner->getGraphAsPath();

    gui->drawPath(path);

    //windowthread.join();

  }

    return 0;
}

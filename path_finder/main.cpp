#include <stdio.h>
#include <iostream>
#include <fstream>
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
  std::cout<<"planner spawned"<<endl;

  planner->createGraph();

  if(argc >= 5){
    double startx = atof(argv[1]);
    double starty = atof(argv[2]);
    double goalx  = atof(argv[3]);
    double goaly  = atof(argv[4]);

    //cout<<"Recieved: "<< startx <<", "<<starty<<" : "<<goalx<<", "<<goaly<<endl;

    Point2D* startpoint = new Point2D(startx, starty);
    Point2D* goalpoint  = new Point2D(goalx, goaly);
      std::cout<<"This is what should be returned..."<<endl;
    Point2D** path = planner->getPath(startpoint, goalpoint);

    while(*path){
      std::cout<<path[0]->getX() << "," <<path[0]->getY()<<endl;
      std::cout.flush();
      path++;
    }


    ofstream file;
    file.open("path0.txt");
    while(*path){
      file<<path[0]->getX() << "," <<path[0]->getY()<<endl;
      path++;
    }
    file.close();
    cout<<"Path written to file."<<endl;
    
    return 0;
  }
  //Point2D** path = planner->getGraphAsPath();

  //gui->drawPath(path);

  if(argc == 1){
    Gui* gui = new Gui();
    std::thread windowthread(&gui->createWindow);

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

      //double startx = 770;
      //double starty = 2406;

      Point2D* startpoint = new Point2D(startx, starty);
      Point2D* endpoint   = new Point2D(goalx, goaly);
      gui->drawStartEnd(startpoint, endpoint);

      Point2D** path = planner->getPath(startpoint, endpoint);

      gui->drawPath(path);

      //windowthread.join();

    }
  }
  else {
    cout << "Wrong number of arguments" <<endl;
  }

    return 0;
};

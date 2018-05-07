#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "multi_planner.cpp"
#include <thread>
#include <unistd.h>
#include <time.h>

using namespace std;

#include "lib/Node.h"
#include "lib/Point2D.h"


int countCollisions(multi_planner*);
void printPath(Point2D**);

int beamSize = 10000;
double speed = 10;

int main(int argc, const char * argv[]) {

  multi_planner* planner = new multi_planner();
  //std::cout<<"planner spawned"<<endl;

  planner->createGraph();
  //planner->checkTakenNodes();

  if(argc >= 5){
    int id = stoi(argv[1]);
    double startx = atof(argv[2]);
    double starty = atof(argv[3]);
    double goalx  = atof(argv[4]);
    double goaly  = atof(argv[5]);

    //cout<<"Recieved: "<< startx <<", "<<starty<<" : "<<goalx<<", "<<goaly<<endl;

    Point2D* startpoint = new Point2D(startx, starty);
    Point2D* goalpoint  = new Point2D(goalx, goaly);
      //std::cout<<"Attempting to find path: (" << startx << "," <<starty<< ") to (" << goalx<< ", " <<goaly<<")"<<endl;
    Point2D** path = planner->getPath(id, startpoint, goalpoint);
    //Point2D** path = planner->beamSearch(id, speed, beamSize, startpoint, goalpoint);
    ofstream file;
    string filename = "data/path_" + to_string(id) + ".txt";
    file.open(filename);

    //std::cout<<"path start";
    while(*path){
      file<<path[0]->getX() << "," <<path[0]->getY()<<endl;
      std::cout<<path[0]->getX() << "," <<path[0]->getY()<<endl;
      std::cout.flush();
      path++;
    }
    file.close();
    //std::cout<<"path end";

/*
    ofstream file;
    file.open("path0.txt");
    while(*path){
      file<<path[0]->getX() << "," <<path[0]->getY()<<endl;
      path++;
    }
    file.close();
    cout<<"Path written to file."<<endl;
*/
    return 0;
  }
  //Point2D** path = planner->getGraphAsPath();

  //gui->drawPath(path);



  if(argc == 3){
    std::string cmd = argv[2];
    std::string input = argv[1];
    if(cmd.compare("-clear") == 0){
      string filename = "data/path_" + input + ".txt";
      if(remove(filename.c_str()) != 0){
        cout << "Error deleting file"<<endl;
      } else{
        cout << "Cleared "<<filename <<endl;
      }
    }
  }

  else {
    cout << "Wrong number of arguments" <<endl;
  }

    return 0;
};

int countCollisions(multi_planner* planner){
  int result = 0;
  Node** graph = planner->graph;
  while(*graph){
    if((*graph)->getTakenAgents()->size() > 1)
      result++;
    graph++;
  }
  return result;
}

void printPath(Point2D** path){
  while(*path){
    cout<<"("<<(*path)->getX()<<","<<(*path)->getY()<<")"<<endl;
    path++;
  }
}

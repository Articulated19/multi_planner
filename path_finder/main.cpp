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
#include <SFML/Graphics.hpp>

#include "Gui.cpp"

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

  if(argc == 1){

    Gui* gui = new Gui();
    std::thread windowthread(&gui->createWindow);
      while(1){
      cout<<"Id: >>";
      int id;
      cin >> id;

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

      Point2D** path = planner->getPath(id, startpoint, endpoint);
      Node* node = planner->getNode(startpoint);
      cout<<"taken before is: "<<node->isTaken(2)<<endl;
      //Point2D** path = planner->beamSearch(id, speed, beamSize, startpoint, endpoint);

      gui->drawPath(path);

      ofstream file;
      string filename = "data/path_" + to_string(id) + ".txt";
      file.open(filename);

      //std::cout<<"path start";
      while(*path){
        file<<path[0]->getX() << "," <<path[0]->getY()<<endl;
        path++;
      }
      file.close();

      //windowthread.join();
    }
  }

  if(argc == 2){
    std::string cmd = argv[1];
    if(cmd.compare("-clear") == 0){
      system("exec rm -r data/*");
      cout << "Cleared path data"<<endl;
    } else if(cmd.compare("-test") == 0){
      int maxTests = 7;
      Gui* gui = new Gui();
      std::thread windowthread(&gui->createWindow);
      int nrTests;
      char alg;
      cout<<"Number of tests(max "<<maxTests<<"):";
      cin>>nrTests;
      cout<<"Choose pathfinder((b)eam search or (g)reedy breath first search):";
      cin>>alg;

      Point2D* starts[maxTests];
      Point2D* ends[maxTests];
  
        starts[0] = new Point2D(212.2,135.1);
        ends[0] = new Point2D(275.2,449.2);
        starts[1] = new Point2D(77,281.8);
        ends[1] = new Point2D(327.6,585);
        starts[2] = new Point2D(77, 467.2);
        ends[2] = new Point2D(365, 684.6);
        starts[3] = new Point2D(325.8, 665);
        ends[3] = new Point2D(116.6, 426);
        starts[4] = new Point2D(365, 225);
        ends[4] = new Point2D(77, 714.5);
        starts[5] = new Point2D(179.1, 419.5);
        ends[5] = new Point2D(327.6, 585);
        starts[6] = new Point2D(366.9, 584.3);
        ends[6] = new Point2D(179.1, 381.4);

        if(nrTests > maxTests)
          nrTests = maxTests;
  
        cout<<"Running Tests"<<endl;
        double totalTime = 0;
        for(int i = 0; i < nrTests; i++){
          gui->drawStartEnd(starts[i], ends[i]);
          Point2D** path;
          double time = 0;
          if(alg == 'b'){ 
            clock_t begin = clock();
            path = planner->beamSearch(i+1, speed, beamSize, starts[i], ends[i]);
            clock_t end = clock();
            time = double(end - begin) / CLOCKS_PER_SEC;
          }else if(alg == 'g'){
            clock_t begin = clock();
            path = planner->getPath(i+1, starts[i], ends[i]);
            clock_t end = clock();
            time = double(end - begin) / CLOCKS_PER_SEC;
          }
          totalTime += time;
          cout<<"*****************************Test number "<<i+1<<"*****************************"<<endl;
          cout<<"Time:"<<time<<endl;
          cout<<"Number of nodes visited: "<<planner->visited<<endl;
          cout<<"***********************************************************************"<<endl;
          cout<<endl;
          gui->drawPath(path);
          usleep(5000000);
        }
        cout<<endl;
        cout<<"*****************************TOTAL*****************************"<<endl;
        cout<<"Total time:"<<totalTime<<endl;
        cout<<"Number of Collisions: "<<countCollisions(planner) + planner->collisions<<endl;
        cout<<"***********************************************************************"<<endl;
        
         
        while(1);
    } else if (cmd.compare("-random") == 0){
      cout<<"Printing Random Paths"<<endl;
      Gui* gui = new Gui();
      std::thread windowthread(&gui->createWindow);
      srand(time(NULL));
      char quit;
      int id = 1;
      do
      {
        Point2D* startpoint = planner->graph[rand() % 313]->getPosition();
        Point2D* endpoint = planner->graph[rand() % 313]->getPosition();
        gui->drawStartEnd(startpoint, endpoint);
        
        
        Point2D** path;
        cout<<"Choose pathfinder((b)eam search or (g)reedy breath first search):";
        char alg;
        cin>>alg;
        if(alg == 'g'){ 
          path = planner->getPath(id, startpoint, endpoint);
        }else if(alg == 'b'){
          path = planner->beamSearch(id, speed, beamSize, startpoint, endpoint);
        }
        gui->drawPath(path);
        cout<<"Printing out ("<<startpoint->getX()<<","<<startpoint->getY()<<")  ---->  (";
        cout<<endpoint->getX()<<","<<endpoint->getY()<<")"<<endl;
        cout<<"Do you want to quit? (y/n)";
        cin>>quit;
        id++;
      } while(quit != 'y');
    }
  }

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

  if(argc == 4){
    string cmd = argv[1];
    if(cmd.compare("-test") == 0){
      string world = argv[2];
      int nrtests = stoi(argv[3]);

      Point2D* starts[nrtests];
      Point2D* ends[nrtests];
      srand(time(NULL));
      for(int i = 0; i < nrtests; i++){
        starts[i] = planner->graph[rand() % 313]->getPosition();
        ends[i] = planner->graph[rand() % 313]->getPosition();
      }
  
      Gui* gui[2];
      for(int alg = 0; alg < 2; alg++){
        cout<<"Running Tests"<<endl;
        double totalTime = 0;
        gui[alg] = new Gui();
        std::thread windowthread(&gui[alg]->createWindow);
        usleep(1000000);
        for(int i = 0; i < nrtests; i++){
          gui[alg]->drawStartEnd(starts[i], ends[i]);
          Point2D** path;
          double time = 0;
          if(alg){ 
            clock_t begin = clock();
            path = planner->beamSearch(i+1, speed, beamSize, starts[i], ends[i]);
            clock_t end = clock();
            time = double(end - begin) / CLOCKS_PER_SEC;
          }else{
            clock_t begin = clock();
            path = planner->getPath(i+1, starts[i], ends[i]);
            clock_t end = clock();
            time = double(end - begin) / CLOCKS_PER_SEC;
          }
          totalTime += time;
          cout<<"*****************************Test number "<<i+1<<"*****************************"<<endl;
          cout<<"Time:"<<time<<endl;
          cout<<"Number of nodes visited: "<<planner->visited<<endl;
          cout<<"***********************************************************************"<<endl;
          cout<<endl;
          gui[alg]->drawPath(path);
          usleep(5000000);
        }
        cout<<endl;
        cout<<"*****************************TOTAL*****************************"<<endl;
        cout<<"Total time:"<<totalTime<<endl;
        cout<<"Number of Collisions: "<<countCollisions(planner) + planner->collisions<<endl;
        cout<<"***********************************************************************"<<endl;
        windowthread.detach();
        usleep(1000000);
      }
         
        while(1);
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

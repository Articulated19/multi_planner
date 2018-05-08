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
#include <sys/wait.h>

#include "Gui.cpp"

int countCollisions(multi_planner*);
void printPath(Point2D**);

int beamSize = 100;
double speed = 10;

int main(int argc, const char * argv[]) {

  //std::cout<<"planner spawned"<<endl;
  multi_planner* planner = new multi_planner();
  //planner->checkTakenNodes();
  if(argc >= 4){
    string cmd = argv[1];
    if(cmd.compare("-test") == 0){
      string world = argv[2];
      int worldSize = 0;
      if(world.compare("small") == 0){
        worldSize = 313;
        planner->setWorld(0);
      }
      else if(world.compare("medium") == 0){
        worldSize = 655;
        planner->setWorld(1);
      }
      else if(world.compare("large") == 0){
        worldSize = 997;
        planner->setWorld(2);
      }
      
      planner->createGraph();
      int nrtests = stoi(argv[3]);
      
      const char ** checkArgs = argv;
      
      bool details = false;
      bool showGraph = false;
  
      while(*checkArgs){
        string arg = *checkArgs;
        if(arg.compare("-g") == 0){
          showGraph = true;
        } else if(arg.compare("-d") == 0){
          details = true;
        }
        checkArgs++;
      }
      
      Point2D* starts[nrtests];
      Point2D* ends[nrtests];
      srand(time(NULL));
      for(int i = 0; i < nrtests; i++){
        starts[i] = planner->graph[rand() % worldSize]->getPosition();
        ends[i] = planner->graph[rand() % worldSize]->getPosition();
      }
  
        cout<<"Running Tests"<<endl;
        double totalTime = 0;
        int collisions = 0;
        int totalVisited = 0;
        int pid = fork();
        if(pid != 0){
          waitpid(pid,NULL,0);
        }
        Gui* gui;
        gui = new Gui();
        std::thread windowthread(&gui->createWindow);
        usleep(1000000);
        string alg = "";
        for(int i = 0; i < nrtests; i++){
          if(showGraph)
            gui->drawStartEnd(starts[i], ends[i]);
          Point2D** path;
          double time = 0;
          if(pid){
            alg = "Beam Search"; 
            clock_t begin = clock();
            path = planner->beamSearch(i+1, speed, beamSize, starts[i], ends[i]);
            clock_t end = clock();
            time = double(end - begin) / CLOCKS_PER_SEC;
          }else{
            alg = "Greedy Best First Search";
            clock_t begin = clock();
            path = planner->getPath(i+1, starts[i], ends[i]);
            clock_t end = clock();
            time = double(end - begin) / CLOCKS_PER_SEC;
          }
          collisions += planner->collisions;
          totalTime += time;
          totalVisited += planner->visited;
          if(details){
              cout<<"*****************************Test number "<<i+1<<"*****************************"<<endl;
              cout<<"Start: ("<<starts[i]->getX()<<","<<starts[i]->getY()<<")"<<endl;
              cout<<"end: ("<<ends[i]->getX()<<","<<ends[i]->getY()<<")"<<endl;
              cout<<"Algorithm: "<<alg<<endl;
              cout<<"Time: "<<time<<endl;
              cout<<"Collided: "<<planner->collisions<<endl;
              cout<<"Path size: "<<planner->pathCapacity<<endl;
              cout<<"Number of nodes visited: "<<planner->visited<<endl;
              cout<<"***********************************************************************"<<endl;
              cout<<endl;
          }
          if(showGraph){
            gui->drawPath(path);
            usleep(5000000);
          }
        }
        cout<<endl;
        cout<<"*****************************TOTAL*****************************"<<endl;
        cout<<"Algorithm: "<<alg<<endl;
        cout<<"Total time: "<<totalTime<<endl;
        cout<<"Number of Collisions: "<<collisions<<endl;
        cout<<"Visited: "<<totalVisited<<endl;
        cout<<"***********************************************************************"<<endl;
        
        //usleep(1000000);
        //cout<<"i="<<i<<" nrtests="<<nrtests<<endl;
        exit(0);
      }
    planner->createGraph();
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
    planner->createGraph();
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
    planner->createGraph();
    std::string cmd = argv[1];
    if(cmd.compare("-clear") == 0){
      system("exec rm -r data/*");
      cout << "Cleared path data"<<endl;
    }
     else if (cmd.compare("-random") == 0){
      planner->createGraph();
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
    planner->createGraph();
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


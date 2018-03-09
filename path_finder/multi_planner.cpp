#include <stdio.h>
#include <iostream>
#include <fstream>
#include "lib/Point2D.h"
#include <stdlib.h>
#include <string>
#include <vector>
#include <sstream>



using namespace std;

#include "Gui.h"
#include "lib/Node.cpp"

class multi_planner{

public:
  Node* graph[1000];
  Point2D* path[500];

  Point2D** getPath(Point2D* startpoint, Point2D* endpoint){
    //cout << "startpoint: x" << startpoint->x << " , startpoint y:" << startpoint->y<<"\n";
    //cout << "endpoint: x" << endpoint->x << " , endpoint y:" << endpoint->y<<"\n";
    path[0] = startpoint;
    path[1] = endpoint;

    //cout<< path[0]->y << "\n";
    //cout<< path[0]->x << "\n";

    return path;
  }

  Point2D** getGraphAsPath(){
    return path;
  }


  void createGraph(){
    ifstream input("graph.txt");
    double pos[2];

    string arr[5000];
    string line;
    if(input.is_open()){
      int i = 0;
      while(!input.eof()){
        getline(input, line);
        arr[i] = line;
        i++;
        }
    }
      input.close();

      Point2D* points[5];
      Point2D* neighbours[5];

      int x = 0;
      for(int i = 0; i < 1000; i++){
        if(arr[i] == "NODE"){
          i++;
          int k = 0;
          while(arr[i] != "ENDNODE"){
            //cout<<arr[i]<<endl;
            string str = arr[i];

            std::replace(str.begin(), str.end(), ',' , ' ');
            std::replace(str.begin(), str.end(), ';' , ',');

            stringstream ss(str);
            int tmp;
            int j = 0;
            while(ss >> tmp){
              pos[j] = tmp / 10;
              j++;
              cout << "tmp:" << tmp << endl;
            }
            //cout << "Crate point with x: " << pos[0] << ", y: " << pos[1] << endl;;
            points[k] = new Point2D(pos[0], pos[1]);
            //cout << "created point with k: " << k << "  , x:" << points[k]->x << endl;
            i++;
            k++;
            cout<<endl;
          }
          k = 1;
          for(int i = 0; i < k ; i++){
            neighbours[i] = points[k];
            //cout << points[k]->x << ", " << points[k]->y << " added to neighbours for: " << points[0]->x << ", " << points[0]->y <<endl;
            //k++;
          }
          cout<<endl;

          cout << "Node created with posX: " << points[0]->x << " , posY: " << points[0]->y<<endl;
          int m = 0;
          while(neighbours[m]){
            cout << "and neighbours posX: " << neighbours[m]->x << ", posY: " << neighbours[m]->y << endl;
            m++;
          }
          graph[x] = new Node(neighbours, points[0]);
          path[x] = points[0];

          x++;
        }
      }
      cout << "Reading map completed." <<endl;
    }

};

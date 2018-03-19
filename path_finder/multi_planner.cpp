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
  Node* graph[313];
  Point2D* path[313];

  Point2D** getPath(Point2D* startpoint, Point2D* endpoint){
/*
    path[0] = startpoint;
    path[1] = endpoint;
*/
    cout << "Getting startnode.."<<endl;
    Node* startnode = getNode(startpoint);
    cout<< "Startnode: " << startnode->getPosition()->getX() << ", " << startnode->getPosition()->getY()<<endl;

    Node* endnode = getNode(endpoint);
    cout<< "Endnode: " << endnode->getPosition()->getX() << ", " << endnode->getPosition()->getY()<<endl;

/*
    Point2D** neighbour = startnode->getNeighbours();

    int i = 0;
    while(neighbour[i]){
      cout<<"neighbour: " << neighbour[i]->x <<", "<<neighbour[i]->y<<endl;
      path[i] = neighbour[i];
      i++;
    }
*/
    Node* current = startnode;
    Point2D** nbours;
    int i = 0;
    while(1){
      if(current == endnode){
        cout<<"Goal reached"<<endl;
        break;
      }
      nbours = current->getNeighbours();
      cout << "checking node: " << current->getPosition()->x << ", " <<current->getPosition()->y <<endl;
      double h = 10000;
      current = getNode(nbours[0]);

      for(int n = 0; n < 2 ; n++){
        //if(nbours[n]->getX() < 70) break;
        if(!nbours[n]) break;
        if(nbours[n]->getX() < 70) break;
        cout << nbours[n]->getX() <<" , " << nbours[n]->y;
        double tmp = manhattan_heuristics(nbours[n], endpoint);
        cout<< " with heurstics: " <<tmp <<endl;
        if(tmp < h) {
          h = tmp;
          current = getNode(nbours[n]);
        }
      }
      path[i] = current->getPosition();
      i++;
    }
    return path;
  }

  double manhattan_heuristics(Point2D* point, Point2D* goal){
    double x = goal->getX() - point->getX();
    double y = goal->getY() - point->getY();

    return abs(x) + abs(y);
  }

  Node* getNode(Point2D* point){
    //Node* result;
    double pointX = point->getX();
    double pointY = point->getY();
    for(unsigned int i = 0; i < 313 - 1; i++){
      if(graph[i]->getPosition()->getX() == pointX && graph[i]->getPosition()->getY() == pointY) {
        return graph[i];
      }
    }
    throw "Could not find node!";
  }


  Point2D** getGraphAsPath(){
    int i = 0;
    while(graph[i]){
      path[i] = graph[i]->getPosition();
      i++;
    }
    return path;
  }


  void createGraph(){
    ifstream input("graph.txt");
    double pos[5];

    string arr[2000];
    string wline;
    int num_lines = 0;

    if(input.is_open()){
      int i = 0;
      while(!input.eof()){
        getline(input, wline);
        arr[i] = wline;
        i++;
        }
      num_lines = i;
      input.close();
    }
      int x = 0;

      for(int i = 0; i < num_lines; i++){
        Point2D** points = new Point2D*[5];
        if(arr[i] == "NODE"){
          i++;
          int k = 0;
          while(arr[i] != "ENDNODE"){

            string str = arr[i];

            std::replace(str.begin(), str.end(), ',' , ' ');
            std::replace(str.begin(), str.end(), ';' , ' ');

            stringstream ss(str);
            double tmp;
            int j = 0;
            while(ss >> tmp){
              pos[j] = tmp;
              j++;
            }
            for(int n = 0 ; n < j; n += 2){
              points[k] = new Point2D(pos[n], pos[n+1]);
              k++;
            }
            i++;
          }
          //cout<<"node: "<<points[0]->getX() <<", "<<points[0]->getY()<<endl;
          Point2D** neighbours = new Point2D*[3];

          int m = 1;
          for(int index = 0; index < k - 1 ; index++){
            neighbours[index] = points[m];
            //cout<<"neighbours: " << points[m]->getX() << ", " << points[m]->getY() <<endl;
            m++;
          }

          graph[x] = new Node(neighbours, points[0]);
          //delete neighbours;
          delete points;
          x++;
        }
      }
      cout << "Reading map completed." <<endl;
    }
};

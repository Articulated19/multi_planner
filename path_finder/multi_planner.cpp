#include <stdio.h>
#include <iostream>
#include <fstream>
#include "lib/Point2D.h"
#include <stdlib.h>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <dirent.h>

using namespace std;

#include "Gui.h"
#include "lib/Node.cpp"

class multi_planner{

public:
  Node* graph[313];
  Point2D* path[313];

  Point2D** getPath(int id, Point2D* startpoint, Point2D* endpoint){

    //cout << "Getting startnode.."<<endl;
    Node* startnode = getNode(startpoint);
    //cout<< "Startnode: " << startnode->getPosition()->getX() << ", " << startnode->getPosition()->getY()<<endl;

    Node* endnode = getNode(endpoint);
    //cout<< "Endnode: " << endnode->getPosition()->getX() << ", " << endnode->getPosition()->getY()<<endl;

    Node* current = startnode;
    Point2D** nbours;
    int i = 0;
    while(1){
      if(current == endnode){
        //cout<<"Goal reached"<<endl;
        break;
      }
      nbours = current->getNeighbours();
      //cout << "checking node: " << current->getPosition()->getX() << ", " <<current->getPosition()->getY() <<endl;
      double h = 10000;
      current = getNode(nbours[0]);

      for(int n = 0; n < 2 ; n++){
        //if(nbours[n]->getX() < 70) break;
        if(!nbours[n]) break;
        if(nbours[n]->getX() < 70) break;

        double tmp = manhattan_heuristics(nbours[n], endpoint);
        Node* tmpNode = getNode(nbours[n]);
        //cout<< " with heurstics: " <<tmp <<endl;
        if(!tmpNode->isTaken(id)){
          if(tmp < h) {
            h = tmp;
            current = tmpNode;
          }
        }
        else{
          //cout<<"Node was taken!"<<endl;
        }
      }
      if(!current->isTaken(id)){
        current->take(id);
        path[i] = current->getPosition();
      }
      else{
        /* Did not find a path to goal */
        //cout << "Could not find a path to goal"<<endl;
        Gui::drawError(current->getPosition());
        return path;
      }
      i++;
    }
    return path;
  }

  double manhattan_heuristics(Point2D* point, Point2D* goal){
    double x = goal->getX() - point->getX();
    double y = goal->getY() - point->getY();

    //return abs(x) + abs(y);
    return sqrt( pow(x, 2) + pow(y,2));

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
    //cerr<<"Did not find node!"<<endl;
    return new Node({}, new Point2D(0,0));
  }

  void checkTakenNodes(){
    string pathFiles[10];
    int filecount = 0;

    DIR *dir;
    struct dirent *ent;
    if((dir = opendir("data")) != NULL){
      while((ent = readdir(dir)) != NULL){
        string tmp = ent->d_name;
        if(std::string::npos != tmp.find("path")){
          pathFiles[filecount] = tmp;
          filecount++;
        }
      }
      closedir(dir);
    } else {
      perror("");
    }
    for(int i = 0 ; i < filecount; i++){
      string filename = "data/" + pathFiles[i];
      string trimnum = (pathFiles[i].erase(0, 5));
      string num = trimnum.substr(0, trimnum.length()-4);
      ifstream input(filename);
      string wline;

      if(input.is_open()){
      double pos[5];
        while(!input.eof()){
          getline(input, wline);
          std::replace(wline.begin(), wline.end(), ',' , ' ');
          stringstream ss(wline);
          double tmp;
          int x = 0;
          while(ss >> tmp){
            pos[x] = tmp;
            x++;
          }
          Point2D* point = new Point2D(pos[0], pos[1]);
          //cout<<"pos[0]: "<<pos[0]<< ", pos[1]:" << pos[1]<<endl;
          Node* node = getNode(point);
          node->take(stoi(num));
        }
        input.close();
      }
      else{
        //cout << "id "<<num<<" has no path yet"<<endl;
      }
    }
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
              pos[j] = tmp / 10;
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
      //cout << "Reading map completed." <<endl;
    }
};

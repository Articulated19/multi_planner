#include <stdio.h>
#include <iostream>
#include <fstream>
#include "lib/Point2D.h"
#include "lib/Path.cpp"
#include <stdlib.h>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <dirent.h>
#include <queue>

using namespace std;

#include "Gui.h"
#include "lib/Node.cpp"

class multi_planner{

public:
  Node* graph[1000];
  Point2D* path[1000];
  int world = 0;
  int visited = 0; // Used for measuring
  unsigned int graphSize = 313;
  int collisions = 0;
  int pathCapacity = 0;
  
  void setWorld(int n){
    if(n == 0){
      graphSize = 313;
    } else if(n == 1){
      graphSize = 655;
    } else if(n == 2){
      graphSize = 997;
    }
    world = n;
  }

  void resetResults(){
    visited = 0;
    collisions = 0;
    pathCapacity = 0;
  }

  Point2D** getPath(int id, Point2D* startpoint, Point2D* endpoint){
    resetResults();
    //cout << "Getting startnode.."<<endl;
    Node* startnode = getNode(startpoint);
    //cout<< "Startnode: " << startnode->getPosition()->getX() << ", " << startnode->getPosition()->getY()<<endl;

    Node* endnode = getNode(endpoint);
    //cout<< "Endnode: " << endnode->getPosition()->getX() << ", " << endnode->getPosition()->getY()<<endl;

    Node* current = startnode;
    Point2D** nbours;
    int i = 0;
    visited++;
    while(1){
      if(current == endnode){
        //cout<<"Goal reached"<<endl;
        break;
      }
      nbours = current->getNeighbours();
      //cout << "checking node: " << current->getPosition()->getX() << ", " <<current->getPosition()->getY() <<endl;
      double h = 10000;
      current = getNode(nbours[0]);
      visited++;
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
            visited++;
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
        collisions++;
        Gui::drawError(current->getPosition());
        return path;
      }
      i++;
      pathCapacity++;
    }
    return path;
  }

  struct PathCompare{
    bool operator()(Path* n1, Path* n2){
      return n1->getCost() > n2->getCost();
    }
  };

  Point2D** beamSearch(int id, double speed, int beamSize, Point2D* startpoint, Point2D* endpoint){
    resetResults();
    Node* startnode = getNode(startpoint);
    startnode->setCurrentFvalue(manhattan_heuristics(startpoint,endpoint));
    Node* endnode = getNode(endpoint);
    endnode->setCurrentFvalue(0);
    //Node* endnode = getNode(endpoint);
    priority_queue<Path*, vector<Path*>, PathCompare> beam;
    Path* start = new Path();
    start->addNode(startnode);
    beam.push(start);
    Node* current;
    Path* currentPath;
    while(beam.size()){
      //1.Remove the best node from the beam
      visited++;
      currentPath = beam.top();
      beam.pop();
      current = currentPath->fst();
      //2.If we find a goal then we backtrace back to the start and return path
      if(current->getPosition()->equals(endpoint))
        return backtrace(id,speed,currentPath);
      //3.Get neighbors from current
      Point2D** neighbors = current->getNeighbours();
      //4.Add each successor to beam and record it's parent
      for(int n = 0; n < 2; n++){
        if(!neighbors[n]) break;
        if(neighbors[n]->getX() < 70) break;
        Path* newPath;
        Node* newNode = getNode(neighbors[n]);
        newPath = currentPath->addNodeAndClone(newNode);
        newPath->increaseCost(newPath->path_length() + fvalue(currentPath, newNode, endnode, speed));
        beam.push(newPath);
      }
      delete currentPath;
      //5.Remove highest elements if beam capacity is higher than beam size
      priority_queue<Path*, vector<Path*>, PathCompare> tmp;
      for(int i = 0; i < beamSize && beam.size() > 0; i++){
        tmp.push(beam.top());
        beam.pop();
      }
      beam.swap(tmp);
    }
    return path; // Found no path

  }

  Point2D** backtrace(int id, double speed, Path* result){
    //int pathSize = result->path_length();
    vector<Node*>* v = result->getPath();
    vector<Node*>* vPath = new vector<Node*>();
    bool foundCollision = false;
    while(v->size()){
      Node* n = v->back();
      v->pop_back();
      if(n->is_end_node()){
        delete vPath;
        vPath = new vector<Node*>();
        foundCollision = true;
      } else {
        vPath->push_back(n);
      }
    }    
    
    //pathSize--;
    int i = 0;
    Node* current = vPath->back();
    int backStep = 0;
    if(vPath->size() > 3 && foundCollision)
      backStep = 3;
    while(1){
      current->take(id,i+1,speed);
      path[i] = current->getPosition();
      pathCapacity++;
      i++;
      vPath->pop_back();
      if(vPath->size() - backStep){
        current = vPath->back();
      }
      else
      {
        current->enableEndNode();
        if(foundCollision){
          collisions++;
          Gui::drawError(current->getPosition());
        }
        break;
      }
    }
    return path;
  }

  void printBeam(priority_queue<Path*, vector<Path*>, PathCompare> beam){
    priority_queue<Path*, vector<Path*>, PathCompare> tmp = beam;
    cout<<"The beam is:"<<endl;
    while(tmp.size()){
      cout<<tmp.top()->getCost()<<endl;
      tmp.pop();
    }
  }

  double fvalue(Path* current, Node* point, Node* goal, double speed){
    return manhattan_heuristics(point->getPosition(), goal->getPosition()) + meeting_avoidance(current, point, speed);
  }

  double meeting_avoidance(Path* current, Node* go_to, double speed){
    double expectedArrival = time(0) + (current->path_length()/speed)*60*60;
    double result = current->getCost();
    for(auto const& x : *(go_to->getTakenAgents())){
      if(expectedArrival > x.second + speed) continue;
      current->increase_meeting_risk_lvl();
      result = pow(result,current->get_meeting_risk_lvl());
    }
    
    if(isinf((float)result)) return 0; //if result is too big then choose the path with collision
    return result;
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
      for(unsigned int i = 0; i < graphSize - 1; i++){
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
    string graph_name;
    if(world == 1){
      graph_name = "medium";
    }
    else if(world == 2){
      graph_name = "large";
    }
    else{
      graph_name = "small";
    }

    ifstream input(graph_name + ".txt");
    double pos[5];

    string arr[5000];
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


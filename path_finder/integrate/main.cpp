#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "../multi_planner.cpp"
#include <thread>
#include <unistd.h>
#include <time.h>

using namespace std;

#include "../lib/Node.h"
#include "../lib/Point2D.h"

int main(int argc, const char * argv[]) {
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
}

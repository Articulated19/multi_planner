#include <SFML/Graphics.hpp>
#include "Gui.h"
#include <iostream>
#include "lib/Point2D.h"

using namespace std;

Point2D** Gui::paths[500];
Point2D** Gui::todraw[500];
Point2D*  Gui::errors[10];
Point2D*  Gui::startend[10];
sf::Color Gui::color;
int pathcounter = 0;
int errorcount = 0;
//sf::RenderWindow window;

void Gui::createWindow()
{
  sf::RenderWindow window(sf::VideoMode(560, 965), "mutli_planner");
  window.setFramerateLimit(20);
  sf::Texture bg;

  if(!bg.loadFromFile("map_centerline.png"))
  {
    cerr<< "Could not find map";
  }

  sf::Sprite background(bg);

  window.clear();
  //window.draw(background);
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      window.close();
    }
    //window.draw(background);

    if(pathcounter > 0){
        int start_x = startend[0]->getX() * 10;
        int start_y = startend[0]->getY() * 10;
        int end_x   = startend[1]->getX() * 10;
        int end_y   = startend[1]->getY() * 10;

        sf::CircleShape st(10);
        st.setPosition(start_x / 10 -10, start_y / 10 -10);
        st.setFillColor(sf::Color::White);
        window.draw(st);


        sf::CircleShape ed(10);
        ed.setPosition(end_x / 10 -10, end_y / 10 -10);
        ed.setFillColor(sf::Color::White);
        window.draw(ed);
    }


    for(int i = 0; i < pathcounter; i++){
    //if(Gui::paths[i]){
      if(todraw[i]){
        while(*todraw[i]){
          int point_x = todraw[i][0]->getX() *10;
          int point_y = todraw[i][0]->getY() *10;
          todraw[i][0] = 0;


          //cout <<"drawing at: " << point_x << ", " <<  point_y << "\n";
          sf::RectangleShape pt(sf::Vector2f(10,10));
          //pt.setPosition(point_x / 10 - 5,point_y / 10 - 5);
          if(i == 0) {
            pt.setSize(sf::Vector2f(10,10));
            pt.setFillColor(sf::Color::Blue);
            pt.setPosition(point_x / 10 - 5,point_y / 10 - 5);
          }
          if(i == 1) {
            pt.setSize(sf::Vector2f(7,7));
            pt.setFillColor(sf::Color::Green);
            pt.setPosition(point_x / 10 -3,point_y / 10 -3);
          }
          if(i == 2){
            pt.setFillColor(sf::Color::Magenta);
            pt.setSize(sf::Vector2f(4,4));
            pt.setPosition(point_x / 10,point_y / 10 );
          }
          if(i == 3){
            pt.setFillColor(sf::Color::Yellow);
            pt.setSize(sf::Vector2f(4,4));
            pt.setPosition(point_x / 10,point_y / 10 );
          }

          window.draw(pt);
          window.display();
          //sf::sleep(sf::milliseconds(10));
          todraw[i]++;
        }
        todraw[i] = 0;
        //Gui::paths[i] = 0;
      }
      for(int i = 0; i < errorcount ; i++){
        int point_x = errors[i]->getX() * 10;
        int point_y = errors[i]->getY() * 10;

        sf::RectangleShape er(sf::Vector2f(10,10));
        er.setPosition(point_x / 10 -5, point_y / 10 -5);
        er.setFillColor(sf::Color::Red);

        window.draw(er);
      }
      //Gui::paths[i] = 0;
      //Gui::todraw[i] = 0;
    }
    window.display();
  }
}

void Gui::drawPath(Point2D** path)
{
  //Gui::paths[pathcounter] = path;
  todraw[pathcounter] = path;
  pathcounter++;
  cout << "Pathcounter: " <<pathcounter<<endl;
}

void Gui::drawError(Point2D* err){
  Gui::errors[errorcount] = err;
  errorcount++;
}

void Gui::drawStartEnd(Point2D* start, Point2D* end){
  Gui::startend[0] = start;
  Gui::startend[1] = end;

}

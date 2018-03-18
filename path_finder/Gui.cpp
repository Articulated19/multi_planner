#include <SFML/Graphics.hpp>
#include "Gui.h"
#include <iostream>
#include "lib/Point2D.h"

using namespace std;

Point2D** Gui::paths;
//sf::Color color;
//sf::RenderWindow window;

void Gui::createWindow()
{
  sf::RenderWindow window(sf::VideoMode(560, 965), "mutli_planner");
  window.setFramerateLimit(10);
  sf::Texture bg;

  if(!bg.loadFromFile("map_centerline.png"))
  {
    cerr<< "Could not find map";
  }

  sf::Sprite background(bg);

  window.clear();
  window.draw(background);
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      window.close();
    }

    if(Gui::paths){

      Point2D** todraw = Gui::paths;

      while(*todraw){
        int point_x = todraw[0]->x;
        int point_y = todraw[0]->y;
        //todraw[0] = 0;

        //cout <<"drawing at: " << point_x << ", " <<  point_y << "\n";

        sf::RectangleShape pt(sf::Vector2f(10,10));
        pt.setPosition(point_x / 10 - 5,point_y / 10 - 5);
        pt.setFillColor(sf::Color::Green);
        window.draw(pt);
        todraw++;
      }
      Gui::paths = 0;
    }

    window.display();
  }
}

void Gui::drawPath(Point2D** path)
{
  Gui::paths = path;
}

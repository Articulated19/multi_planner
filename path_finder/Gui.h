#ifndef Gui_h
#define Gui_h

#include "lib/Point2D.h"
#include <SFML/Graphics.hpp>

class Gui{
  public :
  static void createWindow();
  static void drawPath(Point2D**);

  static Point2D** paths;
  //static sf::Color color;

};

#endif /* Gui_h */

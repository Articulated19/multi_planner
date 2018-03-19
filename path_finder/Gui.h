#ifndef Gui_h
#define Gui_h

#include "lib/Point2D.h"
#include <SFML/Graphics.hpp>

class Gui{
  public :
  static void createWindow();
  static void drawPath(Point2D**);
  static void drawError(Point2D*);
  static void drawStartEnd(Point2D*, Point2D*);

  static Point2D** paths[];
  static Point2D** todraw[];
  static Point2D* errors[];
  static Point2D* startend[];
  static sf::Color color;

};

#endif /* Gui_h */

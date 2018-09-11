#ifndef _world_h_
#define _world_h_

#include <list>
#include "body.h"
#include "input.h"

using std::list;

class World
{
 public:
  static void init();
  static void terminate();
  static void update(double dt);
  static void draw();
  static void add(Body*);
  static void remove(Body*);

  static Body* inside(double x, double y, Body *ignore = 0);
  
  static void setPlayerInfo(double x, double y, double vx = 0, double vy = 0);
 private:
  static list<Body *> objects;
  static list<Body *>::iterator currentObject;
  static bool removeCurrentObject;
  
 public:
  static double playerX, playerY, playerVX, playerVY;
};

#endif

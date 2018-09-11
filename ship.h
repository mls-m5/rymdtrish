#ifndef _ship_h_
#define _ship_h_
#include "body.h"

class Ship: public Body{
 private:
  
 public:
  Ship(){Body(); isPlayer = 0;};
  Ship(double x, double y, double angle){isPlayer = 0; this->x = x; this->y = y;};
  Ship(double x, double y, double angle, 
       double vx, double vy, double vangle)
    {Body(x,y,angle, vx,vy,vangle);};
  void update(double dt);
  void draw() const ;
  void accelerate(double ax, double ay);
  void fire(int i);
  void setPlayer(bool player = 1);
  void AI(double dt);
  void kill();
  
  protected:
  bool isPlayer;
};

#endif

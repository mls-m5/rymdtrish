#include "body.h"
#include "world.h"

Body::Body()
{
  x = y = 0;
  angle = 0;
  vx = vy = vangle = 0;

  size = 1;
  r = g = b = 1;
  duration = -1;
  hitPoints = 1;
}

Body::Body(double x, double y, double angle)
{
  this->x = x;
  this->y = y;
  this->angle = angle;
  vx = vy = vangle = 0;

  size = 1;
  r = g = b = 1;
  duration = -1;
  hitPoints = 1;
}

Body::Body(double x, double y, double angle,
	   double vx, double vy, double vangle)
{
  this->x = x;
  this->y = y;
  this->angle = angle;
  this->vx = vx;
  this->vy = vy;
  this->vangle = vangle;

  size = 1;
  r = g = b = 1;
  duration = -1;
  hitPoints = 1;
}

void Body::update(double dt)
{
  x += vx*dt;
  y += vy*dt;
  angle += vangle*dt;
  while (angle >= 2*PI)
    angle -= 2*PI;
  while (angle <= 0)
    angle += 2*PI;

  
  if (duration != -1){
    duration -= dt;
    //kill the object if there is no more time
    if (duration < 0) kill();
  }
}

void Body::kill(){
  World::remove(this);
}

bool Body::inside(double px, double py) const{
  double dx = x - px, dy = y - py;
  if (dx * dx + dy * dy <= size){
    return 1;
  }
  else{
    return 0;
  }
}

void Body::hit(double d){
  hitPoints -= d;
  if (hitPoints <= 0){
    kill();
  }
}

void Body::setDuration(double d){
  duration = d;
}

void Body::setHitPoints(double hp){
  hitPoints = hp;
}

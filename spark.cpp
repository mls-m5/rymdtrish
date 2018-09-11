#include "spark.h"
#include "draw.h"
#include "world.h"

void Spark::update(double dt){
	angle += dt * 2.;
  x += vx * dt; y += vy * dt;
  vx /= (1 + dt);
  vy /= (1 + dt);
  
  r = (rand() % 100) / 100.;
  g = (rand() % 100) / 100.;
  b = (rand() % 100) / 100.;
  this->Body::update(dt);
}

Spark::Spark(double x, double y, double vx, double vy){
	Body(x,y,0, vx, vy, 0);
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	//cout << "x: " << x << endl;
}


//Draws the ship
void Spark::draw()const {
  //Draw::drawShip(x,y,angle,1,0,1);
  Draw::drawSpark(x,y,angle,r / angle,g / angle,b / angle);
}




#include "world.h"
#include "body.h"
#include "asteroid.h"
#include "projectile.h"
#include "ship.h"

//Create the static variables
list <Body*> World::objects;
list <Body*>::iterator World::currentObject;
bool World::removeCurrentObject;
double World::playerX, World::playerY, World::playerVX, World::playerVY;

void World::init()
{
  objects.push_back(new Asteroid(0, 0, 0, 1, 2, 2*2*PI));
  objects.push_back(new Asteroid(-2, 0, PI, 1, 2, 2*PI));
  //objects.push_back(new Projectile(-4, -3, -PI/2, 3, 0, 0));
  
  Ship *s = new Ship();
  s->setPlayer();
  objects.push_back(s); 
  objects.push_back(new Ship(10,1,1));
  objects.push_back(new Ship(10,1,1));
  objects.push_back(new Ship(-10,20,1));
}

void World::terminate()
{
  list<Body *>::iterator it;
  for (it = objects.begin(); it != objects.end(); ++it) {
    delete (*it);
    objects.erase(it);
  }
}

void World::update(double dt)
{

  //The previous method
  // Iterate through all objects in the world and update them
  //list<Body *>::iterator it;
  //for (it = objects.begin(); it != objects.end(); ++it) {
  //  (*it)->update(dt);
  //}

  //Iterate througth all objects
  //This method can handle when some objects tries to remove themselves during update
  //Se World::remove to get a clearer picture
  currentObject = objects.begin();
  while (currentObject != objects.end()){
    //Resets the remove flag
    removeCurrentObject = 0;

    //Handles the updating
    //Sometimes the object will try to remove itself
    (*currentObject)->update(dt);
    if (removeCurrentObject){
      //Remove the updated object and move on to the next one
      currentObject = objects.erase(currentObject);
    }
    else{
      //Only moves on to the next object
      ++currentObject;
    }
    
  }

  //Note that in the end currentObject is objects.end() witch is not in the listy
}


void World::draw()
{
  // Iterate through all objects in the world and draw them
  list<Body *>::iterator it;
  for (it = objects.begin(); it != objects.end(); ++it) {
    (*it)->draw();
  }
}

void World::add(Body *b){
  objects.push_front(b);
}

void World::remove(Body *b){
  if (b == *currentObject){
    removeCurrentObject = 1;
  }
  else{
    objects.remove(b);
  }
}

Body* World::inside(double x, double y, Body *ignore){
  //Return the first found object that is found in (x,y)
  for (list<Body*>::iterator it = objects.begin(); it != objects.end(); ++it){
    if ((*it)->inside(x,y)){
      //Check so the object is not ignored
      if (*it != ignore){
	return (*it);
      }
    }
  }
  return 0;
}

void World::setPlayerInfo(double x, double y, double vx, double vy){
	playerX = x;
	playerY = y;
	playerVX = vx;
	playerVY = vy;
}


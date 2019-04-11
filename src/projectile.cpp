#include "projectile.h"
#include "draw.h"
#include "world.h"
#include "explosion.h"

void Projectile::draw() const
{
  Draw::drawProjectile(x, y, angle);
}

void Projectile::update(double dt){
  Body *collision;
  this->Body::update(dt);
  
  collision = World::inside(x,y,owner);
  if (collision){
    //Domages the found object
    collision->hit(10);
    //Destroy the own object
    kill();

    World::add(new Explosion(x,y,.3,.5,.5,1));
  }
}

#include "explosion.h"
#include "draw.h"

Explosion::Explosion(World &world,
                     double nX,
                     double nY,
                     double nSize,
                     double r,
                     double g,
                     double b)
    : Body(world, nX, nY, 0) {
    size(nSize);
    this->r(r);
    this->g(g);
    this->b(b);
}

void Explosion::update(double dt) {
    _size -= dt;
    if (_size < .01) {
        this->Body::kill();
    }
}

void Explosion::draw() const {
    Draw::drawAsteroid({_x, _y, _angle, _r, _g, _b, _size});
}

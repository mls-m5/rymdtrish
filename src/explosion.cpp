#include "explosion.h"
#include "draw.h"

Explosion::Explosion(
    double nX, double nY, double nSize, double r, double g, double b)
    : Body(nX, nY, 0) {
    size = nSize;
    this->r = r;
    this->g = g;
    this->b = b;
}

void Explosion::update(double dt) {
    size -= dt;
    if (size < .01)
        this->Body::kill();
}

void Explosion::draw() const {
    Draw::drawAsteroid(x, y, angle, r, g, b, size);
}

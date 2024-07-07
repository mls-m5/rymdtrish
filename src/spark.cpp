#include "spark.h"
#include "draw.h"

void Spark::update(double dt) {
    _angle += dt * 2.;
    _x += _vx * dt;
    _y += _vy * dt;
    _vx /= (1 + dt);
    _vy /= (1 + dt);

    _r = (rand() % 100) / 100.;
    _g = (rand() % 100) / 100.;
    _b = (rand() % 100) / 100.;
    this->Body::update(dt);
}

Spark::Spark(double x, double y, double vx, double vy)
    : Body(x, y, 0, vx, vy, 0) {}

void Spark::draw() const {
    Draw::drawSpark({_x, _y, _angle, _r / _angle, _g / _angle, _b / _angle});
}

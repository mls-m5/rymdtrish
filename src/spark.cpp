#include "spark.h"
#include "draw.h"

void Spark::update(double dt) {
    angle += dt * 2.;
    x += vx * dt;
    y += vy * dt;
    vx /= (1 + dt);
    vy /= (1 + dt);

    r = (rand() % 100) / 100.;
    g = (rand() % 100) / 100.;
    b = (rand() % 100) / 100.;
    this->Body::update(dt);
}

Spark::Spark(double x, double y, double vx, double vy)
    : Body(x, y, 0, vx, vy, 0) {}

void Spark::draw() const {
    Draw::drawSpark({x, y, angle, r / angle, g / angle, b / angle});
}

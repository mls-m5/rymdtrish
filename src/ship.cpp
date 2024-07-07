#include "ship.h"
#include "draw.h"
#include "explosion.h"
#include "input.h"
#include "projectile.h"
#include "spark.h"
#include "world.h"
#include <cmath>

// A helper function that get the difference of a angle

double getAngle(double x, double y, double a) {
    double angle = atan2(x, y) + a;

    while (angle < pi) {
        angle += pi * 2.;
    }

    while (angle > pi) {
        angle -= pi * 2.;
    }

    return angle;
}

void Ship::update(double dt) {
    const double acceleration = 10.;
    const double angleAcceleration = .5;

    // Handeling input from the keyboard

    if (isPlayer) {
        if (Input::key(KEY_UP)) {
            accelerate(0, dt * acceleration);
        }
        if (Input::key(KEY_DOWN)) {
            accelerate(0, -dt * acceleration);
        }
        if (Input::key(KEY_LEFT)) {
            vangle += dt * angleAcceleration;
        }
        if (Input::key(KEY_RIGHT)) {
            vangle -= dt * angleAcceleration;
        }
        if (Input::key(' ')) {
            fire(0);
        }

        World::setPlayerInfo(x, y, vx, vy);
    }
    else {
        AI(dt);
    }

    x += vx * dt;
    y += vy * dt;
    angle += vangle;

    // adding som friction to the angularvolocity
    vangle /= (1. + dt * 5);

    if (isPlayer)
        Draw::transformView(x, y, angle);
}

// Draws the ship
void Ship::draw() const {
    Draw::drawShip({x, y, angle, 1, 0, 1});
}

// Accelerate the ship relative to the ships location
void Ship::accelerate(double ax, double ay) {
    auto sx = sin(angle);
    auto sy = cos(angle);

    // Apply the acceleration in the proper direction
    vx += sy * ax - sx * ay;
    vy += sy * ay + sx * ax;
}

void Ship::fire(int i) {
    // Add a projectile
    Projectile *p = World::create<Projectile>(
        x, y, angle, -sin(angle) * 30 + vx, cos(angle) * 30 + vy, 0);
    p->setDuration(1);
    p->setOwner(this);
}

void Ship::AI(double dt) {
    // vangle += ((rand() % 100) / 1000. - .05) / 2.;

    angle += getAngle(x - World::playerX, y - World::playerY, angle) * dt +
             ((rand() % 100) / 1000. - .05) / 2.;

    if (rand() % 100 > 90) {
        fire(0);
    }

    accelerate(0, dt * 4.);
}

void Ship::setPlayer(bool player) {
    isPlayer = player;
}

void Ship::kill() {
    for (int i = 0; i < 100; i++) {
        double a = (rand() % 10000) / 10000. * pi * 2.;
        double amp = pow((rand() % 10000) / 1000. - 5., 1.2);
        double sx = sin(a) * amp;
        double sy = cos(a) * amp;

        auto s = World::create<Spark>(x, y, sx, sy);
        s->setDuration(1 + (rand() % 100) / 100.);
    }

    World::create<Explosion>(x, y, 3., .5, .5, 1);

    this->Body::kill();
}

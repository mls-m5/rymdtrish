#include "ship.h"
#include "draw.h"
#include "explosion.h"
#include "input.h"
#include "projectile.h"
#include "spark.h"
#include "world.h"
#include <SDL2/SDL.h>
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

    _controller->update(dt);

    _x += _vx * dt;
    _y += _vy * dt;
    _angle += _vangle;

    // adding som friction to the angularvolocity
    _vangle /= (1. + dt * 5);

    _controller->postUpdate();
}

// Draws the ship
void Ship::draw() const {
    Draw::drawShip({_x, _y, _angle, 1, 0, 1});
}

// Accelerate the ship relative to the ships location
void Ship::accelerate(double ax, double ay) {
    auto sx = sin(_angle);
    auto sy = cos(_angle);

    // Apply the acceleration in the proper direction
    _vx += sy * ax - sx * ay;
    _vy += sy * ay + sx * ax;
}

void Ship::angleimpulse(double va) {
    _vangle += va;
}

void Ship::fire(int i) {
    Projectile *p = world().create<Projectile>(
        _x, _y, _angle, -sin(_angle) * 30 + _vx, cos(_angle) * 30 + _vy, 0);
    p->setDuration(1);
    p->setOwner(this);
}

void Ship::setController(std::unique_ptr<Controller> controller) {
    _controller = std::move(controller);
}

void Ship::kill() {
    for (int i = 0; i < 100; i++) {
        double a = (rand() % 10000) / 10000. * pi * 2.;
        double amp = pow((rand() % 10000) / 1000. - 5., 1.2);
        double sx = sin(a) * amp;
        double sy = cos(a) * amp;

        auto s = world().create<Spark>(_x, _y, sx, sy);
        s->setDuration(1 + (rand() % 100) / 100.);
    }

    world().create<Explosion>(_x, _y, 3., .5, .5, 1);

    this->Body::kill();
}

void Player::update(double dt) {
    const double acceleration = 10.;
    const double angleAcceleration = .5;

    // Handeling input from the keyboard
    if (Input::key(SDLK_UP)) {
        _ship->accelerate(0, dt * acceleration);
    }
    if (Input::key(SDLK_DOWN)) {
        _ship->accelerate(0, -dt * acceleration);
    }
    if (Input::key(SDLK_LEFT)) {
        _ship->angleimpulse(dt * angleAcceleration);
    }
    if (Input::key(SDLK_RIGHT)) {
        _ship->angleimpulse(-dt * angleAcceleration);
    }
    if (Input::key(' ')) {
        _ship->fire(0);
    }

    _ship->world().setPlayerInfo(
        _ship->x(), _ship->y(), _ship->vx(), _ship->vy());
}

void Player::postUpdate() {
    Draw::transformView(_ship->x(), _ship->y(), _ship->angle());
}

void AI::update(double t) {
    _ship->angle(_ship->angle() +
                 getAngle(_ship->x() - _ship->world().playerX,
                          _ship->y() - _ship->world().playerY,
                          _ship->angle()) *
                     t +
                 ((rand() % 100) / 1000. - .05) / 2.);

    if (rand() % 100 > 90) {
        _ship->fire(0);
    }

    _ship->accelerate(0, t * 4.);
}

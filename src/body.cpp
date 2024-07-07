#include "body.h"
#include "world.h"

Body::Body(World &world,
           double x,
           double y,
           double angle,
           double vx,
           double vy,
           double vangle)
    : _world{&world}
    , _x(x)
    , _y(y)
    , _angle(angle)
    , _vy(vy)
    , _vangle(vangle)
    , _size(1)
    , hitPoints(1)
    , duration(-1)
    , _vx(vx) {
    _r = _g = _b = 1;
}

void Body::update(double dt) {
    _x += _vx * dt;
    _y += _vy * dt;
    _angle += _vangle * dt;
    while (_angle >= 2 * PI) {
        _angle -= 2 * PI;
    }
    while (_angle <= 0) {
        _angle += 2 * PI;
    }

    if (duration != -1) {
        duration -= dt;
        // kill the object if there is no more time
        if (duration < 0)
            kill();
    }
}

void Body::kill() {
    world().remove(this);
}

bool Body::inside(double px, double py) const {
    double dx = _x - px, dy = _y - py;
    if (dx * dx + dy * dy <= _size) {
        return 1;
    }
    else {
        return 0;
    }
}

void Body::hit(double d) {
    hitPoints -= d;
    if (hitPoints <= 0) {
        kill();
    }
}

void Body::setDuration(double d) {
    duration = d;
}

void Body::setHitPoints(double hp) {
    hitPoints = hp;
}

double Body::x() const {
    return _x;
}

void Body::x(double nX) {
    _x = nX;
}

double Body::y() const {
    return _y;
}

void Body::y(double nY) {
    _y = nY;
}

double Body::angle() const {
    return _angle;
}

void Body::angle(double nAngle) {
    _angle = nAngle;
}

double Body::vx() const {
    return _vx;
}

void Body::vx(double nVx) {
    _vx = nVx;
}

double Body::vy() const {
    return _vy;
}

void Body::vy(double nVy) {
    _vy = nVy;
}

double Body::vangle() const {
    return _vangle;
}

void Body::vangle(double nVangle) {
    _vangle = nVangle;
}

double Body::r() const {
    return _r;
}

void Body::r(double nR) {
    _r = nR;
}

double Body::b() const {
    return _b;
}

void Body::b(double nB) {
    _b = nB;
}

double Body::g() const {
    return _g;
}

void Body::g(double nG) {
    _g = nG;
}

World &Body::world() const {
    return *_world;
}

double Body::size() const {
    return _size;
}

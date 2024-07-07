#pragma once

#include <cmath>

constexpr auto PI = M_PI;

class Body {
public:
    virtual ~Body() {}
    Body(double x = 0,
         double y = 0,
         double angle = 0,
         double vx = 0,
         double vy = 0,
         double vangle = 0);

    Body(const Body &) = default;
    Body(Body &&) = delete;
    Body &operator=(const Body &) = default;
    Body &operator=(Body &&) = delete;

    virtual void update(double dt);
    virtual void draw() const {};
    virtual void kill();
    virtual bool inside(double x, double y) const;

    virtual void hit(double d);

    void setDuration(double d);
    void setHitPoints(double hp);

    void setColor(double r, double g, double b) {
        this->_r = r;
        this->_g = g;
        this->_b = b;
    }

    void size(double size) {
        _size = size;
    }

    double size() const;

    double x() const;
    void x(double newX);

    double y() const;
    void y(double newY);

    double angle() const;
    void angle(double newAngle);

    double vx() const;

    void vx(double newVx);

    double vy() const;
    void vy(double newVy);

    double vangle() const;
    void vangle(double newVangle);

    double r() const;
    void r(double newR);

    double b() const;
    void b(double newB);

    double g() const;
    void g(double newG);

protected:
    // Position and angle
    // units is in ship lengths, angle is in radians
    double _x;
    double _y;
    double _angle;
    // Velocity
    double _vx;
    double _vy;
    double _vangle;
    // Size
    double _size;
    // Color
    double _r, _b, _g;

    // duration = the time before the object by itself calls kill()
    // if set to -1 the duration is infinite
    double duration;
    // the vitalaty of the object
    // if less than zero the kill() function is to be called
    double hitPoints;
};

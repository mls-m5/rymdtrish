#ifndef _asteroid_h_
#define _asteroid_h_

#include "body.h"

class Asteroid : public Body {
public:
    Asteroid()
        : Body() {
        size = 2;
    }
    Asteroid(double x, double y, double angle)
        : Body(x, y, angle) {
        size = 2;
    }
    Asteroid(
        double x, double y, double angle, double vx, double vy, double vangle)
        : Body(x, y, angle, vx, vy, vangle) {
        size = 2;
    }
    void draw() const;
    void kill();
};

#endif

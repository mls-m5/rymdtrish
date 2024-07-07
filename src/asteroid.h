#pragma once

#include "body.h"

class Asteroid : public Body {
public:
    Asteroid(
        double x, double y, double angle, double vx, double vy, double vangle)
        : Body{x, y, angle, vx, vy, vangle} {
        size(2);
    }
    void draw() const override;
    void kill() override;
};

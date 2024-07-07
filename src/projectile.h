#ifndef _projectile_h_
#define _projectile_h_

#include "body.h"

class Projectile : public Body {
public:
    Projectile(double x = 0,
               double y = 0,
               double angle = 0,
               double vx = 0,
               double vy = 0,
               double vangle = 0)
        : Body(x, y, angle, vx, vy, vangle) {}
    void draw() const override;
    void update(double dt) override;

    // Make sure the projectile do not hit itself
    bool inside(double x, double y) const override {
        return 0;
    };

    void setOwner(Body *b) {
        owner = b;
    };

private:
    // To make sure the projectile do not hit its origin body
    Body *owner = nullptr;
};

#endif

#ifndef _projectile_h_
#define _projectile_h_

#include "body.h"

class Projectile : public Body {
public:
    Projectile()
        : Body() {}
    Projectile(double x, double y, double angle)
        : Body(x, y, angle) {}
    Projectile(
        double x, double y, double angle, double vx, double vy, double vangle)
        : Body(x, y, angle, vx, vy, vangle) {}
    void draw() const;
    void update(double dt);
    // Make sure the projectile dont hit itself
    bool inside(double x, double y) const {
        return 0;
    };

    void setOwner(Body *b) {
        owner = b;
    };

private:
    // To make sure the projectile do not hit its origin body
    Body *owner;
};

#endif

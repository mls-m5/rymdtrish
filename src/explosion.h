#ifndef _explosion_h_
#define _explosion_h_

#include "body.h"

class Explosion : public Body {
public:
    Explosion(double x,
              double y,
              double size,
              double r = 1,
              double g = 1,
              double b = 1);

    void update(double dt);
    void draw() const;

    bool inside(double x, double y) const {
        return 0;
    };
};

#endif //_explosion_h_

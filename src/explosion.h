#pragma once

#include "body.h"

class Explosion : public Body {
public:
    Explosion(World &world,
              double x,
              double y,
              double size,
              double r = 1,
              double g = 1,
              double b = 1);

    void update(double dt) override;
    void draw() const override;

    bool inside(double x, double y) const override {
        return 0;
    };
};

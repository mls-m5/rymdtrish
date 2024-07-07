#pragma once

#include "body.h"

class Spark : public Body {
private:
public:
    Spark(World &world, double x, double y, double vx, double vy);
    void update(double dt) override;
    void draw() const override;
};

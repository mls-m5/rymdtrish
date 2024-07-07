#pragma once

#include "body.h"

class Ship : public Body {
private:
public:
    Ship(double x,
         double y,
         double angle = 0,
         double vx = 0,
         double vy = 0,
         double vangle = 0) {
        Body(x, y, angle, vx, vy, vangle);
    };
    void update(double dt) override;
    void draw() const override;
    void kill() override;

    void accelerate(double ax, double ay);
    void fire(int i);
    void setPlayer(bool player = 1);
    void AI(double dt);

private:
    bool isPlayer = false;
};

#pragma once

#include "body.h"
#include <memory>

class Controller {
public:
    virtual void update(double t) = 0;
    virtual void postUpdate() {}

    Controller() = default;
    Controller(const Controller &) = delete;
    Controller(Controller &&) = delete;
    Controller &operator=(const Controller &) = delete;
    Controller &operator=(Controller &&) = delete;
    virtual ~Controller() = default;
};

class Ship : public Body {
private:
public:
    Ship(double x,
         double y,
         double angle = 0,
         double vx = 0,
         double vy = 0,
         double vangle = 0)
        : Body(x, y, angle, vx, vy, vangle){};
    void update(double dt) override;
    void draw() const override;
    void kill() override;

    void accelerate(double ax, double ay);
    void angleimpulse(double va);
    void fire(int i);

    void setController(std::unique_ptr<Controller> controller);

    template <typename T, typename... Args>
    void createController(Args &&...args) {
        setController(std::make_unique<T>(*this, std::forward<Args>(args)...));
    }

private:
    bool isPlayer = false;

    std::unique_ptr<Controller> _controller;
};

class Player : public Controller {
public:
    Player(Ship &ship)
        : _ship{&ship} {}

    Ship *_ship = nullptr;

    void update(double t) override;
    void postUpdate() override;
};

class AI : public Controller {
public:
    AI(Ship &ship)
        : _ship{&ship} {}

    Ship *_ship = nullptr;

    void update(double t) override;
};

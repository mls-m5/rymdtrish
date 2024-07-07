#pragma once

#include "body.h"
#include <list>
#include <memory>
#include <utility>

using std::list;

class World {
public:
    void init();
    void terminate();
    void update(double dt);
    void draw();

    template <typename T, typename... Args>
    T *create(Args &&...args) {
        return static_cast<T *>(
            add(std::make_unique<T>(*this, std::forward<Args>(args)...)));
    }

    void remove(Body *);

    Body *inside(double x, double y, Body *ignore = 0);

    void setPlayerInfo(double x, double y, double vx = 0, double vy = 0);

private:
    Body *add(std::unique_ptr<Body>);
    list<Body *> objects; // TODO: Convert to uniqueptr
    list<Body *>::iterator currentObject;
    bool removeCurrentObject;

public:
    double playerX, playerY, playerVX, playerVY;
};

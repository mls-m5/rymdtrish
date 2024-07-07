#pragma once

#include "body.h"
#include <list>
#include <memory>
#include <utility>

using std::list;

class World {
public:
    static void init();
    static void terminate();
    static void update(double dt);
    static void draw();

    template <typename T, typename... Args>
    static T *create(Args &&...args) {
        return static_cast<T *>(
            add(std::make_unique<T>(std::forward<Args>(args)...)));
    }

    static void remove(Body *);

    static Body *inside(double x, double y, Body *ignore = 0);

    static void setPlayerInfo(double x, double y, double vx = 0, double vy = 0);

private:
    static Body *add(std::unique_ptr<Body>);
    static list<Body *> objects;
    static list<Body *>::iterator currentObject;
    static bool removeCurrentObject;

public:
    static double playerX, playerY, playerVX, playerVY;
};

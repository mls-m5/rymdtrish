#include "asteroid.h"
#include "draw.h"
#include "explosion.h"
#include "spark.h"
#include "world.h"
#include <cmath>

void Asteroid::draw() const {
    Draw::drawAsteroid({x, y, angle, r, g, b, size});
}

void Asteroid::kill() {
    // Calculations to set speed of new objects
    // And to verify that there will be any new asteroids
    const double minSize = .3;
    const double killScale = 1 / 1.5;

    if (size * killScale < minSize) {
        World::add(new Explosion(x, y, .3));
    }
    else {
        auto sx = (rand() % 100) / 50. - 1.;
        auto sy = (rand() % 100) / 50. - 1.;
        Asteroid *a1, *a2;
        a1 = new Asteroid(x, y, angle, sx, sy, vangle);
        a1->setSize(size * killScale);
        a2 = new Asteroid(x, y, angle, -sx, -sy, -vangle);
        a2->setSize(size * killScale);
        World::add(a1);
        World::add(a2);
    }

    for (int i = 0; i < 100; i++) {
        float a = (rand() % 10000) / 10000. * pi * 2.;
        float amp = pow((rand() % 10000) / 1000. - 5., 1.2);
        auto sx = sin(a) * amp;
        auto sy = cos(a) * amp;

        auto s = new Spark(x, y, sx, sy);
        s->setDuration(1 + (rand() % 100) / 100.);
        World::add(s);
    }

    this->Body::kill();
}

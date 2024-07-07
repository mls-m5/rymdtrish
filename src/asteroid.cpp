#include "asteroid.h"
#include "draw.h"
#include "explosion.h"
#include "spark.h"
#include "world.h"
#include <cmath>

void Asteroid::draw() const {
    Draw::drawAsteroid({_x, _y, _angle, _r, _g, _b, _size});
}

void Asteroid::kill() {
    // Calculations to set speed of new objects
    // And to verify that there will be any new asteroids
    const double minSize = .3;
    const double killScale = 1 / 1.5;

    if (_size * killScale < minSize) {
        world().create<Explosion>(_x, _y, .3);
    }
    else {
        auto sx = (rand() % 100) / 50. - 1.;
        auto sy = (rand() % 100) / 50. - 1.;
        // Asteroid *a1, *a2;
        auto a1 = world().create<Asteroid>(_x, _y, _angle, sx, sy, _vangle);
        a1->size(_size * killScale);
        auto a2 = world().create<Asteroid>(_x, _y, _angle, -sx, -sy, -_vangle);
        a2->size(_size * killScale);
    }

    for (int i = 0; i < 100; i++) {
        float a = (rand() % 10000) / 10000. * pi * 2.;
        float amp = pow((rand() % 10000) / 1000. - 5., 1.2);
        auto sx = sin(a) * amp;
        auto sy = cos(a) * amp;

        auto s = world().create<Spark>(_x, _y, sx, sy);
        s->setDuration(1 + (rand() % 100) / 100.);
    }

    this->Body::kill();
}

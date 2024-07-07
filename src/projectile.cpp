#include "projectile.h"
#include "draw.h"
#include "explosion.h"
#include "world.h"

void Projectile::draw() const {
    Draw::drawProjectile({_x, _y, _angle});
}

void Projectile::update(double dt) {
    this->Body::update(dt);

    auto collision = World::inside(x(), y(), owner);
    if (collision) {
        collision->hit(10);
        kill();

        World::create<Explosion>(_x, _y, .3, .5, .5, 1);
    }
}

//
// Created by dex on 6/8/23.
//

#include "fire.h"

Fire::Fire() {
    _type = Projectile::FFIRE;
}

void Fire::move() {
    if (_ttl < 30) {
        _moveable = false;
    }
    auto direction = (float) (((double) (_direction % 360) / 180.0f) * M_PI);
    float speed = (float) _speed / 100.0f;
    _position.x += (sin(direction) * speed);
    _position.y += (cos(direction) * speed);
}

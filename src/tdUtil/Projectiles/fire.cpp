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
    Projectile::move();
}

//
// Created by dex on 6/8/23.
//

#include "fire.h"
#include "../../gamebase.h"

Fire::Fire() {
    _type = ProjectileType::FFIRE;
}

void Fire::move() {
    if (_ttl < 30) {
        _moveable = false;
    }
    Projectile::move();
}

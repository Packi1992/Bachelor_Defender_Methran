//
// Created by dex on 6/10/23.
//

#include "boomerang.h"

Boomerang::Boomerang() {
    _type=ProjectileType::BOOMERANG;
}

void Boomerang::move() {
    Projectile::move();
}

//
// Created by dex on 6/8/23.
//

#include "arrow.h"

Arrow::Arrow() {
    _type=ProjectileType::ARROW;
}

void Arrow::move() {
    Projectile::move();
}

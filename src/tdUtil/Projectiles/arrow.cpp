//
// Created by dex on 6/8/23.
//

#include "arrow.h"

Arrow::Arrow() {
    _type=Projectile::ARROW;
}

void Arrow::move() {
    Projectile::move();
}

//
// Created by dex on 6/8/23.
//

#include "link.h"

LinkProjectile::LinkProjectile() {
    _type=ProjectileType::LINK;
}

void LinkProjectile::move(float deltaT) {
    Projectile::move(deltaT);
}

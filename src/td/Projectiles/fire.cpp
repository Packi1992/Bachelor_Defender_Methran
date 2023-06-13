//
// Created by dex on 6/8/23.
//

#include "fire.h"
#include "../../gamebase.h"

Fire::Fire() {
    _type = ProjectileType::FFIRE;
}

void Fire::move(float deltaT) {
    if (_ttl < 30) {
        _moveable = false;
    }
    Projectile::move(deltaT);
}

void Fire::collide(float deltaT) {
    float x = (float)(CT::getPosOnScreen(_position).x) / float(windowSize.x);

    Projectile::collide(deltaT);

}

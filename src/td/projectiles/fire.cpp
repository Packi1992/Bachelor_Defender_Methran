//
// Created by dex on 6/8/23.
//

#include "fire.h"
#include "../../util/gamebase.h"

Fire::Fire() {
    _type = ProjectileType::FFIRE;
}

void Fire::Update() {
    if (_ttl < 30) {
        _moveable = false;
    }
    Projectile::Update();
}

void Fire::collide() {
    //float x = (float)(CT::getPosOnScreen(_position).x) / float(windowSize.x);

    Projectile::collide();

}

Fire::Fire(Fire &p, std::shared_ptr<Enemy> e, uint16_t direction) : Projectile(p, e, direction) {

}

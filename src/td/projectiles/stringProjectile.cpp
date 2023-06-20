//
// Created by dex on 6/19/23.
//

#include "stringProjectile.h"

StringProjectile::StringProjectile() {
    _type = ProjectileType::STRINGPROJECTILE;
    _direction = 0;
}

StringProjectile::StringProjectile(StringProjectile &p) : Projectile(p, nullptr, 0) {

}

void StringProjectile::Update() {
    _diff = (int) (totalMscg - _lastTimePoint);
    for (auto &entry: hitList) {
        entry.hitCooldown -= _diff;
    }
    hitList.erase(
            std::remove_if(
                    hitList.begin(),
                    hitList.end(),
                    [](HitTimer mov) { return mov.hitCooldown <= 0; }
            ),
            hitList.end());
    if (_diff < 0)_diff = 0;
    _lastTimePoint = totalMscg;
    // need to fix travel speed with render time

    if (_ttl != 0) {
        _ttl -= (int) _diff;
        if (_ttl <= 0) {
            _alive = false;
        } else {
            if (((_ttl / 10) % 100) < _tick) {
                _direction+=4;
                _tick--;
            }
        }
    }
}

void StringProjectile::collide() {
    float x = (float) (CT::getPosOnScreen(_position).x) / float(windowSize.x);
    audioHandler->playSound(SoundArrowHit, x);
}

bool StringProjectile::collision(std::shared_ptr<Enemy> e) {
    bool inList = false;
    for (auto &entry: hitList) {
        if (entry.enemy == e) {
            inList = true;
            break;
        }
    }
    if (!inList && Projectile::collision(e)) {
        hitList.push_back({e, 50});
        return true;
    }
    return false;
}


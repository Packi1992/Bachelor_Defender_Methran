//
// Created by dex on 6/8/23.
//

#include "link.h"
#include "../enemy/enemy.h"

LinkProjectile::LinkProjectile() {
    _type = ProjectileType::LINK;
    _speed = 0;
    _alive = true;
    _ttl = 200;
    _lastSoundTimePoint = totalMSec;
}

void LinkProjectile::set(u16 timeToLife, FPoint position, FPoint position2, u8 damage) {
    _ttl = timeToLife;
    _position = position;
    _position2 = position2;
    _damage = damage;
}

void LinkProjectile::Update() {
    Projectile::Update();
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
}

void LinkProjectile::Render() {
    Point p1 = CT::getPosOnScreen(_position);
    Point p2 = CT::getPosOnScreen(_position2);
    rh->line(p1, p2, GREEN);
}

bool LinkProjectile::collision(std::shared_ptr<Enemy> e) {
    bool inList = false;
    for (auto &entry: hitList) {
        if (entry.enemy == e) {
            inList = true;
            break;
        }
    }
    if (!inList && CT::collisionLineRect(_position, _position2, e->getHitBox())) {
        e->takeDamage(this);
        hitList.push_back({e, 100});
        return true;
    }
    return false;
}

LinkProjectile::LinkProjectile(LinkProjectile &p) : Projectile(p) {
    _position2 = p._position2;
}

void LinkProjectile::collide() {
    if (totalMSec - _lastSoundTimePoint > 1000) {
        float x = (float)(CT::getPosOnScreen(_position).x) / float(windowSize.x);
        audioHandler->playSound(SoundLinkHit, x);
        _lastSoundTimePoint = totalMSec;
    }
}

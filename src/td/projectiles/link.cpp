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
}

void LinkProjectile::set(u16 timeToLife, FPoint position, FPoint position2, u8 damage) {
    _ttl = timeToLife;
    _position = position;
    _position2 = position2;
    _damage = damage;
}

void LinkProjectile::Update() {
    Projectile::Update();
}

void LinkProjectile::Render() {
    Point p1 = CT::getPosOnScreen(_position);
    Point p2 = CT::getPosOnScreen(_position2);
    rh->line(p1, p2, GREEN);
}

bool LinkProjectile::collision(std::shared_ptr<Enemy> e) {
    if (CT::collisionLineRect(_position, _position2, e->getHitBox())) {
        e->takeDamage(this);
    }
    return true;
}

LinkProjectile::LinkProjectile(LinkProjectile &p) : Projectile(p) {
    _position2 = p._position2;
}

void LinkProjectile::collide() {
}

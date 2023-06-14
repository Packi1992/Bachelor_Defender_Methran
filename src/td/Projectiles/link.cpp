//
// Created by dex on 6/8/23.
//

#include "link.h"

LinkProjectile::LinkProjectile() {
    _type=ProjectileType::LINK;
    _speed = 0;
    _alive = true;
    _ttl = 1000;
}
void LinkProjectile::set(float length, u16 timeToLife, FPoint position, FPoint position2, u16 direction){
    _length = length;
    _ttl = timeToLife;
    _position = position;
    _direction = direction;
    _position2 = position2;

}

void LinkProjectile::move() {
    Projectile::move();
}

void LinkProjectile::Render() {
    Point p1 = CT::getPosOnScreen(_position);
    Point p2 = CT::getPosOnScreen(_position2);
    rh->line(p1,p2,GREEN);
}

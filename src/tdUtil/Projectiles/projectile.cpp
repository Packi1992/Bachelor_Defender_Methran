//
// Created by dex on 6/8/23.
//

#include "projectile.h"

void Projectile::move() {
    auto direction = (float)(((double)(_direction % 360) / 180.0f) * M_PI);
    float speed = (float)(((float)_speed) *0.01f);

    float xdiff = (sin(direction) * speed);
    float ydiff = (cos(direction) * speed);
    _position.x += (sin(direction) * speed);
    _position.y -= (cos(direction) * speed);
}

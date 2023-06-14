//
// Created by dex on 6/8/23.
//

#include "projectile.h"
#include "../../gamebase.h"

void Projectile::move() {
    _hitCooldown -= deltaTg;
    auto direction = (float)(((double)(_direction % 360) / 180.0f) * M_PI);
    auto speed = (float)(((float)_speed) *0.01f);
    _position.x += (sin(direction) * speed);
    _position.y -= (cos(direction) * speed);
}

bool Projectile::onScreen() const {
    Point posOnScreen = CT::getPosOnScreen(_position);
    return (posOnScreen.x + _size > 0) &&      // left
           (posOnScreen.y + _size > 0) &&             // top
           (posOnScreen.y < windowSize.y) &&        // bot
           (posOnScreen.x < windowSize.x);         // right
}

void Projectile::Render() {
    if (_alive && onScreen()) {
        Point pos = CT::getPosOnScreen(_position);

        Rect srcRect =*TdTileHandler::getProjectileSrcRect(_type, totalMscg);
        float sizeW = ((float)scale/64 * (float)_size / 100.0f)*(float)srcRect.w;
        float sizeH = ((float)scale/64 * (float)_size / 100.0f)*(float)srcRect.h;
        //dstRect needs to be changed depending on direction
        float angle = (float)_direction/180.0f*(float)M_PI;
        float sinAngle = sin(angle);
        float cosAngle = cos(angle);
        int xFix = (int)(-sizeW*0.5-sinAngle*sizeW);
        int yFix = (int)((cosAngle-1)*0.5*sizeH);
        Rect dstRect = { pos.x+xFix,pos.y+yFix, (int)sizeW, (int)sizeH };
        rh->tile(&dstRect, _direction, TdTileHandler::getProjectileSrcRect(_type, totalMscg));
        dstRect.y = pos.y;
        dstRect.x = pos.x;
        dstRect.w = 5;
        dstRect.h = 5;
        rh->fillRect(&dstRect, BLACK);
    }
}

void Projectile::collide() {
    _alive = false;
}

Projectile::~Projectile() = default;

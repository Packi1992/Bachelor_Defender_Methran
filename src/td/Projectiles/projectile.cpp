//
// Created by dex on 6/8/23.
//

#include "projectile.h"
#include "../../gamebase.h"

void Projectile::move() {
    auto direction = (float)(((double)(_direction % 360) / 180.0f) * M_PI);
    auto speed = (float)(((float)_speed) *0.01f);

    float xdiff = (sin(direction) * speed);
    float ydiff = (cos(direction) * speed);
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

void Projectile::Render(u32 totalMSec) {
    if (_alive && onScreen()) {
        Point pos = CT::getPosOnScreen(_position);
        int size = (int)((float)scale * (float)_size / 100.0f);
        Rect dstRect = { (int)pos.x, (int)(pos.y - (float)size * 0.5f), size, size };
        rh->tile(&dstRect, _direction, TdTileHandler::getProjectileSrcRect(_type, totalMSec));
        dstRect.y += size * 0.5;
        dstRect.w = 5;
        dstRect.h = 5;
        rh->fillRect(&dstRect, BLACK);
    }
}


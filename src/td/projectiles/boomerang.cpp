//
// Created by dex on 6/10/23.
//

#include "boomerang.h"

Boomerang::Boomerang() {
    _type = ProjectileType::BOOMERANG;
}

void Boomerang::Update() {
    _diff = (int)(totalMscg - _lastTimePoint);
    if(_diff < 0 )_diff = 0;
    _lastTimePoint = totalMscg;
    _direction += 3;
    auto direction = (float) (((double) (_direction % 360) / 180.0f) * M_PI);
    auto speed = (float) (((float) _speed) * 0.01f);
    _position.x += (sin(direction) * speed);
    _position.y -= (cos(direction) * speed);
    _minFlyingTime -= _diff;
    if (_minFlyingTime <= 0) {
        _toggleDirection = !_toggleDirection;
    }
    if (((int) _position.x == (int) _startingPoint.x) && ((int) _position.y == (int) _startingPoint.y) &&
        _toggleDirection) {
        _alive = false;
    }
}

void Boomerang::Render() {
    if (_alive && onScreen()) {
        Point pos = CT::getPosOnScreen(_position);

        Rect srcRect = *TdTileHandler::getProjectileSrcRect(_type, totalMscg);
        float sizeW = ((float) scale / 64 * (float) _size / 100.0f) * (float) srcRect.w;
        float sizeH = ((float) scale / 64 * (float) _size / 100.0f) * (float) srcRect.h;
        //dstRect needs to be changed depending on direction
        //float angle = (float)(totalMSec%360)/180.0f*(float)M_PI;
        float angle = (float) _direction / 180.0f * (float) M_PI;
        float sinAngle = sin(angle);
        float cosAngle = cos(angle);
        int xFix = (int) (-sizeW * 0.5 - sinAngle * sizeW);
        int yFix = (int) ((cosAngle - 1) * 0.5 * sizeH);
        Rect dstRect = {pos.x + xFix, pos.y + yFix, (int) sizeW, (int) sizeH};
        rh->tile(&dstRect, 360 - (totalMscg % 360), TdTileHandler::getProjectileSrcRect(_type, totalMscg));
        dstRect.y = pos.y;
        dstRect.x = pos.x;
        dstRect.w = 5;
        dstRect.h = 5;
        rh->fillRect(&dstRect, BLACK);
    }
}

void Boomerang::collide() {
    float x = (float) (CT::getPosOnScreen(_position).x) / float(windowSize.x);
    audioHandler->playSound(SoundArrowHit, x);
}

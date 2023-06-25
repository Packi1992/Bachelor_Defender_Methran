//
// Created by dex on 6/8/23.
//

#include "projectile.h"

#include <utility>
#include "../../util/gamebase.h"
#include "../enemy/enemy.h"

void Projectile::Update() {
    if (_alive) {
        u32 diff = totalMSec - _lastTimePoint;
        _lastTimePoint = totalMSec;
        _posOnScreen = CT::getPosOnScreen(_position);
        // need to fix travel speed with render time
        auto direction = (float) (((double) (_direction % 360) / 180.0f) * M_PI);
        auto speed = (float) (((float) _speed) * 0.01f);
        _position.x += (sin(direction) * speed);
        _position.y -= (cos(direction) * speed);
        if (_ttl != 0) {
            _ttl -= (int) diff;
            if (_ttl <= 0) {
                _alive = false;
            }
        }
    }
}

bool Projectile::onScreen() const {
    return (_posOnScreen.x + _size > 0) &&      // left
           (_posOnScreen.y + _size > 0) &&             // top
           (_posOnScreen.y < windowSize.y) &&        // bot
           (_posOnScreen.x < windowSize.x);         // right
}

void Projectile::Render() {
    if (_alive && onScreen()) {
        Point pos = CT::getPosOnScreen(_position);

        Rect srcRect = *TdTileHandler::getProjectileSrcRect(_type, totalMSec);
        float sizeW = ((float) scale / 64 * (float) _size / 100.0f) * (float) srcRect.w;
        float sizeH = ((float) scale / 64 * (float) _size / 100.0f) * (float) srcRect.h;
        //dstRect needs to be changed depending on direction
        float angle = (float) _direction / 180.0f * (float) M_PI;
        float sinAngle = sin(angle);
        float cosAngle = cos(angle);
        int xFix = (int) (-sizeW * 0.5 - sinAngle * sizeW);
        int yFix = (int) ((cosAngle - 1) * 0.5 * sizeH);
        Rect dstRect = {pos.x + xFix, pos.y + yFix, (int) sizeW, (int) sizeH};
        rh->tile(&dstRect, _direction, TdTileHandler::getProjectileSrcRect(_type, totalMSec));
        IfDebug {
            dstRect.y = pos.y;
            dstRect.x = pos.x;
            dstRect.w = 5;
            dstRect.h = 5;
            rh->fillRect(&dstRect, BLACK);
        }
    }
}

bool Projectile::collision(std::shared_ptr<Enemy> e) {
    FRect en = e->getHitBox();
    if ((_position.x >= en.x) &&
        (_position.x < (en.x + en.w)) &&
        (_position.y >= en.y) &&
        (_position.y < (en.y + en.h))) {
        e->takeDamage(this);
        collide();
        return true;
    }
    return false;
}

void Projectile::collide() {
    _alive = false;
}

Projectile::Projectile() {
    _lastTimePoint = totalMSec;
}

Projectile::Projectile(Projectile &p) {
    _alive = p._alive;
    _ttl = p._ttl;
    _destroy = p._destroy;
    _type = p._type;
    _startingPoint = p._startingPoint;
    _position = p._position;
    _hitCoolDown = p._hitCoolDown;
    _size = p._size;
    _speed = p._speed;
    _direction = p._direction;
    _damage = p._damage;
    _moveable = p._moveable;
    _hitSound = p._hitSound;
    _lastTimePoint = totalMSec;
}

Projectile::Projectile(Projectile &p, std::shared_ptr<Enemy> e, uint16_t direction) : Projectile(p) {
    _targetE = e;
    _direction = direction;
}

Projectile::~Projectile() = default;

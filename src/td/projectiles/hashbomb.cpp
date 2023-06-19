//
// Created by dex on 6/18/23.
//

#include "hashbomb.h"
#include "../testtd.h"
#include "baseExplosion.h"

Hashbomb::Hashbomb() {
    _type = ProjectileType::HASHBOMB;
    _lastTimePoint = totalMscg;
    _ttl = 1500;
    _endDirection = 0;
    _exdmg = 20;
}


void Hashbomb::Update() {
    _diff = (int) (totalMscg - _lastTimePoint);

    if (_diff < 0)_diff = 0;
    _lastTimePoint = totalMscg;
    _ttl -= _diff;

    if (_endDirection != _direction) {
        if (_upDown)
            _direction++;
        else
            _direction--;
    }

    auto direction = (float) (((double) (_direction % 360) / 180.0f) * M_PI);
    auto speed = (float) (((float) _speed) * 0.01f);
    _position.x += (sin(direction) * speed);
    _position.y -= (cos(direction) * speed);
    if (_ttl != 0) {
        _ttl -= (int) _diff;
        if (_ttl <= 0) {
            _alive = false;
            float x = (float) (CT::getPosOnScreen(_position).x) / float(windowSize.x);
            audioHandler->playSound(SoundArrowHit, x);
            addExplosion();
        }
    }
}

void Hashbomb::Render() {
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

void Hashbomb::collide() {

}

bool Hashbomb::collision(std::shared_ptr<Enemy> e) {
    return false;
}

Hashbomb::Hashbomb(Hashbomb &p, std::shared_ptr<Enemy> e, uint16_t direction) : Projectile(p, e, direction) {
    _endDirection = (_direction + 180) % 360;
    _exrange = p._exrange;
    _exdmg = p._exdmg;
    // need to get fixed
    if (_endDirection > _direction)
        _upDown = false;
}

void Hashbomb::addExplosion() {
    for (int i = (-1*_exrange); i <= _exrange; i++) {
        for (int j = (-1*_exrange); j <= _exrange; j++) {
            SDL_FPoint tmp = {_position.x + (float) i, _position.y + (float) j};
            tdGlobals->_projectiles.push_back(std::make_shared<BaseExplosion>(tmp,_exdmg));
        }
    }
}
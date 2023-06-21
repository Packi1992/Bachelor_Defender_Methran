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


    auto speed = (float) (((float) _speed) * 0.01f);

    _xDistance = abs(_position.x - _targetP.x);
    _position.x = _position.x + (_direction <= 180 ? 1.0f : -1.0f) * speed;

    if (_xDistance >= abs(_startingPoint.x - _targetP.x) / 2)
        _position.y -= 1 * speed;
    else
        _position.y += 1 * speed;


    if (_ttl != 0) {
        _ttl -= (int) _diff;
    }
    if ((_ttl <= 0) || ((_targetP.x == _position.x) && (_targetP.y == _position.y))) {
        _alive = false;
        float x = (float) (CT::getPosOnScreen(_position).x) / float(windowSize.x);
        audioHandler->playSound(SoundArrowHit, x);
        addExplosion();
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

Hashbomb::Hashbomb(Hashbomb &p, SDL_FPoint target) : Projectile(p, nullptr, 0) {
    _exrange = p._exrange;
    _exdmg = p._exdmg;
    _targetP = target;
    _startDistance = sqrt(pow(target.x, 2.0f) * pow(target.y, 2.0f));
    _distance = _startDistance;
    _direction = (uint16_t) CT::getAngle(_position, _targetP);
    _xDistance = abs(_position.x - _targetP.x);
    _startingPoint = p._position;
    // Umrechnung von Radiant in Grad

}

void Hashbomb::addExplosion() {
    for (int i = (-1 * _exrange); i <= _exrange; i++) {
        for (int j = (-1 * _exrange); j <= _exrange; j++) {
            SDL_FPoint tmp = {_position.x + (float) i, _position.y + (float) j};
            tdGlobals->_projectiles.push_back(std::make_shared<BaseExplosion>(tmp, _exdmg));
        }
    }
}
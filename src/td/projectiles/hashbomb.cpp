//
// Created by dex on 6/18/23.
//

#include "hashbomb.h"
#include "../testtd.h"
#include "baseExplosion.h"
#include "../../util/recthelper.h"

Hashbomb::Hashbomb() {
    _type = ProjectileType::HASHBOMB;
    _lastTimePoint = totalMSec;
    _ttl = 1500;
    _endDirection = 0;
    _exdmg = 20;
}


void Hashbomb::Update() {
    // handle collisions
    _diff = (int) (totalMSec - _lastTimePoint);
    _lastTimePoint = totalMSec;
    // calculate next position
    double flSpeed = _diff * _speed * 0.001;
    // gibt probleme wenn auf hauptachse losgeschossen wird :(
    //
    _position.x += (float) ((_targetVec.x + _driftVec.x) * flSpeed);
    _position.y -= (float) ((_targetVec.y + _driftVec.y) * flSpeed);
    _driftVec += (_counterDriftVec * flSpeed);
    if (!_midflight && abs(_position.x - _targetP.x) < 0.25 &&
        abs(_position.y - _targetP.y) < 0.25) {
        _targetVec *= -1;
        _counterDriftVec *= -1;
        _midflight = true;
    }
    if (!_midflight) {
        _ttl += _diff;
        if (_ttl >= 4000)
            _alive = false;
    } else {
        _alive = false;
        addExplosion();
    }
}

void Hashbomb::Render() {
    if (_alive && onScreen()) {
        Point pos = CT::getPosOnScreen(_position);
        Rect srcRect = *TdTileHandler::getProjectileSrcRect(_type, totalMSec);
        float targPy = pow(_targetVec.x, 2) + pow(_targetVec.y, 2);
        float driftPy = pow(_driftVec.x, 2) + pow(_driftVec.y, 2);
        float flyingScale = (targPy - driftPy) / targPy * 3;
        float sizeW = ((float) scale / 64 * (float) _size / 100.0f) * (float) srcRect.w * flyingScale;
        float sizeH = ((float) scale / 64 * (float) _size / 100.0f) * (float) srcRect.h * flyingScale;
        //dstRect needs to be changed depending on direction
        //float angle = (float)(totalMSec%360)/180.0f*(float)M_PI;
        float angle = (float) _direction / 180.0f * (float) M_PI;
        float sinAngle = sin(angle);
        float cosAngle = cos(angle);
        int xFix = (int) (-sizeW * 0.5 - sinAngle * sizeW);
        int yFix = (int) ((cosAngle - 1) * 0.5 * sizeH);
        Rect dstRect = {pos.x + xFix, pos.y + yFix, (int) sizeW, (int) sizeH};
        rh->tile(&dstRect, 360 - (totalMSec % 360), TdTileHandler::getProjectileSrcRect(_type, totalMSec));
        IfDebug {
            Point t = CT::getPosOnScreen(_targetP);
            dstRect.y = t.y;
            dstRect.x = t.x;
            dstRect.w = 5;
            dstRect.h = 5;
            rh->fillRect(&dstRect, BLACK);
        }
    }
}

void Hashbomb::collide() {
    float x = (float) (CT::getPosOnScreen(_position).x) / float(windowSize.x);
    audioHandler->playSound(SoundHashbombHit, x);
    audioHandler->playSound(SoundBaseExplosion, x);
}

bool Hashbomb::collision(std::shared_ptr<Enemy> e) {
    return false;
}

Hashbomb::Hashbomb(Hashbomb &p, std::shared_ptr<Enemy> e) : Projectile(p, e, 0) {
    calculateVectors();
    _exrange = p._exrange;
    _exdmg = p._exdmg;
    _ttl = 0;
}

void Hashbomb::addExplosion() {
    for (int i = (-1 * _exrange); i <= _exrange; i++) {
        for (int j = (-1 * _exrange); j <= _exrange; j++) {
            SDL_FPoint tmp = {_position.x + (float) i, _position.y + (float) j};
            tdGlobals->_projectiles.push_back(std::make_shared<BaseExplosion>(tmp, _exdmg));
            collide();
        }
    }
}

void Hashbomb::calculateVectors() {
    // boomerang is flying counter clockwise
    _targetP = _position - _targetE->_pos;
    _targetP = _targetE->_pos;
    // know your ***** Pythagoras
    double totalPathLength = (sqrt(pow(_targetP.x - _position.x, 2) + pow(_targetP.y - _position.y, 2)));
    double targetAngle = CT::getAngle(_position, _targetP) / 180.0 * M_PI;
    _targetVec = {sin(targetAngle) * totalPathLength * 0.01,
                  cos(targetAngle) * totalPathLength * 0.01};
    if (_targetVec.x > 0 && _targetVec.y > 0) {
        _driftVec = {_targetVec.y, -_targetVec.x};
        _counterDriftVec = {-(_driftVec.x) * 0.02, -(_driftVec.y) * 0.02};
    } else if (_targetVec.x > 0 && _targetVec.y < 0) { // unten rechts
        _driftVec = {_targetVec.y, -_targetVec.x};
        _counterDriftVec = {-(_driftVec.x) * 0.02, -(_driftVec.y) * 0.02};
    } else if (_targetVec.x > 0 && _targetVec.y == 0) {
        _driftVec = {0, -_targetVec.x};
        _counterDriftVec = {-(_driftVec.x) * 0.02, -(_driftVec.y) * 0.02};
    } else if (_targetVec.x <= 0 && _targetVec.y <= 0) {
        _driftVec = {_targetVec.y, -_targetVec.x};
        _counterDriftVec = {-(_driftVec.x) * 0.02, -(_driftVec.y) * 0.02};
    } else if (_targetVec.x <= 0 && _targetVec.y > 0) { // oben links
        _driftVec = {_targetVec.y, -_targetVec.x};
        _counterDriftVec = {-(_driftVec.x) * 0.02, -(_driftVec.y) * 0.02};
    }
    _driftVec.x = _driftVec.x - _counterDriftVec.x;
    _driftVec.y = _driftVec.y - _counterDriftVec.y;
    IfDebug e = _targetE->_pos;
}
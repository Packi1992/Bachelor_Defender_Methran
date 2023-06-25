//
// Created by dex on 6/10/23.
//

#include "boomerang.h"
#include "../enemy/enemy.h"
#include "../testtd.h"
#include "../../util/recthelper.h"

Boomerang::Boomerang() {
    _type = ProjectileType::BOOMERANG;
    _lastTimePoint = totalMSec;
}

void Boomerang::Update() {
    // handle collisions
    _diff = (int) (totalMSec - _lastTimePoint);
    _lastTimePoint = totalMSec;
    for (auto &entry: hitList) {
        entry.hitCooldown -= _diff;
    }
    hitList.erase(
            std::remove_if(
                    hitList.begin(),
                    hitList.end(),
                    [](HitTimer mov) { return mov.hitCooldown <= 0; }
            ),
            hitList.end());
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
        if (_ttl >= 15000)
            _alive = false;
    } else {
        if (_ttl > _diff)
            _ttl -= _diff;
        else
            _ttl = 0;
        if (_ttl <= 0) {
            _alive = false;
        }
    }
}

void Boomerang::calculateVectors() {
    // boomerang is flying counter clockwise
    _targetP = _position - _targetE->_pos;
    DPoint _stargetP = {(double) _targetP.x, (double) _targetP.y};
    float length = sqrt(_targetP.x * _targetP.x + _targetP.y * _targetP.y);
    double angle = CT::getAngle({0.0, 0.0}, _stargetP);
    angle = (((int) angle + 120) % 360);
    angle = angle / 180 * M_PI;
    _targetP.x = sin(angle) * length;
    _targetP.y = -cos(angle) * length;
    _targetP = _targetP + _targetE->_pos;
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

void Boomerang::Render() {
    if (_alive && onScreen()) {
        Point pos = CT::getPosOnScreen(_position);
        Rect srcRect = *TdTileHandler::getProjectileSrcRect(_type, totalMSec);
        float sizeW = ((float) scale / 64 * (float) _size / 100.0f) * (float) srcRect.w;
        float sizeH = ((float) scale / 64 * (float) _size / 100.0f) * (float) srcRect.h;
        Rect dstRect = {(int) (pos.x - (float) sizeW * 0.5f), (int) (pos.y - (float) sizeH * 0.5f), (int) sizeW,
                        (int) sizeH};
        rh->tile(&dstRect, 360 - (totalMSec % 360), TdTileHandler::getProjectileSrcRect(_type, totalMSec));
        IfDebug {
            dstRect.y = pos.y;
            dstRect.x = pos.x;
            dstRect.w = 5;
            dstRect.h = 5;
            rh->fillRect(&dstRect, BLACK);
            Point targetOnScreen = CT::getPosOnScreen(_targetP);
            Rect target = {targetOnScreen.x - 5, targetOnScreen.y - 5, 10, 10};
            rh->fillRect(&target, RED);
            Point targetVecP = {(int) ((float) pos.x + _targetVec.x * 100 * (float) scale),
                                (int) ((float) pos.y - _targetVec.y * 100 * (float) scale)};
            rh->line(pos, targetVecP, RED);
            Point driftVecP = {(int) ((float) pos.x + _driftVec.x * 100 * (float) scale),
                               (int) ((float) pos.y - _driftVec.y * 100 * (float) scale)};
            rh->line(pos, driftVecP, BLUE);
            Point cdriftVecP = {(int) ((float) pos.x + _counterDriftVec.x * 500 * (float) scale),
                                (int) ((float) pos.y - _counterDriftVec.y * 500 * (float) scale)};
            rh->line(pos, cdriftVecP, GREEN);
            Point es = CT::getPosOnScreen(e);
            Rect target2{es.x - 5, es.y - 5, 10, 10};
            rh->fillRect(&target2, GREEN);
        }
    }
}

void Boomerang::collide() {
    float x = (float)(CT::getPosOnScreen(_position).x) / float(windowSize.x);
    audioHandler->playSound(SoundBoomerangHit, x);
}

bool Boomerang::collision(std::shared_ptr<Enemy> e) {
    bool inList = false;
    for (auto &entry: hitList) {
        if (entry.enemy == e) {
            inList = true;
            break;
        }
    }
    if (!inList && Projectile::collision(e)) {
        if (e->isCopyable()) {
            std::shared_ptr<Enemy> e1 = std::make_shared<Enemy>(e->_pos, 30, 70, 0, e->_type, 0.5f, false);
            std::shared_ptr<Enemy> e2 = std::make_shared<Enemy>(e->_pos, 30, 70, 0, e->_type, 0.5f, false);
            tdGlobals->_enemies.push_back(e1);
            tdGlobals->_enemies.push_back(e2);
            hitList.push_back({e1, 500});
            hitList.push_back({e2, 500});
        }
        if (e->isStunable()) {
            e->stun(_stunduration);
        }
        hitList.push_back({e, 500});
        return true;
    }
    return false;
}

Boomerang::Boomerang(Boomerang &p, std::shared_ptr<Enemy> e, uint16_t direction) : Projectile(p, e, direction) {
    _stunduration = p._stunduration;
    calculateVectors();
    _ttl = 0;
}

void Boomerang::calcNextPos() {
    float _angle = 1.0f;
    FPoint oq = {_rotatePoint.x - _position.x, _rotatePoint.y - _position.y};
    FPoint oq_ = {(cos(_angle) * oq.x + (-sin(_angle)) * oq.x), (sin(_angle) * oq.y + cos(_angle) * oq.y)};
    _position = oq_ + _rotatePoint;
}



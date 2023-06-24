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
    float flSpeed = (float) _diff * (float) _speed * 0.00001f;
    _position.x += (_targetVec.x + _driftVec.x) * flSpeed;
    _position.y -= (_targetVec.y + _driftVec.y) * flSpeed;
    _driftVec += _counterDriftVec * flSpeed;
    if (!_midflight && (int) (_position.x * 10) == (int) (_targetP.x * 10) &&
        (int) (_position.y * 10) == (int) (_targetP.y * 10)) {
        _targetVec *= -1;
        _counterDriftVec *= -1;
        _midflight = true;
    }
    if (!_midflight) {
        _ttl += _diff;
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
    _targetP *= -1;
    _targetP = _targetP + _targetE->_pos;
    float totalPathLength = (float) (sqrt(pow(_targetP.x + _position.x, 2) + pow(_targetP.y + _position.y, 2)));
    float targetAngle = CT::getAngle(_position, _targetP) / 180.0f * (float) M_PI;
    _targetVec = {(float) sin(targetAngle) * totalPathLength * 0.01f,
                  (float) cos(targetAngle) * totalPathLength * 0.01f};
    if(_targetVec.x > 0){
        _driftVec.x
    }
    _driftVec = {_targetVec.y, _targetVec.x};
    _counterDriftVec = {(-_driftVec.x) * 0.01f, (-_driftVec.y) * 0.01f};
}

void Boomerang::Render() {
    if (_alive && onScreen()) {
        Point pos = CT::getPosOnScreen(_position);
        cout << "pos:" << pos.x << ", " << pos.y << "| position:" << _position.x << ", " << _position.y << endl;
        Rect srcRect = *TdTileHandler::getProjectileSrcRect(_type, totalMSec);
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
        rh->tile(&dstRect, 360 - (totalMSec % 360), TdTileHandler::getProjectileSrcRect(_type, totalMSec));
        dstRect.y = pos.y;
        dstRect.x = pos.x;
        dstRect.w = 5;
        dstRect.h = 5;
        rh->fillRect(&dstRect, BLACK);
        Point targetOnScreen = CT::getPosOnScreen(_targetP);
        Rect target = {targetOnScreen.x, targetOnScreen.y, 64, 64};
        rh->fillRect(&target, RED);
    }
}

void Boomerang::collide() {
    float x = (float) (CT::getPosOnScreen(_position).x) / float(windowSize.x);
    audioHandler->playSound(SoundArrowHit, x);
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
    _minFlyingTime = p._minFlyingTime;
    _flyingTime = p._minFlyingTime;
    _toggleDirection = p._toggleDirection;
    _stunduration = p._stunduration;
    calculateVectors();
    _ttl = 0;
}

void Boomerang::calcNextPos() {
    float _angle = 1.0f;
    FPoint oq = {_rotatePoint.x - _position.x, _rotatePoint.y - _position.y};
    FPoint oq_ = {(cos(_angle) * oq.x + (-sin(_angle)) * oq.x), (sin(_angle) * oq.y + cos(_angle) * oq.y)};
    _position = oq_ + _rotatePoint;
    cout << _position.x << " " << _position.y << endl;
}



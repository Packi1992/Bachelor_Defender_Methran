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
    if (_diff < 0)_diff = 0;
    _lastTimePoint = totalMSec;
    if (_toggleDirection) {
        calcNextPos();
    }else {
        auto direction = (float) (((double) (_direction % 360) / 180.0f) * M_PI);
        auto speed = (float) (((float) _speed) * 0.01f);
        _position.x += (sin(direction) * speed);
        _position.y -= (cos(direction) * speed);
    }

    _flyingTime -= _diff;
    if (_flyingTime <= _minFlyingTime / 2 && !_midflight) {
        _midflight = true;
        _rotatePoint = _position;
    }
    if (_flyingTime <= 0 && _toggleDirection == false) {
        _endFlyPos = _position;
        _toggleDirection = true;
        //_travellength = sqrt(_endFlyPos.x * _endFlyPos.x + _endFlyPos.y * _endFlyPos.y);
    }
    if (((int) _position.x == (int) _startingPoint.x) && ((int) _position.y == (int) _startingPoint.y) &&
        _toggleDirection) {
        _alive = false;
    }
    if (_ttl != 0) {
        _ttl -= (int) _diff;
        if (_ttl <= 0) {
            _alive = false;
        }
    }
}

void Boomerang::Render() {
    if (_alive && onScreen()) {
        Point pos = CT::getPosOnScreen(_position);

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
    }
}

void Boomerang::collide() {
    float x = (float) (CT::getPosOnScreen(_position).x) / float(windowSize.x);
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
    _minFlyingTime = p._minFlyingTime;
    _flyingTime = p._minFlyingTime;
    _toggleDirection = p._toggleDirection;
    _stunduration = p._stunduration;
}

void Boomerang::calcNextPos() {
    float _angle = 1.0f;
    FPoint oq = {_rotatePoint.x - _position.x, _rotatePoint.y - _position.y};
    FPoint oq_ = {(cos(_angle) * oq.x + (-sin(_angle)) * oq.x), (sin(_angle) * oq.y + cos(_angle) * oq.y)};
    _position = oq_ + _rotatePoint;
    cout << _position.x << " " << _position.y << endl;
}

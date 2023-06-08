//
// Created by banoodle on 17.05.23.
//

#include "enemy.h"

void Enemy::Update(const float deltaT ) {
    if (_stunTime > 0) {
        _stunTime > deltaT ? _stunTime -= deltaT : _stunTime = 0;
    } else {
        // move ...
        updateDir();
        if (_pos.x == _nextPos.x && _pos.y == _nextPos.y) {
            // updated Target if reached
            if(pMap->getObject(_pos) == MapObjects::Goal)
            {
                _alive = false;
            }
            _nextPos = pMap->getNextPosCentre(_pos);
        } else {
            // actually move
            float runLength = deltaT* (float)_speed/30.0f;
            if (_slowTimer > 0) {
                _slowTimer -= deltaT;
                runLength = (float) ((double) runLength * (_speedDiff / 10.0));
            }
            if (_dir == 0)
                _pos.y = (_pos.y + runLength) - _nextPos.y > 0 ? _pos.y -= runLength : _pos.y = _nextPos.y;
            if (_dir == 90)
                _pos.x = _nextPos.x - (_pos.x + runLength) > 0 ? _pos.x += runLength : _pos.x = _nextPos.x;
            if (_dir == 180)
                _pos.y = _nextPos.y - (_pos.y + runLength) > 0 ? _pos.y += runLength : _pos.y = _nextPos.y;
            if (_dir == 270)
                _pos.x = (_pos.x + runLength) - _nextPos.x > 0 ? _pos.x += runLength : _pos.x = _nextPos.x;
        }
    }
}

void Enemy::takeDamage(uint16_t damage) {
    _health < damage ? _health = 0 : _health -= damage;
    if (_health == 0) {
        startDeathAnimation();
        _alive = false;
    }
}

void Enemy::stun(uint16_t time) {
    _stunTime = time;
}

void Enemy::setEnemy(Point pos, uint16_t health, uint8_t speed, EnemyType type) {
    _pos.x = (float) pos.x + 0.5f;
    _pos.y = (float) pos.y + 0.5f;
    _nextPos = pMap->getNextPosCentre(_pos);
    updateDir();
    _health = health;
    _maxHealth = health;
    _speed = speed;
    _type = type;
    _alive = true;
}

void Enemy::startDeathAnimation() {
    _dying = 1000;
}

void Enemy::setSpeed(uint8_t speed) {
    _speed = speed;
}

void Enemy::setSlow(uint8_t speedDiff, uint16_t time) {
    _speedDiff = speedDiff;
    _slowTimer = time;
}

bool Enemy::isStunned() const {
    return _stunTime > 0;
}

bool Enemy::isPoisend() const {
    return _poisonTimer > 0;
}

bool Enemy::isSlowed() const {
    return _slowTimer > 0;
}

void Enemy::updateDir() {
    if (_nextPos == _pos)
        return;
    if (_nextPos.x == _pos.x) { // up or down
        if (_nextPos.y > _pos.y)
            _dir = 180;
        else
            _dir = 0;
    } else if (_nextPos.y == _pos.y) {// left or right
        if (_nextPos.x > _pos.x)
            _dir = 90;
        else
            _dir = 270;
    }

}

bool Enemy::isPointInside(const FPoint &p) const {
    FRect en = { _pos.x-0.5f, _pos.y-1.6f, 0.9f, 1.8f };
    return ( (p.x >= en.x) && (p.x < (en.x + en.w)) &&
             (p.y >= en.y) && (p.y < (en.y + en.h)) ) ? SDL_TRUE : SDL_FALSE;
}
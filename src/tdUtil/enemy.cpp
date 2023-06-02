//
// Created by banoodle on 17.05.23.
//

#include "enemy.h"

void Enemy::Update() {
    if (_stunTime > 0) {
        _stunTime > pMap->getMapTimeDiff() ? _stunTime -= pMap->getMapTimeDiff() : _stunTime = 0;
    } else {
        // move ...
        updateDir();
        FPoint target = Map::getPreciseCenterOfPos(_nextPos);// getTargetPos
        if (_pos.x == target.x && _pos.y == target.y) {
            // updated Target if reached
            if(pMap->getObject(_pos) == MapObjects::Goal)
            {
                cout << "goal reached yesssss"<< endl;
                _alive = false;
            }
            _nextPos = pMap->getNextPos(_nextPos);
            //cout << "my next target is: {"<<_nextPos.x << ", "<< _nextPos.y << "}" << endl;
        } else {
            // actually move
            float runLength = (float) pMap->getMapTimeDiff() * 100 * (float) _speed;
            if (runLength == 0)
                runLength = 0.05;
            if (_slowTimer > 0) {
                _slowTimer -= pMap->getMapTimeDiff();
                runLength = (float) ((double) runLength * (_speedDiff / 10.0));
            }
            if (_dir == 0)
                _pos.y = (_pos.y + runLength) - target.y > 0 ? _pos.y -= runLength : _pos.y = target.y;
            if (_dir == 90)
                _pos.x = target.x - (_pos.x + runLength) > 0 ? _pos.x += runLength : _pos.x = target.x;
            if (_dir == 180)
                _pos.y = target.y - (_pos.y + runLength) > 0 ? _pos.y += runLength : _pos.y = target.y;
            if (_dir == 270)
                _pos.x = (_pos.x + runLength) - target.x > 0 ? _pos.x += runLength : _pos.x = target.x;
        }
    }
}

bool Enemy::takeDamage(uint16_t damage) {
    _health < damage ? _health = 0 : _health -= damage;
    if (_health == 0) {
        startDeathAnimation();
        return false;
    }
    return true;

}

void Enemy::stun(uint16_t time) {
    _stunTime = time;
}

void Enemy::setEnemy(Point pos, uint16_t health, uint8_t speed, EnemyType type) {
    _pos.x = (float) pos.x + 0.5f;
    _pos.y = (float) pos.y + 0.5f;
    _nextPos = pMap->getNextPos(_pos);
    //cout << "my next target is: {"<<_nextPos.x << ", "<< _nextPos.y << "}" << endl;
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
    return _poisenTimer > 0;
}

bool Enemy::isSlowed() const {
    return _slowTimer > 0;
}

void Enemy::updateDir() {
    FPoint target = Map::getPreciseCenterOfPos(_nextPos);
    if (target == _pos)
        return;
    if (target.x == _pos.x) { // up or down
        if (target.y > _pos.y)
            _dir = 180;
        else
            _dir = 0;
    } else if (target.y == _pos.y) {// left or right
        if (target.x > _pos.x)
            _dir = 90;
        else
            _dir = 270;
    }

}





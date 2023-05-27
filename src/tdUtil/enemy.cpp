//
// Created by banoodle on 17.05.23.
//

#include "enemy.h"

void Enemy::Update() {
    if (_stunTime != 0) {
        _stunTime > pMap->getMapTimeDiff() ? _stunTime -= pMap->getMapTimeDiff() : _stunTime = 0;
    } else {
        // move ...
        Point target = Map::getCenterOfPosInLogic(_nextPos);// getTargetPos
        if (_pos.x == target.x && _pos.y == target.y) {
            // updated Target if reached
            _nextPos = pMap->getNextPos(_nextPos);
            target = Map::getCenterOfPosInLogic(_nextPos);// getTargetPos
            Point diff = target - _nextPos;
            /*if (diff.x == 1)
                _dir = 90;
            if (diff.x == -1)
                _dir = 270;
            if (diff.y == 1)
                _dir = 0;
            if (diff.y == -1)
                _dir = 180;*/
            _dir = 90;
        } else {
            // actually move
            int runLength = pMap->getMapTimeDiff()*100 * _speed * scale;
            if(runLength == 0)
                runLength=10;
            if (_slowTimer > 0) {
                _slowTimer -= pMap->getMapTimeDiff();
                runLength = (int)((double)runLength*(_speedDiff / 10.0));

            }
            if (_dir == 0) {
                _pos.y -= runLength;
                if (_pos.y < target.y)
                    _pos.y = target.y;
            }
            if (_dir == 90) {
                _pos.x +=  runLength;
                if (_pos.x > target.x)
                    _pos.x = target.x;
            }
            if (_dir == 180) {
                _pos.y +=  runLength;
                if (_pos.y > target.y)
                    _pos.y = target.y;
            }
            if (_dir == 270) {
                _pos.x -= runLength;
                if (_pos.x < target.x)
                    _pos.x = target.x;
            }
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
    _pos = pos;
    _health = health;
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





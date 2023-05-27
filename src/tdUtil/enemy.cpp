//
// Created by banoodle on 17.05.23.
//

#include "enemy.h"

void Enemy::Render() {
        // Render enemy on pos with angle
        // (status like slowed maybe burning or poisoned in future)
}

void Enemy::move() {
    if(_stunTime!=0){
        ulong now = _pMap->getMapTime();
        ulong tDiff = now-_lastMapTime;
        _lastMapTime = now;
        _stunTime > tDiff?_stunTime-=tDiff:_stunTime=0;
    }
    if(_stunTime!=0){
        // pos == nextPos? -> evaluate next step
        // pos and nextPos are positions on pixel level

        // if nextPos is reached ... get new Pos from map

        // else go next step .. for fluid movement
        // if slowTimer != 0 enemy is slowed ... animation and movement are slowed
        // maybe color indicator for slow ?
    }
}

bool Enemy::isAlive() {
    return _alive;
}

bool Enemy::takeDamage(uint16_t damage) {
    _health < damage ? _health = 0 : _health -= damage;
    if (_health == 0){
        startDeathAnimation();
        return false;
    }
    return true;

}

void Enemy::stun(uint16_t time) {
    _stunTime = time;
}

void Enemy::setEnemy(Game *game, Map *map, Point pos, uint16_t health, uint8_t speed, EnemyType type) {
    _pGame = game;
    _pMap = map;
    _pos = pos;
    _health = health;
    _speed = speed;
    _type = type;
    _alive = true;
    _lastMapTime = _pMap->getMapTime();
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



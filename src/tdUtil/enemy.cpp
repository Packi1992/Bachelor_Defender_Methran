//
// Created by banoodle on 17.05.23.
//

#include "enemy.h"
#include "../global.h"
#include "../td/testtd.h"

#include "tdTileHandler.h"
#include "map.h"
void Enemy::Update(float deltaT) {
    if (_stunTime > 0) {
        _stunTime > deltaT ? _stunTime -= deltaT : _stunTime = 0;
    } else {
        // move ...
        updateDir();
        if (_pos.x == _nextPos.x && _pos.y == _nextPos.y) {
            // updated Target if reached
            _reachedGoal = pMap->getObject(_pos) == MapObjects::Goal;
            _nextPos = pMap->getNextPosCentre(_pos);
        } else if (!_reachedGoal) {
            // actually move
            float runLength = deltaT * (float) _speed / 30.0f;
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
                _pos.x = (_pos.x + runLength) - _nextPos.x > 0 ? _pos.x -= runLength : _pos.x = _nextPos.x;
        }
        else{
            // enemy reached goal
            _alive = false;
            tdGlobals->_pl._sanity-= _sanity;
        }
    }
}

void Enemy::takeDamage(uint16_t damage) {
    _health < damage ? _health = 0 : _health -= damage;
    if (_health == 0) {
        startDeathAnimation();
        tdGlobals->_pl._creditPoints+=this->_value;
        _alive = false;
    }
}

void Enemy::stun(uint16_t time) {
    _stunTime = time;
}

void Enemy::setEnemy(Point pos, uint16_t health, uint8_t speed, u8 value, EnemyType type) {
    _pos.x = (float) pos.x + 0.5f;
    _pos.y = (float) pos.y + 0.5f;
    _nextPos = pMap->getNextPosCentre(_pos);
    updateDir();
    _health = health;
    _maxHealth = health;
    _speed = speed;
    _type = type;
    _alive = true;
    _value = value;
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

bool Enemy::isPoisoned() const {
    return _poisonTimer > 0;
}

bool Enemy::isSlowed() const {
    return _slowTimer > 0;
}

void Enemy::updateDir() {
    if (_nextPos.x == _pos.x && _nextPos.y == _pos.y)
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
    FRect en = getHitBox();
    return ((p.x >= en.x) && (p.x < (en.x + en.w)) &&
            (p.y >= en.y) && (p.y < (en.y + en.h))) ? SDL_TRUE : SDL_FALSE;
}

bool Enemy::hasReachedGoal() const {
    return _reachedGoal;
}

void Enemy::Render(u32 totalMSec,bool life, bool hitbox) const {
    if (_alive) {
        // make dstRect
        Point POS = CT::getPosOnScreen(_pos);
        Rect dstRect = {POS.x, POS.y, scale, scale + scale};
        dstRect.x = (int) (POS.x - dstRect.w * 0.5);
        dstRect.y = (int) (POS.y - dstRect.h * 0.8);
        // check if enemy is on screen
        if ((dstRect.x + dstRect.w > 0) &&        // left
            (dstRect.y + dstRect.h > 0) &&        // top
            (dstRect.y < windowSize.y) &&        // bot
            (dstRect.x < windowSize.x))         // right
        {
            rh->tile(&dstRect, TdTileHandler::getEnemySrcRect(this->_type,totalMSec));
        }
        if (hitbox) {
            FRect hitBoxRect = CT::getFRectOnScreen(getHitBox());
            rh->fillFRect(&hitBoxRect, BLACK);
            hitBoxRect.x += hitBoxRect.w / 2 - 5;
            hitBoxRect.y += hitBoxRect.h / 2 - 5;
            hitBoxRect.w = 5;
            hitBoxRect.h = 5;
            rh->fillFRect(&hitBoxRect, RED);
        }
        if(life){
            float health=(float)_health/(float)_maxHealth;
            Rect HealthBar = {POS.x-dstRect.w/2,POS.y-(int)(dstRect.h), dstRect.w,(int)((float)dstRect.h*0.1f)};
            rh->fillRect(&HealthBar,RED);
            Rect HealthBarRest = HealthBar;
            HealthBarRest.w = (int)((float)HealthBarRest.w * health);
            rh->fillRect(&HealthBarRest,GREEN);
            rh->rect(&HealthBar,2,BLACK);
        }
    }
}

FRect Enemy::getHitBox() const {
    return {_pos.x - 0.35f, _pos.y - 1.4f, 0.7f, 1.6f};
}


//
// Created by banoodle on 17.05.23.
//

#include "enemy.h"
#include "../testtd.h"

void Enemy::Update() {
    u32 diff = totalMSec - _lastTimePoint;
    _lastTimePoint = totalMSec;
    if (_stunTime > 0) {
        _stunTime -= (int) diff;
        if (_stunTime < 0) _stunTime = 0;
    }else {
        // move ...
        updateDir();
        if (_pos.x == _nextPos.x && _pos.y == _nextPos.y) {
            // updated Target if reached
            if(pMap->getObject(_pos) != MapObjects::Goal)
                _nextPos = pMap->getNextPosCentre(_pos);
            else
                _reachedGoal = true;
        }
        if (!_reachedGoal) {
            // actually move
            auto runLength = (float) ((float) diff * (float) _speed * 0.00001);
            if (_slowTimer > 0) {
                _slowTimer -= (float) diff;
                if(_speedDiff > 100)
                    _speedDiff = 100;
                runLength = (float) ((double) runLength * (_speedDiff / 100.0f));
            }
            if (_dir == 0)
                ((_pos.y - runLength) > _nextPos.y) ? _pos.y -= runLength : _pos.y = _nextPos.y;
            if (_dir == 90)
                _nextPos.x - (_pos.x + runLength) > 0 ? _pos.x += runLength : _pos.x = _nextPos.x;
            if (_dir == 180)
                _nextPos.y - (_pos.y + runLength) > 0 ? _pos.y += runLength : _pos.y = _nextPos.y;
            if (_dir == 270)
                _nextPos.x - (_pos.x - runLength) < 0 ? _pos.x -= runLength : _pos.x = _nextPos.x;
        } else {
            // enemy reached goal
            _alive = false;
            if(tdGlobals->_pl._sanity >= _sanity)
                tdGlobals->_pl._sanity -= _sanity;
            else
                tdGlobals->_pl._sanity = 0;
        }

        // check stun cooldown
        if (_stunCooldownTimer > 0) {
            _stunCooldownTimer -= (int) diff;
            if (_stunCooldownTimer < 0) _stunCooldownTimer = 0;
        }
    }
}

void Enemy::takeDamage(Projectile *p) {
    _health < p->_damage ? _health = 0 : _health -= p->_damage;
    if (_health == 0) {
        startDeathAnimation();
        tdGlobals->_pl._creditPoints += this->_value;
        collide();
        _alive = false;
    }
}

void Enemy::collide() {
    float x = (float)(CT::getPosOnScreen(_pos).x) / float(windowSize.x);
    audioHandler->playSound(SoundEnemyOrdinary, x);
}

void Enemy::setEnemy(Point pos, uint16_t health, uint8_t speed, u8 value, EnemyType type, float size, uint copycount) {
    _pos.x = (float)pos.x + 0.5f;
    _pos.y = (float)pos.y + 0.5f;
    _nextPos = pMap->getNextPosCentre(_pos);
    updateDir();
    _health = health;
    _maxHealth = health;
    _speed = speed;
    if (type == Ordinary) {
        type = (totalMSec % 4 > 0) ? Boy : Girl;
    }
    _type = type;
    _alive = true;
    _value = value;
    _size = size;
    _copycount = copycount;
}

void Enemy::setEnemy(const GameEvent *ev) {
    Point pos = pMap->getStartPoint(ev->SpawnPoint);
    _pos.x = (float) pos.x + 0.5f;
    _pos.y = (float) pos.y + 0.5f;
    _nextPos = pMap->getNextPosCentre(_pos);
    updateDir();
    _health = ev->health;
    _maxHealth = ev->health;
    _sanity = ev->sanity;
    _speed = ev->speed;
    _copycount = 0;
    if (ev->type == Ordinary) {
        _type = (totalMSec % 4 > 0) ? Boy : Girl;
    }
    _alive = true;
    _value = ev->value;
    switch (ev->type) {
    case Boss_Frohle_Poehlich:
        _size = 1.2f;
        break;
    case Boss_Drueberbolz:
        _size = 1.2f;
        break;
    default:
        _size = 1.0f;
    }
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
            _dir = BOTTOM;
        else
            _dir = TOP;
    } else if (_nextPos.y == _pos.y) {// left or right
        if (_nextPos.x > _pos.x)
            _dir = RIGHT;
        else
            _dir = LEFT;
    }

}

bool Enemy::hasReachedGoal() const {
    return _reachedGoal;
}

void Enemy::Render() const {
    if (_alive) {
        // make dstRect
        Point POS = CT::getPosOnScreen(_pos);
        Rect dstRect = {POS.x, POS.y, (int)((float)scale * _size), (int)((float)(scale+scale) * _size)};
        dstRect.x = (int) (POS.x - dstRect.w * 0.5);
        dstRect.y = (int) (POS.y - dstRect.h * 0.8);
        u32 anim = _stunTime > 0 ? 0 : (pGame->isGameover() ? 0 : totalMSec + _animOffset);
        anim = (u32)((float)anim * ((float)_speed* 0.01f));
        // check if enemy is on screen

        if (Game::onScreen(dstRect)) {
            bool flipped;
            switch (_dir) {
                case 270:
                    flipped = true;
                    break;
                default:
                    flipped = false;
                    break;
            }
            rh->tile(&dstRect, TdTileHandler::getEnemySrcRect(this->_type, anim, _dir), flipped);
        }
    }
}

void Enemy::RenderExtras(bool life, bool hitBox) const {
    if (_alive) {
        if (hitBox) {
            FRect hitBoxRect = CT::getFRectOnScreen(getHitBox());
            rh->fillFRect(&hitBoxRect, BLACK);
            hitBoxRect.x += hitBoxRect.w * 0.5f - 5;
            hitBoxRect.y += hitBoxRect.h * 0.5f - 5;
            hitBoxRect.w = 5;
            hitBoxRect.h = 5;
            rh->fillFRect(&hitBoxRect, RED);
        }
        if (life && _maxHealth > _health) {
            Point POS = CT::getPosOnScreen(_pos);
            Rect dstRect = {POS.x, POS.y, scale, scale + scale};
            float health = (float) _health / (float) _maxHealth;
            Rect HealthBar = {(int) ((float) POS.x - (float) dstRect.w * 0.5f),
                              (int) ((float) POS.y - (float) (dstRect.h) * 0.85f), dstRect.w,
                              (int) ((float) dstRect.h * 0.1f)};
            rh->fillRect(&HealthBar, RED);
            Rect HealthBarRest = HealthBar;
            HealthBarRest.w = (int) ((float) HealthBarRest.w * health);
            rh->fillRect(&HealthBarRest, GREEN);
            rh->rect(&HealthBar, 2, BLACK);
        }
    }
}

FRect Enemy::getHitBox() const {
    return {_pos.x - 0.35f*_size, _pos.y - 1.4f*_size, 0.7f*_size, 1.6f*_size};
}

void Enemy::stun(u16 time) {
    if (_stunCooldownTimer == 0) {
        _stunTime = time;
        _stunCooldownTimer = _stunCooldown;
    }
    _recursivable = false;
}

Enemy::Enemy() {
    _lastTimePoint = totalMSec;
    _animOffset = _lastTimePoint % 800;
}

bool Enemy::isRecursivable() const {
    return _recursivable && _copycount < 2;
}

Enemy::Enemy(std::shared_ptr<Enemy> e, bool recursive) {
    _pos = e->_pos;
    _nextPos = pMap->getNextPosCentre(_pos);
    _health = (u16)((float)e->_health * (recursive?0.8f:1.0f));
    _maxHealth = (u16)((float)e->_health* (recursive?0.8f:1.0f));
    _speed = (u8)((float)e->_speed* (recursive?0.8f:1.0f));
    _type = e->_type;
    _alive = true;
    _value = e->_value* (recursive?0:1);
    _recursivable = e->_recursivable && (!recursive || (e->_copycount < 2));
    _size = e->_size* (recursive?0.8f:1.0f);
    _copycount = e->_copycount+ (recursive?1:0);
    _lastTimePoint = totalMSec;
    _sanity = (u16)((float)e->_sanity* (recursive?0.8f:1.0f));
}

bool Enemy::isStunable() const {
    return (_stunCooldownTimer <= 0 && _stunable);
}

bool Enemy::isRow(float row) const {
    return (int)(row*10) ==(int)(_pos.y*10);
}


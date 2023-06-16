//
// Created by banoodle on 17.05.23.
//

#include "enemy.h"
#include "../../global.h"
#include "../testtd.h"
#include "../projectiles/projectile.h"
#include "../../tdUtil/tdTileHandler.h"
#include "../../tdUtil/map.h"
#include "../../gamebase.h"

void Enemy::Update() {
    if (_stunTime > 0) {
        _stunTime > deltaTg ? _stunTime -= deltaTg : _stunTime = 0;
    } else {
        // move ...
        updateDir();
        if (_pos.x == _nextPos.x && _pos.y == _nextPos.y) {
            // updated Target if reached
            _reachedGoal = pMap->getObject(_pos) == MapObjects::Goal;
            _nextPos = pMap->getNextPosCentre(_pos);
        } else if (!_reachedGoal) {
            // actually move
            float runLength = deltaTg * (float) _speed / 30.0f;
            if (_slowTimer > 0) {
                _slowTimer -= deltaTg;
                runLength = (float) ((double) runLength * (_speedDiff / 10.0));
            }
            if (_dir == 0)
                (_pos.y + runLength) - _nextPos.y > 0 ? _pos.y -= runLength : _pos.y = _nextPos.y;
            if (_dir == 90)
                _nextPos.x - (_pos.x + runLength) > 0 ? _pos.x += runLength : _pos.x = _nextPos.x;
            if (_dir == 180)
                _nextPos.y - (_pos.y + runLength) > 0 ? _pos.y += runLength : _pos.y = _nextPos.y;
            if (_dir == 270)
                (_pos.x + runLength) - _nextPos.x > 0 ? _pos.x -= runLength : _pos.x = _nextPos.x;
        } else {
            // enemy reached goal
            _alive = false;
            tdGlobals->_pl._sanity -= _sanity;
        }
    }
}

void Enemy::takeDamage(Projectile *p) {
    _health < p->_damage ? _health = 0 : _health -= p->_damage;
    if (_health == 0) {
        startDeathAnimation();
        tdGlobals->_pl._creditPoints += this->_value;
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

bool Enemy::hasReachedGoal() const {
    return _reachedGoal;
}

void Enemy::Render() const {
    if (_alive) {
        // make dstRect
        Point POS = CT::getPosOnScreen(_pos);
        Rect dstRect = {POS.x, POS.y, scale, scale + scale};
        dstRect.x = (int) (POS.x - dstRect.w * 0.5);
        dstRect.y = (int) (POS.y - dstRect.h * 0.8);
        u32 anim = (pGame->isGameover()?0:totalMscg);
        // check if enemy is on screen
        if (Game::onScreen(dstRect)) {
            Direction dir;
            bool flipped = false;
            switch (_dir) {
                case 0:
                    dir = Direction::TOP;
                    flipped = false;
                    break;
                case 90:
                    dir = Direction::RIGHT;
                    flipped = false;
                    break;
                case 180:
                    dir = Direction::BOTTOM;
                    flipped = false;
                    break;
                case 270:
                    dir = Direction::LEFT;
                    flipped = true;
                    break;
                default:
                    break;
            }
            rh->tile(&dstRect, TdTileHandler::getEnemySrcRect(this->_type, anim, dir), flipped);
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
    return {_pos.x - 0.35f, _pos.y - 1.4f, 0.7f, 1.6f};
}




#include "bossEnemy.h"
#include "../testtd.h"

BossEnemy::BossEnemy() {
	_stunable = false;
    _recursivable = false;
}

BossEnemy::BossEnemy(std::shared_ptr<Enemy> e)
	: Enemy(e) {

}


BossEnemy::BossEnemy(std::shared_ptr<BossEnemy> e) {
    _size = 1.5f;
    _pos = e->_pos;
    _nextPos = pMap->getNextPosCentre(_pos);
    _health = e->_health;
    _maxHealth = e->_health;
    _speed = e->_speed;
    _type = e->_type;
    _alive = true;
    _value = e->_value;
    _recursivable = e->_recursivable;
    _copycount = e->_copycount;
    _lastTimePoint = totalMSec;
    _sanity = e->_sanity;
}

void BossEnemy::takeDamage(Projectile* p) {
    _health < p->_damage ? _health = 0 : _health -= p->_damage;
    if (_health == 0) {
        startDeathAnimation();
        tdGlobals->_pl._creditPoints += this->_value;
        collide();
        _alive = false;
        audioHandler->playSound(getSoundName());
    }
}


soundType BossEnemy::getSoundName() {
	return SoundError;
}

void BossEnemy::collide() {
	float x = (float)(CT::getPosOnScreen(_pos).x) / float(windowSize.x);
	audioHandler->playSound(getSoundName(), x);
}
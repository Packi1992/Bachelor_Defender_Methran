#include "bossEnemy.h"
#include "../testtd.h"

BossEnemy::BossEnemy() {
	_stunable = false;
    _recursivable = false;
	_sanity *= 3;
	_value *= 3;
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


soundType BossEnemy::getSoundName() {
	return SoundError;
}

void BossEnemy::collide() {
	float x = (float)(CT::getPosOnScreen(_pos).x) / float(windowSize.x);
	audioHandler->playSound(getSoundName(), x);
	cout << getSoundName() << endl;
}
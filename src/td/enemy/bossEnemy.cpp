#include "bossEnemy.h"

BossEnemy::BossEnemy() {
	_stunable = false;
    _recursivable = false;
	_sanity *= 3;
	_value *= 3;
}

BossEnemy::BossEnemy(std::shared_ptr<Enemy> e)
	: Enemy(e) {

}

soundType BossEnemy::getSoundName() {
	return SoundError;
}

void BossEnemy::collide() {
	float x = (float)(CT::getPosOnScreen(_pos).x) / float(windowSize.x);
	audioHandler->playSound(getSoundName(), x);
	cout << getSoundName() << endl;
}
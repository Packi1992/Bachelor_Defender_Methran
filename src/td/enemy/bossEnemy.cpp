#include "bossEnemy.h"

BossEnemy::BossEnemy(FPoint pos, uint16_t health, uint8_t speed, u8 value, EnemyType type, float size, bool stunable)
	: Enemy(pos, health, speed, value, type, size, stunable) {

}

soundType BossEnemy::getSoundName() {
	return SoundError;
}

void BossEnemy::collide() {
	float x = (float)(CT::getPosOnScreen(_pos).x) / float(windowSize.x);
	audioHandler->playSound(getSoundName(), x);
	cout << getSoundName() << endl;
}
#include "frolePoehlich.h"
#include "../testtd.h"

FrolePoehlich::FrolePoehlich() : BossEnemy(){
    _size = 1.2f;
}

FrolePoehlich::FrolePoehlich(FPoint pos, uint16_t health, uint8_t speed, u8 value, EnemyType type, float size, bool stunable)
	: BossEnemy(pos, health, speed, value, type, size, stunable) {
	_copyable = false;
	_sanity *= 3;
	_value *= 3;
}

soundType FrolePoehlich::getSoundName() {
	return SoundFrolePoehlich;
}
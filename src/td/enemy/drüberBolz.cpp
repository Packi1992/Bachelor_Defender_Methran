#include "dr�berBolz.h"
#include "../testtd.h"

Dr�berBolz::Dr�berBolz(FPoint pos, uint16_t health, uint8_t speed, u8 value, EnemyType type, float size, bool stunable)
	: BossEnemy(pos, health, speed, value, type, size, stunable) {
	_copyable = false;
	_sanity *= 3;
	_value *= 3;
}

soundType Dr�berBolz::getSoundName() {
	return SoundDrueberbolz;
}
#include "froleP�hlich.h"

FroleP�hlich::FroleP�hlich(FPoint pos, uint16_t health, uint8_t speed, u8 value, EnemyType type, float size, bool stunable)
	: BossEnemy(pos, health, speed, value, type, size, stunable) {
	_copyable = false;
	_sanity *= 3;
	_value *= 3;
}
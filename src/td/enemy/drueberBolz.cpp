#include "drueberBolz.h"
#include "../testtd.h"

DrueberBolz::DrueberBolz() : BossEnemy() {
    _size = 1.2f;
}

DrueberBolz::DrueberBolz(FPoint pos, uint16_t health, uint8_t speed, u8 value, float size)
	: BossEnemy(pos, health, speed, value, EnemyType::Boss_Drueberbolz, size, false) {
	_copyable = false;
	_sanity *= 3;
	_value *= 3;
}

soundType DrueberBolz::getSoundName() {
	return SoundDrueberbolz;
}

void DrueberBolz::set(Point pos, uint16_t health, uint8_t speed, u8 value, float size) {
    _pos = {pos.x-0.5f,pos.y-0.5f};
    _health = health;
    _speed = speed;
    _value = value;
    _size = size;
    _type = Boss_Drueberbolz;
}
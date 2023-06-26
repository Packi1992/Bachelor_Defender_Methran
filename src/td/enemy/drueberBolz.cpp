#include "drueberBolz.h"
#include "../testtd.h"

DrueberBolz::DrueberBolz() : BossEnemy() {
    _size = 1.2f;
}

DrueberBolz::DrueberBolz(std::shared_ptr<BossEnemy> e)
        : BossEnemy(e) {
    _recursivable = false;
    _sanity *= 3;
    _value *= 3;
    _type = EnemyType::Boss_Drueberbolz;
}

soundType DrueberBolz::getSoundName() {
    return SoundDrueberbolz;
}

void DrueberBolz::set(Point pos, uint16_t health, uint8_t speed, u8 value, float size) {
    _pos = {pos.x + 0.5f, pos.y + 0.5f};
    _health = health;
    _speed = speed;
    _value = value;
    _size = size;
    _type = Boss_Drueberbolz;
}

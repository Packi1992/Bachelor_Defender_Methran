#include "bossEnemy.h"

BossEnemy::BossEnemy(FPoint pos, uint16_t health, uint8_t speed, u8 value, EnemyType type, float size, bool stunable)
	: Enemy(pos, health, speed, value, type, size, stunable) {

}
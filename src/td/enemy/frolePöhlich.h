#ifndef SDL_BASEGAME_FroleP�hlich_H
#define SDL_BASEGAME_FroleP�hlich_H

#include "bossEnemy.h"

class FroleP�hlich : public BossEnemy {
	FroleP�hlich(FPoint pos, uint16_t health, uint8_t speed, u8 value, EnemyType type, float size = 1.0f, bool stunable = false);
};

#endif //SDL_BASEGAME_FroleP�hlich_H
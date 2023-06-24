#ifndef SDL_BASEGAME_DRÜBERBOLZ_H
#define SDL_BASEGAME_DRÜBERBOLZ_H

#include "bossEnemy.h"

class DrüberBolz : public BossEnemy {
	DrüberBolz(FPoint pos, uint16_t health, uint8_t speed, u8 value, EnemyType type, float size = 1.0f, bool stunable);
};

#endif //SDL_BASEGAME_DRÜBERBOLZ_H
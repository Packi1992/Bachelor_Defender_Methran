#ifndef SDL_BASEGAME_DRÜBERBOLZ_H
#define SDL_BASEGAME_DRÜBERBOLZ_H

#include "bossEnemy.h"

class DrüberBolz : public BossEnemy {
public:
	DrüberBolz();
	DrüberBolz(FPoint pos, uint16_t health, uint8_t speed, u8 value, EnemyType type, float size = 1.0f, bool stunable = false);
	soundType getSoundName() override;
};

#endif //SDL_BASEGAME_DRÜBERBOLZ_H
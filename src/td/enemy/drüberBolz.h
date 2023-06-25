#ifndef SDL_BASEGAME_DR�BERBOLZ_H
#define SDL_BASEGAME_DR�BERBOLZ_H

#include "bossEnemy.h"

class Dr�berBolz : public BossEnemy {
public:
	Dr�berBolz();
	Dr�berBolz(FPoint pos, uint16_t health, uint8_t speed, u8 value, EnemyType type, float size = 1.0f, bool stunable = false);
	soundType getSoundName() override;
};

#endif //SDL_BASEGAME_DR�BERBOLZ_H
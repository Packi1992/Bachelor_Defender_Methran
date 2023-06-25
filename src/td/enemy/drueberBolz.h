#ifndef SDL_BASEGAME_DRUEBERBOLZ_H
#define SDL_BASEGAME_DRUEBERBOLZ_H

#include "bossEnemy.h"

class DrueberBolz : public BossEnemy {
public:
	DrueberBolz();
	DrueberBolz(FPoint pos, uint16_t health, uint8_t speed, u8 value, float size = 1.2f);
    void set(Point pos, uint16_t health, uint8_t speed, u8 value, float size);
	soundType getSoundName() override;
};

#endif //SDL_BASEGAME_DRUEBERBOLZ_H
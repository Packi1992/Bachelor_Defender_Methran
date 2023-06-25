#ifndef SDL_BASEGAME_DRUEBERBOLZ_H
#define SDL_BASEGAME_DRUEBERBOLZ_H

#include "bossEnemy.h"

class DrueberBolz : public BossEnemy {
public:
	DrueberBolz();
	DrueberBolz(std::shared_ptr<Enemy> e);
    void set(Point pos, uint16_t health, uint8_t speed, u8 value, float size);
	soundType getSoundName() override;
};

#endif //SDL_BASEGAME_DRUEBERBOLZ_H
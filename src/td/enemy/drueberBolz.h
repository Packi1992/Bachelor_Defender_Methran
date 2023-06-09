#ifndef SDL_BASEGAME_DRUEBERBOLZ_H
#define SDL_BASEGAME_DRUEBERBOLZ_H

#include "bossEnemy.h"

class DrueberBolz : public BossEnemy {
public:
	DrueberBolz();
	DrueberBolz(std::shared_ptr<BossEnemy> e);
	soundType getSoundName() override;
};

#endif //SDL_BASEGAME_DRUEBERBOLZ_H
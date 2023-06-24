#ifndef SDL_BASEGAME_BOSSENEMY_H
#define SDL_BASEGAME_BOSSENEMY_H

#include "enemy.h"

class BossEnemy : public Enemy {
public:
	BossEnemy(FPoint pos, uint16_t health, uint8_t speed, u8 value, EnemyType type, float size = 1.0f, bool stunable);
};

#endif //SDL_BASEGAME_BOSSENEMY_H
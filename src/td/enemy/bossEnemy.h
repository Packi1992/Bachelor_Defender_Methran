#ifndef SDL_BASEGAME_BOSSENEMY_H
#define SDL_BASEGAME_BOSSENEMY_H

#include "enemy.h"

class BossEnemy : public Enemy {
public:
	BossEnemy(FPoint pos, uint16_t health, uint8_t speed, u8 value, EnemyType type, float size, bool stunable);
};

#endif //SDL_BASEGAME_BOSSENEMY_H
#ifndef SDL_BASEGAME_FrolePoehlich_H
#define SDL_BASEGAME_FrolePoehlich_H

#include "bossEnemy.h"

class FrolePoehlich : public BossEnemy {
public:
	FrolePoehlich();
	FrolePoehlich(FPoint pos, uint16_t health, uint8_t speed, u8 value, EnemyType type, float size = 1.2f, bool stunable = false);
	soundType getSoundName() override;
};

#endif //SDL_BASEGAME_FrolePoehlich_H
#ifndef SDL_BASEGAME_FrolePöhlich_H
#define SDL_BASEGAME_FrolePöhlich_H

#include "bossEnemy.h"

class FrolePöhlich : public BossEnemy {
public:
	FrolePöhlich();
	FrolePöhlich(FPoint pos, uint16_t health, uint8_t speed, u8 value, EnemyType type, float size = 1.0f, bool stunable = false);
	soundType getSoundName() override;
};

#endif //SDL_BASEGAME_FrolePöhlich_H
#ifndef SDL_BASEGAME_FrolePöhlich_H
#define SDL_BASEGAME_FrolePöhlich_H

#include "bossEnemy.h"

class FrolePöhlich : public BossEnemy {
	FrolePöhlich(FPoint pos, uint16_t health, uint8_t speed, u8 value, EnemyType type, float size = 1.0f, bool stunable = false);
};

#endif //SDL_BASEGAME_FrolePöhlich_H
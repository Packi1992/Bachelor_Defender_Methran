//
// Created by dex on 6/19/23.
//

#ifndef SDL_BACHELORDEFENDER_SMALLEMY_H
#define SDL_BACHELORDEFENDER_SMALLEMY_H

#include "enemy.h"

class Smallemy : public Enemy{
public:
    Smallemy(FPoint pos, uint16_t health, uint8_t speed, u8 value, EnemyType type);
    void Render() const override;
    [[nodiscard]] FRect getHitBox() const override;
};


#endif //SDL_BACHELORDEFENDER_SMALLEMY_H

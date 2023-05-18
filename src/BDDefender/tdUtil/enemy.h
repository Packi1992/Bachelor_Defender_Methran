//
// Created by banoodle on 17.05.23.
//

#ifndef SDL_BASEGAME_ENEMY_H
#define SDL_BASEGAME_ENEMY_H
#include "../../global.h"
#include "../../gamebase.h"
#include "map.h"
enum EnemyType{
    Ordinary,
    Fast,
    Silly,
    Strong
};

class Enemy {
    Enemy();
    void setEnemy(Game *game,Map* map, Point pos, int Health, EnemyType type=Ordinary);
};


#endif //SDL_BASEGAME_ENEMY_H

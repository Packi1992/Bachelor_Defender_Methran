//
// Created by banoodle on 27.05.23.
//

#ifndef SDL_BACHELORDEFENDER_ENEMYHANDLER_H
#define SDL_BACHELORDEFENDER_ENEMYHANDLER_H
#include "../gamebase.h"
#include "enemy.h"
#define MAXENEMIES 250
class EnemyHandler {
public:
    EnemyHandler();
    Enemy _enemies[MAXENEMIES];
    Texture *_texture={};
    void Render();
    void Update(float deltaT);
    void UnInit();
    void addEnemy(Enemy e);
protected:
    Rect srcRect{};
    Rect dstRect{};
    Point PosOnScreen{};
    int overflow=0;
    Rect * getSrcRect(Enemy &e);
    Rect * getDstRect(Enemy &enemy);
    [[nodiscard]] bool onScreen() const;
};


#endif //SDL_BACHELORDEFENDER_ENEMYHANDLER_H

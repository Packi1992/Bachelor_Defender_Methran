//
// Created by dex on 5/26/23.
//

#ifndef SDL_BACHELORDEFENDER_PROJECTILESHANDLER_H
#define SDL_BACHELORDEFENDER_PROJECTILESHANDLER_H

#include "../global.h"
#include "../gamebase.h"

class ProjectilesHandler;
class Projectile;

class ProjectilesHandler {
public:
    ~ProjectilesHandler();

    void Render();

    void move();

    Projectile *_projectiles[MAXPROJECTILES] = {};

    void add(Projectile *p);

    void set();

    void collisionDetected(Projectile **p);

private:
    uint overflow = 0;
    Texture *_texture = nullptr;
};

#endif //SDL_BACHELORDEFENDER_PROJECTILESHANDLER_H
//
// Created by dex on 5/26/23.
//

#ifndef SDL_BACHELORDEFENDER_PROJECTILESHANDLER_H
#define SDL_BACHELORDEFENDER_PROJECTILESHANDLER_H

#include "../global.h"
#include "../gamebase.h"
#include "../tdUtil/enemy.h"
#include "Projectiles/projectile.h"
#include "../tdUtil/coordinateTransformer.h"

using CT = CoordinateTransformer;
#define MAXPROJECTILES 100

class ProjectilesHandler {
public:
    ~ProjectilesHandler();

    void Render(const u32 frame, const u32 totalMSec, const float deltaT);

    void move();

    Projectile *_projectiles[MAXPROJECTILES] = {};

    void add(Projectile *p);

    void set();

    void remove(Projectile **p);

private:
    uint overflow = 0;
    Texture *_texture = nullptr;

    static bool onScreen(Point &posOnScreen, int &size);
};

#endif //SDL_BACHELORDEFENDER_PROJECTILESHANDLER_H
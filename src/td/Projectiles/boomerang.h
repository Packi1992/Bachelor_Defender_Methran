//
// Created by dex on 6/10/23.
//

#ifndef SDL_BACHELORDEFENDER_BOOMERANG_H
#define SDL_BACHELORDEFENDER_BOOMERANG_H
#include "projectile.h"

class Boomerang :public Projectile {
public:
    Boomerang();
    void move() override;
};

#endif //SDL_BACHELORDEFENDER_BOOMERANG_H

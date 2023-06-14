//
// Created by dex on 6/8/23.
//

#ifndef SDL_BACHELORDEFENDER_FIRE_H
#define SDL_BACHELORDEFENDER_FIRE_H

#include "projectile.h"

class Fire:public Projectile {
public:
    Fire();
    void move() override;
    void collide() override;
};


#endif //SDL_BACHELORDEFENDER_FIRE_H

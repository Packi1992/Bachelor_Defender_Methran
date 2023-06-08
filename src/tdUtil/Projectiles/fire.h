//
// Created by dex on 6/8/23.
//

#ifndef SDL_BACHELORDEFENDER_FIRE_H
#define SDL_BACHELORDEFENDER_FIRE_H

#include "projectile.h"

// Maybe changing to class?
struct Fire:Projectile {
    Fire();
    void move() override;
};


#endif //SDL_BACHELORDEFENDER_FIRE_H

//
// Created by dex on 6/8/23.
//

#ifndef SDL_BACHELORDEFENDER_ARROW_H
#define SDL_BACHELORDEFENDER_ARROW_H
#include "projectile.h"

// Maybe changing to class?
struct Arrow:Projectile {
    Arrow();
    void move() override;
};


#endif //SDL_BACHELORDEFENDER_ARROW_H

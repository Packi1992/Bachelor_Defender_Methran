//
// Created by dex on 6/8/23.
//

#ifndef SDL_BACHELORDEFENDER_ARROW_H
#define SDL_BACHELORDEFENDER_ARROW_H

#include "projectile.h"

class Arrow : public Projectile {
public:
    Arrow();

    void move(float deltaT) override;
    void collide(float deltaT) override;
};


#endif //SDL_BACHELORDEFENDER_ARROW_H

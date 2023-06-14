//
// Created by banoodle on 6/8/23.
//

#ifndef SDL_BACHELORDEFENDER_LinkProjectile_H
#define SDL_BACHELORDEFENDER_LinkProjectile_H
#include "projectile.h"

class LinkProjectile:public Projectile {
public:
    LinkProjectile();
    void move() override;
};


#endif //SDL_BACHELORDEFENDER_LinkProjectile_H

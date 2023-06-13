//
// Created by dex on 6/10/23.
//

#ifndef SDL_BACHELORDEFENDER_BOOMERANG_H
#define SDL_BACHELORDEFENDER_BOOMERANG_H

#include "projectile.h"

class Boomerang : public Projectile {
private:
    float _minFlyingTime = .1f;
    bool _toggleDirection = false;
public:
    Boomerang();
    void Render(u32 totalMSec) override;
    void move(float deltaT) override;
    void collide(float deltaT) override;
};

#endif //SDL_BACHELORDEFENDER_BOOMERANG_H

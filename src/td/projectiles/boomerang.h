//
// Created by dex on 6/10/23.
//

#ifndef SDL_BACHELORDEFENDER_BOOMERANG_H
#define SDL_BACHELORDEFENDER_BOOMERANG_H

#include "projectile.h"

class Boomerang : public Projectile {
private:
    int _minFlyingTime = 1000;
    bool _toggleDirection = false;
    u_int32_t _lastTimePoint = 0;
    int _diff = 0;
public:
    Boomerang();

    void Render() override;

    void Update() override;

    void collide() override;
};

#endif //SDL_BACHELORDEFENDER_BOOMERANG_H

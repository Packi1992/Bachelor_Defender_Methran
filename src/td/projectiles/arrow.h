//
// Created by dex on 6/8/23.
//

#ifndef SDL_BACHELORDEFENDER_ARROW_H
#define SDL_BACHELORDEFENDER_ARROW_H

#include "projectile.h"

class Arrow : public Projectile {
    float _aimSpeed = 1.0f;
public:
    Arrow();
    Arrow(Arrow &p, std::shared_ptr<Enemy> e, uint16_t direction);
    void Update() override;
};


#endif //SDL_BACHELORDEFENDER_ARROW_H

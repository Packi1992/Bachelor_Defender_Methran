//
// Created by dex on 6/18/23.
//

#ifndef SDL_BACHELORDEFENDER_BASEEXPLOSION_H
#define SDL_BACHELORDEFENDER_BASEEXPLOSION_H


#include "projectile.h"

class BaseExplosion : public Projectile {

public:
    BaseExplosion();

    BaseExplosion(SDL_FPoint pos, int exdmg);

    BaseExplosion(BaseExplosion &p, std::shared_ptr<Enemy> e, uint16_t direction);

    void Render() override;

    void Update() override;

    void collide() override;

    bool collision(std::shared_ptr<Enemy> e) override;
};

#endif //SDL_BACHELORDEFENDER_BASEEXPLOSION_H

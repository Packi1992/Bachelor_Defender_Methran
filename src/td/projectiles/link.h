//
// Created by banoodle on 6/8/23.
//

#ifndef SDL_BACHELORDEFENDER_LinkProjectile_H
#define SDL_BACHELORDEFENDER_LinkProjectile_H

#include "projectile.h"

class LinkProjectile : public Projectile {
public:
    LinkProjectile();

    void Update() override;

    void set(u16 timeToLife, FPoint position, FPoint position2, u8 damage);

    void Render() override;

    bool collision(std::shared_ptr<Enemy> e) override;

private:
    FPoint _position2{};
};

#endif //SDL_BACHELORDEFENDER_LinkProjectile_H
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
    void set(float length, u16 timeToLife, FPoint position,FPoint  position2, u16 direction);
    void Render();
private:
    float _length=0;
    FPoint _position2;
};


#endif //SDL_BACHELORDEFENDER_LinkProjectile_H

//
// Created by dex on 6/19/23.
//

#ifndef SDL_BACHELORDEFENDER_STRINGPROJECTILE_H
#define SDL_BACHELORDEFENDER_STRINGPROJECTILE_H

#include "projectile.h"

class StringProjectile : public Projectile {
    u32 _diff = 0;
    u32 _tick = 200;
    Rect _src{};
    Texture *_texture = nullptr;
public:
    StringProjectile();

    StringProjectile(StringProjectile &p);

    void Update() override;

    void Render() override;

    void collide() override;

    bool collision(std::shared_ptr<Enemy> e) override;

    string _string;
};


#endif //SDL_BACHELORDEFENDER_STRINGPROJECTILE_H

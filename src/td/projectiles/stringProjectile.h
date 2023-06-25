//
// Created by dex on 6/19/23.
//

#ifndef SDL_BACHELORDEFENDER_STRINGPROJECTILE_H
#define SDL_BACHELORDEFENDER_STRINGPROJECTILE_H

#include "projectile.h"

class StringProjectile : public Projectile {

    u32 _tick = 200;
    Rect _src{};
    Texture *_texture = nullptr;
public:
    StringProjectile();

    StringProjectile(StringProjectile &p);

    void Update() override;

    void Render() override;

    void collide() override;

    int _fontSize = 0;

    bool collision(std::shared_ptr<Enemy> e) override;

    int _xFix = 0;
    int _yFix = 0;
    SDL_FPoint _end{};
    string _string;
};


#endif //SDL_BACHELORDEFENDER_STRINGPROJECTILE_H

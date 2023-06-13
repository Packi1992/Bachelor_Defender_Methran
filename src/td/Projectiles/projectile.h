//
// Created by dex on 6/8/23.
//

#ifndef SDL_BACHELORDEFENDER_PROJECTILE_H
#define SDL_BACHELORDEFENDER_PROJECTILE_H

#include "../../global.h"

class Enemy;

class Projectile {
public:
    float _hitCooldown = 0.1f;
    bool _alive = true;
    FPoint _position = {-1.0f, -1.0f};
    FPoint _startingPoint = {-1.0f, -1.0f};
    ProjectileType _type = ProjectileType::DISABLED;
    uint16_t _size = 100;
    uint16_t _speed = 100;
    uint16_t _direction = 270;
    bool _destroy = false;
    Enemy *_targetE = nullptr;
    FPoint _targetP = {0, 0};
    uint16_t _ttl = 1000;
    uint8_t _damage = 100;
    bool _moveable = false;

    virtual void move(float deltaT);
    virtual void collide(float deltaT);
    virtual void Render(u32 totalMSec);

    [[nodiscard]] bool onScreen() const;
};

#include "arrow.h"
#include "fire.h"
#include "link.h"
#include "boomerang.h"

#endif //SDL_BACHELORDEFENDER_PROJECTILE_H

//
// Created by dex on 6/8/23.
//

#ifndef SDL_BACHELORDEFENDER_PROJECTILE_H
#define SDL_BACHELORDEFENDER_PROJECTILE_H

#include "../../util/global.h"

class Enemy;

class Projectile {
public:
    struct HitTimer {
        std::shared_ptr<Enemy> enemy = nullptr;
        int hitCooldown = 0;
    };
    bool _alive = true;
    int _ttl = 0;
    int _diff = 0;
    bool _destroy = false;
    ProjectileType _type = ProjectileType::DISABLED;

    FPoint _startingPoint = {-1.0f, -1.0f};
    FPoint _position = {-1.0f, -1.0f};
    float _hitCoolDown = 0.1f;

    uint16_t _size = 100;
    uint16_t _speed = 100;
    uint16_t _direction = 270;

    std::shared_ptr<Enemy> _targetE = nullptr;
    FPoint _targetP = {0, 0};

    uint8_t _damage = 100;
    bool _moveable = false;
    Vector<HitTimer> hitList;
    soundType _hitSound = SoundDisabled;
    u32 _lastTimePoint;

    virtual ~Projectile();

    Projectile();

    Projectile(Projectile &p);

    Projectile(Projectile &p, std::shared_ptr<Enemy> e, uint16_t direction);

    virtual bool collision(std::shared_ptr<Enemy> e);

    virtual void collide();

    Point _posOnScreen{};
    Rect _dstRect{};

    virtual void Update();

    virtual void Render();


    [[nodiscard]] bool onScreen() const;
};

#include "arrow.h"
#include "fire.h"
#include "link.h"
#include "boomerang.h"
#include "baseExplosion.h"
#include "hashbomb.h"
#include "stringProjectile.h"


#endif //SDL_BACHELORDEFENDER_PROJECTILE_H

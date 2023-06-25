//
// Created by dex on 6/10/23.
//

#ifndef SDL_BACHELORDEFENDER_BOOMERANG_H
#define SDL_BACHELORDEFENDER_BOOMERANG_H

#include "projectile.h"

class Boomerang : public Projectile {
private:
    int _minFlyingTime = 1000;
    int _flyingTime = 1000;
    bool _toggleDirection = false;
    FPoint _endFlyPos = {0.0f, 0.0f};
    //   u_int32_t _lastTimePoint = 0;
    int _diff = 0;
    float _travellength = 0.0f;
    FPoint _rotatePoint = {0.0f,0.0f};
    void calcNextPos();
    bool _midflight = false;
    FPoint e{};
    DPoint _targetVec{};
    DPoint _driftVec{};
    DPoint _counterDriftVec{};
public:
    bool _enHittable = false;
    bool _freez = false;
    uint _stunduration = 1500;

    Boomerang();

    Boomerang(Boomerang &p, std::shared_ptr<Enemy> e, uint16_t direction);

    void Render() override;

    void Update() override;

    void collide() override;

    bool collision(std::shared_ptr<Enemy> e) override;

    void calculateVectors();
};

#endif //SDL_BACHELORDEFENDER_BOOMERANG_H

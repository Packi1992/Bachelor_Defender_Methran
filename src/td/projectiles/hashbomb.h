//
// Created by dex on 6/18/23.
//

#ifndef SDL_BACHELORDEFENDER_HASHBOMB_H
#define SDL_BACHELORDEFENDER_HASHBOMB_H


#include "projectile.h"

class Hashbomb : public Projectile {
private:
    //   u_int32_t _lastTimePoint = 0;
    int _diff = 0;
    int _endDirection = 0;
    bool _upDown = true;
    float _distance = 0.0f;
    float _startDistance = 0.0f;
    float _xDistance = 0.0f;
public:
    int _exrange = 0;
    int _exdmg = 0;
    Hashbomb();

    Hashbomb(Hashbomb &p, SDL_FPoint target);

    void Render() override;

    void Update() override;

    void collide() override;

    bool collision(std::shared_ptr<Enemy> e) override;

    void addExplosion();
};

#endif //SDL_BACHELORDEFENDER_HASHBOMB_H

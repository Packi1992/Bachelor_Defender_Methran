
#ifndef SDL_BASEGAME_ENEMY_H
#define SDL_BASEGAME_ENEMY_H

#include "../global.h"
class Projectile;
class Enemy {
public:
    Enemy() = default;

    // move enemy -> status effects will impact here
    void Update(float deltaT);

    void Render(u32 totalMSec) const;
    void RenderExtras(bool life=false, bool hitBox=false) const;
    // use Enemy slot for new enemy spawn
    void setEnemy(Point pos, u16 Health, u8 speed, u8 value,EnemyType type = EnemyType::Ordinary);

    // setTile enemy speed -- maybe a buff or something else
    void setSpeed(u8 speed);

    // add slow effect for specific amount of _time in ms
    void setSlow(u8 speedDiff, uint16_t time);

    // stun _time in ms / enemy will not move
    void stun(u16 time);

    // take damage
    void takeDamage(Projectile * p);

    // status effects for Render decoration
    [[nodiscard]] bool isStunned() const;

    [[nodiscard]] bool isPoisoned() const;

    [[nodiscard]] bool isSlowed() const;

    [[nodiscard]] bool hasReachedGoal() const;

    EnemyType _type = EnemyType::Ordinary;

    // logical pixel pos
    u16 _dir = 0;
    bool _alive = false;

    u16 _health = 0;
    u16 _maxHealth = 0;

    // target where the enemy is heading
    FPoint _nextPos{};
    //pos on _map
    FPoint _pos = {};

    u16 _sanity = 1;

    // used to handle collision detection - is not necessarily same as dstRect
    [[nodiscard]] bool isPointInside(const FPoint &p) const;
    [[nodiscard]] FRect getHitBox() const;
protected:
    void startDeathAnimation();

    u16 _dying = false;


    u8 _speed = 0;
    u8 _speedDiff = 0;
    u8 _value = 0;

    u8 _poisonStrength = 0;
    float _stunTime = 0;
    float _slowTimer = 0;
    float _poisonTimer = 0;
    bool _reachedGoal = false;
    void updateDir();
};


#endif //SDL_BASEGAME_ENEMY_H

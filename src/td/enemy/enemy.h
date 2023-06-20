
#ifndef SDL_BASEGAME_ENEMY_H
#define SDL_BASEGAME_ENEMY_H

#include "../../global.h"
class Projectile;
class Enemy {
public:
    Enemy();
    Enemy(FPoint pos, uint16_t health, uint8_t speed, u8 value, EnemyType type);
    // move enemy -> status effects will impact here
    void Update();

    virtual void Render() const;
    void RenderExtras(bool life=false, bool hitBox=false) const;
    // use Enemy slot for new enemy spawn
    void setEnemy(Point pos, u16 Health, u8 speed, u8 value,EnemyType type = EnemyType::Ordinary);

    // setTile enemy speed -- maybe a buff or something else
    void setSpeed(u8 speed);

    // add slow effect for specific amount of _time in ms
    void setSlow(u8 speedDiff, uint16_t time);

    // stun _time in ms / enemy will not move
    void stun(u16 time);
    void stun(bool stun, bool hittable);

    // take damage
    void takeDamage(Projectile * p);
    bool isHittable();
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
    FPoint _pos = {0,0};

    u16 _sanity = 1;

    [[nodiscard]] virtual FRect getHitBox() const;

    bool _copyable = true;

protected:
    void startDeathAnimation();
    u_int32_t _lastTimePoint;
    u16 _dying = false;
    u8 _speed = 0;
    u8 _speedDiff = 0;
    u8 _value = 0;
    bool _hittable = true;
    u8 _poisonStrength = 0;
    u_int32_t _stunTime = 0;
    bool _forceStun = false;
    float _slowTimer = 0;
    float _poisonTimer = 0;
    bool _reachedGoal = false;
    void updateDir();

};

#include "smallemy.h"
#endif //SDL_BASEGAME_ENEMY_H

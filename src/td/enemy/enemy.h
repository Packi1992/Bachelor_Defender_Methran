
#ifndef SDL_BASEGAME_ENEMY_H
#define SDL_BASEGAME_ENEMY_H

#include "../../util/global.h"
class Projectile;
class Enemy {
public:
    Enemy();
    Enemy(std::shared_ptr<Enemy> e, bool recursiv = false);
    // move enemy -> status effects will impact here
    void Update();

    virtual void Render() const;
    void RenderExtras(bool life=false, bool hitBox=false) const;
    // use Enemy slot for new enemy spawn
    void setEnemy(Point pos, u16 Health, u8 speed, u8 value,EnemyType type = EnemyType::Ordinary, float size = 1.0f, uint copycount = 0);

    // setTile enemy speed -- maybe a buff or something else
    void setSpeed(u8 speed);

    // add slow effect for specific amount of _time in ms
    void setSlow(u8 speedDiff, uint16_t time);

    // stun _time in ms / enemy will not move
    void stun(u16 time);

    // take damage
    void takeDamage(Projectile * p);
    bool isRecursivable() const;
    // status effects for Render decoration
    [[nodiscard]] bool isStunned() const;

    [[nodiscard]] bool isPoisoned() const;

    [[nodiscard]] bool isSlowed() const;

    [[nodiscard]] bool hasReachedGoal() const;

    [[nodiscard]] bool isStunable() const;

    EnemyType _type = EnemyType::Ordinary;
    [[nodiscard]] bool isRow(float row) const;

    // logical pixel pos
    Direction _dir = TOP;
    bool _alive = false;

    u16 _health = 0;
    u16 _maxHealth = 0;

    // target where the enemy is heading
    FPoint _nextPos{};
    //pos on _map
    FPoint _pos = {0,0};

    u16 _sanity = 1;

    [[nodiscard]] virtual FRect getHitBox() const;

    virtual void collide();
    u8 _speed = 0;
    float _size = 1.0f;
    uint _copycount = 0;
    u8 _value = 0;

protected:
    bool _recursivable = true;
    u32 _animOffset = 0;
    int small = 0;
    void startDeathAnimation();
    u32 _lastTimePoint;
    u16 _dying = false;
    u8 _speedDiff = 0;
    u8 _poisonStrength = 0;
    int _stunTime = 0;
    int _stunCooldown = 4000;
    int _stunCooldownTimer = 0;
    float _slowTimer = 0;
    float _poisonTimer = 0;
    bool _stunable = true;
    bool _reachedGoal = false;
    void updateDir();

};

#endif //SDL_BASEGAME_ENEMY_H

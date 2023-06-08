 
#ifndef SDL_BASEGAME_ENEMY_H
#define SDL_BASEGAME_ENEMY_H

#include "../global.h"
#include "../gamebase.h"
#include "tdTileHandler.h"
#include "map.h"

enum EnemyType {
    Ordinary,
    Fast,
    Silly,
    Strong,
    Boss,
};

class Enemy {
public:
    Enemy() = default;

    // move enemy -> status effects will impact here
    void Update(const float deltaT );

    // use Enemy slot for new enemy spawn
    void setEnemy(Point pos, uint16_t Health, uint8_t speed, EnemyType type = Ordinary);
    // setTile enemy speed -- maybe a buff or something else
    void setSpeed(uint8_t speed);

    // add slow effect for specific amount of _time in ms
    void setSlow(uint8_t speedDiff, uint16_t time);

    // stun _time in ms / enemy will not move
    void stun(uint16_t time);

    // take damage
    void takeDamage(uint16_t damage);

    // status effects for Render decoration
    [[nodiscard]] bool isStunned() const;

    [[nodiscard]] bool isPoisend() const;

    [[nodiscard]] bool isSlowed() const;

    EnemyType _type = Ordinary;

    // logical pixel pos
    u16 _dir = 0;
    bool _alive = false;
    u16 _health = 0;
    u16 _maxHealth = 0;

    // target where the enemy is heading
    FPoint _nextPos{};
    //pos on _map
    FPoint _pos = {};

    // used to handle collision detection - is not necessarily same as dstRect
    [[nodiscard]] bool isPointInside(const FPoint &p) const;

protected:
    void startDeathAnimation();
    u16 _dying = false;


    u8 _speed = 0;
    u8 _speedDiff = 0;

    u8 _poisonStrength = 0;
    float _stunTime = 0;
    float _slowTimer = 0;
    float _poisonTimer = 0;

    void updateDir();
};


#endif //SDL_BASEGAME_ENEMY_H

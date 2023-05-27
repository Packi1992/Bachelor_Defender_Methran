
#ifndef SDL_BASEGAME_ENEMY_H
#define SDL_BASEGAME_ENEMY_H

#include "../global.h"
#include "../gamebase.h"
#include "tdTileHandler.h"
#include "map.h"

enum EnemyType{
    Ordinary,
    Fast,
    Silly,
    Strong,
    Boss,
};

class Enemy {
public:
    Enemy()= default;
    // Render enemy on map -> show status effects?
    void Render();

    // move enemy -> status effects will impact here
    void move();

    // indicates, if enemy is alive --> dead enemies are empty spots for new enemies
    bool isAlive();

    // use Enemy slot for new enemy spawn
    void setEnemy(Game *game,Map* map, Point pos, uint16_t Health, uint8_t speed,EnemyType type=Ordinary);

    // set enemy speed -- maybe a buff or something else
    void setSpeed(uint8_t speed);

    // add slow effect for specific amount of time in ms
    void setSlow(uint8_t speedDiff, uint16_t time);

    // stun time in ms / enemy will not move
    void stun(uint16_t time);

    // take damage
    bool takeDamage(uint16_t damage);

protected:
    void startDeathAnimation();
    bool _alive=false;
    uint16_t _dying=false;
    Point _pos={};
    std::uint16_t _dir=0;
    Point _nextPos{};

    Game *_pGame={};
    Map *_pMap={};

    ulong _lastMapTime = 0;
    std::uint16_t _stunTime = 0;
    std::uint16_t _health = 0;
    std::uint8_t _speed = 0;
    std::uint8_t _speedDiff = 0;
    std::uint16_t _slowTimer =0;
    EnemyType _type=Ordinary;
};


#endif //SDL_BASEGAME_ENEMY_H

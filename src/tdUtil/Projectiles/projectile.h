//
// Created by dex on 6/8/23.
//

#ifndef SDL_BACHELORDEFENDER_PROJECTILE_H
#define SDL_BACHELORDEFENDER_PROJECTILE_H

#include "../../global.h"
#include "../../gamebase.h"
#include "../enemy.h"

class Projectile {
public:
    enum Type {
        DISABLED = TdTileHandler::MapObjects::Empty,
        ARROW = TdTileHandler::MapObjects::ARROW,
        BULLET = TdTileHandler::MapObjects::BULLET,
        BASEEXPLOSION = TdTileHandler::MapObjects::BASEEXPLOSION,
        FFIRE = TdTileHandler::MapObjects::FFIRE,
    };
    bool _alive = false;
    FPoint _position = {-1, -1};
    Type _type = DISABLED;
    uint16_t _size = 100;
    uint16_t _speed = 100;
    uint16_t _direction = 270;
    bool _destroy = false;
    Enemy *_targetE = nullptr;
    FPoint _targetP = {0, 0};
    uint16_t _ttl = 1000;
    uint8_t _damage = 100;
    bool _moveable = false;

    virtual void move();
};


#endif //SDL_BACHELORDEFENDER_PROJECTILE_H

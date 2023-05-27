//
// Created by dex on 5/26/23.
//

#ifndef SDL_BACHELORDEFENDER_PROJECTILESHANDLER_H
#define SDL_BACHELORDEFENDER_PROJECTILESHANDLER_H

#include "../gamebase.h"
#include "../tdUtil/enemy.h"
#define MAXPROJECTILES 1000

class ProjectilesHandler{
public:
    struct Projectile {
        enum Type{
            DISABLED = TdTileHandler::MapObjects::Empty,
            ARROW = TdTileHandler::MapObjects::ARROW,
            BULLET = TdTileHandler::MapObjects::BULLET
        };
        bool _alive = false;
        Point _position = {-1,-1};
        Type _type = DISABLED;
        uint16_t _size = 100;
        uint16_t _speed = 100;
        uint16_t _direction = 0;
        bool _destroy = false;
        Enemy * _targetE = nullptr;
        Point _targetP = {0,0};
        uint16_t _ttl = 1000;
    };
    void Render( const u32 frame, const u32 totalMSec, const float deltaT );
    void move();
    Projectile _projectiles[MAXPROJECTILES];
    void add(Projectile p);
    void set();
private:
    uint overflow = 0;
    void moveBullet(Projectile * p);
    static void moveArrow(Projectile * p);
    Texture * _texture = nullptr;
    static bool onScreen(Point &posOnScreen, int &size);
};


#endif //SDL_BACHELORDEFENDER_PROJECTILESHANDLER_H

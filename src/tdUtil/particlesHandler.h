//
// Created by dex on 5/26/23.
//

#ifndef SDL_BACHELORDEFENDER_PARTICLESHANDLER_H
#define SDL_BACHELORDEFENDER_PARTICLESHANDLER_H
#include "../global.h"
#include "../gamebase.h"
#include "../tdUtil/enemy.h"
#define MAXPARTICLES 1000
class ParticlesHandler {
public:
    struct Particles {
        enum Type{
            DISABLED = TdTileHandler::MapObjects::Empty,
            BASEEXPLOSION = TdTileHandler::MapObjects::BASEEXPLOSION,
            FFIRE = TdTileHandler::MapObjects::FFIRE,
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
        uint16_t _ttl = 100;
        bool _moveable = false;
    };
    void Render( const u32 frame, const u32 totalMSec, const float deltaT );
    void move();
    Particles * getList(){ return _particles;};
    static uint getSize(){ return MAXPARTICLES;};
    void add(Particles p);
    void set();
private:
    Map * _map = nullptr;
    Particles _particles[MAXPARTICLES];
    uint overflow = 0;
    void moveFFire(Particles * p);
    Texture * _texture = nullptr;

    bool onScreen(Point &posOnScreen, int &size);
};


#endif //SDL_BACHELORDEFENDER_PARTICLESHANDLER_H

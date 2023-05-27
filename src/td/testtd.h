//
// Created by banoodle on 14.05.23.
//
#include "../global.h"
#include "../gamebase.h"
#include "../recthelper.h"
#include "../tdUtil/enemy.h"
#include "../tdUtil/tower.h"
#include "../tdUtil/projectilesHandler.h"
#include "../tdUtil/particlesHandler.h"

#ifndef SDL_BASEGAME_TESTTD_H
#define SDL_BASEGAME_TESTTD_H
using Projectile = ProjectilesHandler::Projectile;

class TestTD final: public GameState{
protected:
    Enemy enemyArr[100];
    Map _map;
    Tower* towerArr[50];
    ProjectilesHandler _ph;
    ParticlesHandler _prh;

    bool mbDown=false;
    bool mouseScroll=false;
public:
    // ctor
    using GameState::GameState;

    void Init() override;
    void UnInit() override;

    void Events( const u32 frame, const u32 totalMSec, const float deltaT ) override;
    void Update( const u32 frame, const u32 totalMSec, const float deltaT ) override;
    void Render( const u32 frame, const u32 totalMSec, const float deltaT ) override;

    void MouseDown(SDL_Event event);

    void MouseMotion(SDL_Event event);

    void MouseWheel(SDL_Event event);

    void keyDown(SDL_Event event);
};

#endif //SDL_BASEGAME_TESTTD_H

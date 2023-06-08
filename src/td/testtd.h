//
// Created by banoodle on 14.05.23.
//
#include "../global.h"
#include "../gamebase.h"
#include "../recthelper.h"
#include "../tdUtil/enemy.h"
#include "../tdUtil/tower.h"
#include "../tdUtil/projectilesHandler.h"
#include "../tdUtil/Projectiles/projectile.h"
#include "../tdUtil/Projectiles/arrow.h"
#include "../tdUtil/Projectiles/fire.h"
#include "../tdUtil/enemyHandler.h"
#include "../tdUtil/waveHandler.h"
#include "../tdUtil/player.h"
#include "../tdUtil/dataHandler.h"

#ifndef SDL_BASEGAME_TESTTD_H
#define SDL_BASEGAME_TESTTD_H
using Projectile = Projectile;

class TestTD final : public GameState {
protected:

    Map _map;
    Tower* towerArr[50];
    EnemyHandler _eh;
    ProjectilesHandler _ph;
    WaveHandler _wh;
    Player _pl;
    bool mbDown=false;
    bool mouseScroll=false;
    Point mousePos= {};
public:
    // ctor
    using GameState::GameState;

    void Init() override;
    void UnInit() override;

    void Events(const u32 frame, const u32 totalMSec, const float deltaT) override;
    void Update(const u32 frame, const u32 totalMSec, const float deltaT) override;
    void Render(const u32 frame, const u32 totalMSec, const float deltaT) override;

    void collision();

    void MouseDown(SDL_Event event);

    void MouseMotion(SDL_Event event);

    void MouseWheel(SDL_Event event);

    void keyDown(SDL_Event event);
};

#endif //SDL_BASEGAME_TESTTD_H

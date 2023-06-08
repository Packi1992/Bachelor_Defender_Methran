//
// Created by banoodle on 14.05.23.
//
#ifndef SDL_BASEGAME_TESTTD_H

#include "../global.h"
#include "../gamebase.h"
#include "../recthelper.h"
#include "../tdUtil/enemy.h"

#include "../tdUtil/projectilesHandler.h"
#include "../tdUtil/Projectiles/projectile.h"
#include "../tdUtil/Projectiles/arrow.h"
#include "../tdUtil/Projectiles/fire.h"
#include "../tdUtil/waveHandler.h"
#include "../tdUtil/player.h"
#include "../tdUtil/dataHandler.h"
#include "../tdUtil/coordinateTransformer.h"
#include "../tdUtil/tdTileHandler.h"

class Tower;
#define SDL_BASEGAME_TESTTD_H
#define MAXENEMIES 500
using CT = CoordinateTransformer;

class TestTD final : public GameState {
protected:
    Texture *_tileSheet = {};
    Map _map;

    int enemyOverflow = 0;
    void addEnemy(Enemy e);

    //  debug stuff
    bool mbDown = false;
    bool mouseScroll = false;
    Point mousePos = {};
public:
    struct TDglobals{
        Enemy _enemies[MAXENEMIES];
        ProjectilesHandler _ph;
        WaveHandler _wh;
        Vector<std::shared_ptr<Tower>> _towers{};
        Player _pl;
    };
    TDglobals globals;
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
#include "tower/tower.h"
#endif //SDL_BASEGAME_TESTTD_H

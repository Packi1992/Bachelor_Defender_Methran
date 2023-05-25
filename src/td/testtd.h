//
// Created by banoodle on 14.05.23.
//
#include "../global.h"
#include "../gamebase.h"
#include "../recthelper.h"
#include "../tdUtil/enemy.h"
#include "../tdUtil/tower.h"

#ifndef SDL_BASEGAME_TESTTD_H
#define SDL_BASEGAME_TESTTD_H

class TestTD final: public GameState{
protected:
    Enemy enemyArr[100];
    Map map;
    Tower* towerArr[50];
    Point offset={};
public:
    // ctor
    using GameState::GameState;

    void Init() override;
    void UnInit() override;

    void Events( const u32 frame, const u32 totalMSec, const float deltaT ) override;
    void Update( const u32 frame, const u32 totalMSec, const float deltaT ) override;
    void Render( const u32 frame, const u32 totalMSec, const float deltaT ) override;
};

#endif //SDL_BASEGAME_TESTTD_H

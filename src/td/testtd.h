//
// Created by banoodle on 14.05.23.
//
#ifndef SDL_BASEGAME_TESTTD_H
#define SDL_BASEGAME_TESTTD_H

#include "../gamebase.h"
#include "../enums.h"
#include "../tdUtil/enemy.h"
#include "../tdUtil/projectilesHandler.h"
#include "../tdUtil/waveHandler.h"
#include "../tdUtil/player.h"
#include "tower/tower.h"
#include "../tdUtil/map.h"
#include "../util/gui/floatingMenu.h"
class Gui;
struct TDGlobals {
    Enemy _enemies[MAXENEMIES]{};
    Vector<std::shared_ptr<class Tower>> _towers{};
    ProjectilesHandler _ph{};
    WaveHandler _wh{};
    Player _pl{};
};
extern TDGlobals *tdGlobals;

class TestTD final : public GameState {
protected:
    Rect Sanity{};
    Rect SanityBar{};
    Map _map;

    int enemyOverflow = 0;

    void addEnemy(Enemy e);

    //  debug stuff
    bool mbDown = false;
    bool mouseScroll = false;
    bool _btn_space = false;
    bool _btn_control = false;
    int _arrowDir = 0;
    Point mousePos = {};
public:
    // window handling
    Gui *focus= nullptr;
    FloatingMenu _floatingMenu;
    Vector<MenuEntries> _buildMenuEntries{};
    TDGlobals globals;
    // ctor
    using GameState::GameState;

    void Init() override;

    void UnInit() override;

    void Events(const u32 frame, const u32 totalMSec, const float deltaT) override;

    void Update(const u32 frame, const u32 totalMSec, const float deltaT) override;

    void Render(const u32 frame, const u32 totalMSec, const float deltaT) override;

    void collision();

    void MouseDown(SDL_Event &event);

    void MouseMotion(SDL_Event &event);

    void MouseWheel(SDL_Event &event);

    void keyDown(SDL_Event &event);
};

#endif //SDL_BASEGAME_TESTTD_H

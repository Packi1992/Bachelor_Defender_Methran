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
#include "../util/gui/TextWithValue.h"

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
    Texture *_texMethran{};
    Rect MethranDst{};
    Rect Sanity{};
    Rect SanityBar{};
    Rect _menuBot{};
    Map _map;

    int enemyOverflow = 0;

    void addEnemy(Enemy e);

    void buyTower(Gui **focus);

    //  debug stuff
    int _arrowDir = 0;

    //  buttons & events
    bool _btn_space = false;
    bool _btn_control = false;
    bool _mbLeft = false;
    bool _mbRight = false;
    bool _mouseWheel = false;
    SDL_Event _wheelEvent{};
    bool _mouseMotion = false;
    SDL_Event _motionEvent{};

    // ui
    Gui *focus{};
    FloatingMenu _floatingMenu;
    TextWithValue _creditPointDisplay;
public:
    // window handling

    Vector<MenuEntry> _buildMenuEntries{};
    TDGlobals globals{};

    // ctor
    using GameState::GameState;

    void Init() override;

    void UnInit() override;

    void Events() override;

    void Update() override;

    void Render() override;

    void collision();

    void updateUI();

    void keyDown(SDL_Event &event);

    void updateFloatingMenu();

    bool buyTower(const std::shared_ptr<class Tower> &tower);

    void handleFloatingMenuSelection();

    void updateTowers();
};

#endif //SDL_BASEGAME_TESTTD_H

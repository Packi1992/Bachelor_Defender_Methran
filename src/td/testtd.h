//
// Created by banoodle on 14.05.23.
//
#ifndef SDL_BASEGAME_TESTTD_H
#define SDL_BASEGAME_TESTTD_H

#include "../util/gamebase.h"
#include "../util/enums.h"
#include "enemy/enemy.h"
#include "enemy/dr�berbolz.h"
#include "enemy/froleP�hlich.h"
#include "../tdUtil/waveHandler.h"
#include "../tdUtil/player.h"
#include "tower/tower.h"
#include "../tdUtil/map.h"
#include "../util/gui/floatingMenu.h"
#include "../util/gui/TextWithValue.h"

class Gui;

struct TDGlobals {
    Gui *_focus{};
    Vector<std::shared_ptr<Enemy>> _enemies{};
    Vector<std::shared_ptr<class Tower>> _towers{};
    Vector<std::shared_ptr<Projectile>> _projectiles{};
    WaveHandler _wh{};
    Player _pl{};
    string *_mapPath{};
    void setPath(string newMapPath);
    bool editor = false;
    ~TDGlobals(){
        delete _mapPath;
    }

    bool isEnemyBlocking(FPoint tile);
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
    bool _renderPath = false;

    // ui
    FloatingMenu _floatingMenu;
    TextWithValue _creditPointDisplay;
public:
    // window handling

    Vector<MenuEntry> _buildMenuEntries{};
    TDGlobals globals{};

    // ctor
    using GameState::GameState;
    TestTD(Game &game, string mapPath);

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

    void updateProjectiles();

    void updateEnemeies();

    void handleEvent(const GameEvent& event);
};

#endif //SDL_BASEGAME_TESTTD_H

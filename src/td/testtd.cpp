//
// Created by banoodle on 14.05.23.
//
#include "testtd.h"
#include "../tdUtil/dataHandler.h"
#include "../td/Projectiles/arrow.h"
#include "../td/Projectiles/boomerang.h"

TDGlobals *tdGlobals{};

void TestTD::Init() {
    GameState::Init();
    pGame = &game;
    pMap = &_map;
    DataHandler::load(globals._pl, globals._wh, _map);
    globals._ph.set();
    tdGlobals = &globals;
    _creditPointDisplay.set("Credit Points :", reinterpret_cast<const int *>(&globals._pl._creditPoints), {windowSize.x - 200, windowSize.y - 100}, 20, BLACK);
}

void TestTD::UnInit() {
    GameState::UnInit();
    for (auto &enemy: globals._enemies) {
        enemy._alive = false;
    }
    globals._towers.clear();
    audioHandler->stopMusic();
}

void TestTD::Render(u32 frame, u32 totalMSec, float deltaT) {
    // Background
    rh->background(BG);
    // Map
    _map.Render(totalMSec,true);
    // Tower
    for (auto &tower: globals._towers) {
        tower->Render(deltaT);
    }
    //  render Enemies
    for (auto &enemy: globals._enemies) {
        enemy.Render(totalMSec);
    }
    // projectiles and particles
    globals._ph.Render(totalMSec);
    // render enemy extras (lifeBar or hitBox)
    for (auto &enemy: globals._enemies) {
        enemy.RenderExtras(true);
    }
    // at last render UI
    rh->fillRect(&SanityBar, RED);
    rh->fillRect(&Sanity, GREEN);
    rh->rect(&SanityBar, 4, BLACK);
    // Menu
    for (auto &tower: globals._towers) {
        tower->RenderMenu(deltaT);
    }
    _creditPointDisplay.draw();
    _floatingMenu.Render();

}

void TestTD::addEnemy(Enemy e) {
    for (auto &enemy: globals._enemies) {
        if (!enemy._alive) {
            enemy = e;
            enemy._alive = true;
            return;
        }
    }
    if (enemyOverflow >= MAXENEMIES)
        enemyOverflow = 0;
    globals._enemies[enemyOverflow] = e;
    globals._enemies[enemyOverflow++]._alive = true;
}

void TestTD::Update(const u32 frame, const u32 totalMSec, const float deltaT) {
    _floatingMenu.Update();
    if (_floatingMenu.isDone()) {
        Point pos = {(int) _floatingMenu.getPos().x, (int) _floatingMenu.getPos().y};
        switch (_floatingMenu.getSelectedEntry()) {
            case MenuEntry_DEFAULT:
                break;
            case MenuEntry_POINTER:
            {
                std::shared_ptr<class Tower> tower = std::make_shared<PointerTower>(pos);
                if(globals._pl.buyTower(tower)){
                    globals._towers.push_back(tower);
                }
                _floatingMenu.reset();
                break;
            }

            case MenuEntry_Error:
                break;
            default:
                break;
        }
    }
    // collision detection
    collision();
    // Update Enemies
    for (auto &enemy: globals._enemies) {
        if (enemy._alive) {
            enemy.Update(deltaT);
        }
    }
    // calculate sanity bar (only every 10 frames)
    if (frame % 10 == 0) {
        SanityBar = {windowSize.x - 100, (int) (windowSize.y * 0.1), 50, (int) (windowSize.y * 0.7)};
        int sanity_left = (int) ((float) SanityBar.h *
                                 ((float) globals._pl._sanity / (float) globals._pl._maxSanity));
        Sanity = SanityBar;
        Sanity.y += SanityBar.h - sanity_left;
        Sanity.h = sanity_left;
    }
    // Update towers
    for (auto &tower: globals._towers) {
        tower->Update(deltaT);
        if(tower->isDead()){
            globals._towers.erase(
                    std::remove_if(
                            globals._towers.begin(),
                            globals._towers.end(),
                            [](const std::shared_ptr<class::Tower> &mov) { return mov->isDead(); }
                    ),
                    globals._towers.end());
        }
    }
    // update projectiles
    globals._ph.move();
    // update "Viewport" / Zoom in or Out / Scroll
    if(_mouseWheel){
        Game::zoomScreen(_wheelEvent);
        _mouseWheel = false;
    }
    if(_mouseMotion && _mbRight){
        Game::scrollScreen(_motionEvent);
        _mouseMotion = false;
    }

    // ---- DEV -------------------------------------
    // add projectiles and particles
    // update projectile direction
    if (_btn_space) {
        _arrowDir = (_arrowDir + 5) % 360;
        _btn_space = false;
    }
    if (_btn_control) {
        Point cursor;
        SDL_GetMouseState(&cursor.x,&cursor.y);
        auto *p = new Arrow();
        p->_direction = _arrowDir;
        p->_position = CT::getPosInGame(cursor);
        p->_speed = 1;
        globals._ph.add(p);
        Fire *f = new Fire();
        f->_direction = _arrowDir;
        f->_position = CT::getPosInGame(cursor);
        f->_speed = 1;
        f->_moveable = true;
        f->_ttl = 80;
        //globals._ph.add(f);
        _btn_control = false;
    }
    if (_mbLeft) {
        bool clickTower = false;
        Point cursor;
        SDL_GetMouseState(&cursor.x,&cursor.y);
        for (auto &t: globals._towers) {
            if (t->isClicked(cursor)) {
                t->showMenu(&focus);
                clickTower = true;
                break;
            }
        }
        if (!clickTower) {
            switch (pMap->getObjectAtScreenPos(cursor)) {
                case Empty:
                case Table:
                    // show build menu
                    _floatingMenu.reset();
                    updateFloatingMenu();
                    _floatingMenu.set(&_buildMenuEntriesInfos, CT::getTileCenterInGame(cursor));
                    _floatingMenu.show(&focus);
                    break;
                default:
                    break;
            }
        }
        _mbLeft = false;
    }
    // add enemy
    if (totalMSec % 100 == 0) {
        Enemy e;
        e.setEnemy({7, 3}, 100, 100,1);
        addEnemy(e);
    }
    // -------------------------------------------------------------------
}

void TestTD::collision() {
    for (auto &e: globals._enemies) {
        if (e._alive) {
            for (auto &p: globals._ph._projectiles) {
                if (p != nullptr) {
                    if (p->_alive) {
                        if (e.isPointInside(p->_position)) {
                            e.takeDamage(p->_damage);
                            globals._ph.remove(&p);
                            if (!e._alive) {
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

void TestTD::Events(const u32 frame, const u32 totalMSec, const float deltaT) {
    if (focus == nullptr) {

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (pGame->HandleEvent(event))
                return;
            switch (event.type) {
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                        game.SetNextState(99);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_RIGHT)
                        _mbRight = true;
                    if (event.button.button == SDL_BUTTON_LEFT)
                        _mbLeft = true;
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_RIGHT && _mbRight)_mbRight = false;
                    break;
                case SDL_MOUSEMOTION:
                    _mouseMotion = true;
                    _motionEvent = event;
                    break;
                case SDL_MOUSEWHEEL:
                    _wheelEvent = event;
                    _mouseWheel = true;
                    break;
                case SDL_KEYDOWN:
                    keyDown(event);
                    break;
            }
        }
    } else {
        focus->Input();
    }
}

void TestTD::keyDown(SDL_Event &event) {
    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_ESCAPE:
            game.SetNextState(0);
            break;
        case SDL_SCANCODE_D:
        case SDL_SCANCODE_RIGHT:
            offset.x += 20;
            break;
        case SDL_SCANCODE_A:
        case SDL_SCANCODE_LEFT:
            offset.x -= 20;
            break;
        case SDL_SCANCODE_W:
        case SDL_SCANCODE_UP:
            offset.y -= 20;
            break;
        case SDL_SCANCODE_S:
        case SDL_SCANCODE_DOWN:
            offset.y += 20;
            break;
        case SDL_SCANCODE_SPACE:
            _btn_space = true;
            break;
        case SDL_SCANCODE_RCTRL:
        case SDL_SCANCODE_LCTRL:
            _btn_control = true;
        default:
            break;
    }
}

void TestTD::updateFloatingMenu() {
    _buildMenuEntriesInfos.clear();
    MenuEntry pointerTower{MenuEntries::MenuEntry_POINTER, Status_Active, 5};
    if(globals._pl._creditPoints < 5) pointerTower._status = Status_NotEnoughMoney;
    if(!pMap->checkPath(CT::getMousePosTile())) pointerTower._status = Status_Disabled;
    _buildMenuEntriesInfos.push_back(pointerTower);
    //_buildMenuEntriesInfos.push_back({MenuEntry_Error, Status_Active, 0});
    //_buildMenuEntriesInfos.push_back({MenuEntry_Disabled, Status_Active, 0});
   /* _buildMenuEntriesInfos.push_back({MenuEntry_DEFAULT, Status_Active, 0});
    _buildMenuEntriesInfos.push_back({MenuEntry_POINTER, Status_Active, 0});
    _buildMenuEntriesInfos.push_back({MenuEntry_BOOMERANG, Status_Active, 0});
    _buildMenuEntriesInfos.push_back({MenuEntry_Disabled, Status_Active, 0});*/

}
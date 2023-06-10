//
// Created by banoodle on 14.05.23.
//
#include "testtd.h"
#include "../tdUtil/dataHandler.h"
#include "../td/Projectiles/arrow.h"

TDGlobals *tdGlobals{};

void TestTD::Init() {
    GameState::Init();
    pGame = &game;
    pMap = &_map;
    DataHandler::load(globals._pl, globals._wh, _map);
    globals._ph.set();
    tdGlobals = &globals;
    _buildMenuEntriesInfos.push_back({MenuEntry_DEFAULT, Status_Active, 0});
    _buildMenuEntriesInfos.push_back({MenuEntry_POINTER, Status_Active, 0});
    _buildMenuEntriesInfos.push_back({MenuEntry_Error, Status_Active, 0});
    _buildMenuEntriesInfos.push_back({MenuEntry_Disabled, Status_Active, 0});
    _creditPointDisplay.set("Credit Points :", reinterpret_cast<const int *>(&globals._pl._creditPoints), {windowSize.x - 200, windowSize.y - 100}, 20, BLACK);
}

void TestTD::UnInit() {
    GameState::UnInit();
    for (auto &enemy: globals._enemies) {
        enemy._alive = false;
    }
    audioHandler->stopMusic();
}

void TestTD::Render(u32 frame, u32 totalMSec, float deltaT) {
    // Background
    rh->background(BG);
    // Map
    _map.Render(true);
    // Tower
    for (auto &tower: globals._towers) {
        tower->Render(deltaT);
    }
    //  render Enemies
    for (auto &enemy: globals._enemies) {
        enemy.Render(totalMSec,true);
    }
    // projectiles and particles
    globals._ph.Render(totalMSec);

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
    collision();
    // Update Enemies
    for (auto &enemy: globals._enemies) {
        if (enemy._alive) {
            enemy.Update(deltaT);
        }
    }
    // calculate sanity bar only every 10 frames
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
    globals._ph.move();

    // add projectiles and particles
    // update projectile direction
    if (_btn_space) {
        _arrowDir = (_arrowDir + 5) % 360;
        _btn_space = false;
    }
    if (_btn_control) {
        auto *p = new Arrow();
        p->_direction = _arrowDir;
        p->_position = CT::getPosInGame(mousePos);
        p->_speed = 1;
        globals._ph.add(p);
        Fire *f = new Fire();
        f->_direction = _arrowDir;
        f->_position = CT::getPosInGame(mousePos);
        f->_speed = 1;
        f->_moveable = true;
        f->_ttl = 80;
        //globals._ph.add(f);
        _btn_control = false;
    }
    if (mbDown) {
        bool clickTower = false;
        for (auto &t: globals._towers) {
            if (t->isClicked(mousePos)) {
                t->showMenu(&focus);
                clickTower = true;
                break;
            }
        }
        if (!clickTower) {
            switch (pMap->getObjectAtScreenPos(mousePos)) {
                case Empty:
                case Table:
                    // show build menu
                    _floatingMenu.reset();
                    updateFloatingMenu();
                    _floatingMenu.set(&_buildMenuEntriesInfos, CT::getTileCenterInGame(mousePos));
                    _floatingMenu.show(&focus);
                    break;
                default:
                    break;
            }
        }
        mbDown = false;

    }
    // add enemy
    if (totalMSec % 100 == 0) {
        Enemy e;
        e.setEnemy({7, 3}, 100, 100,1);
        addEnemy(e);
    }
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
                    MouseDown(event);
                    break;
                case SDL_MOUSEBUTTONUP:
                    mbDown = false;
                    if (event.button.button == SDL_BUTTON_RIGHT && mouseScroll)mouseScroll = false;
                    break;
                case SDL_MOUSEMOTION:
                    MouseMotion(event);
                    break;
                case SDL_MOUSEWHEEL:
                    MouseWheel(event);
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

void TestTD::MouseDown(SDL_Event &event) {
    if (event.button.button == SDL_BUTTON_RIGHT) {
        mouseScroll = true;
    }
    if (event.button.button == SDL_BUTTON_LEFT) {
        mbDown = true;
        mousePos = {event.motion.x, event.motion.y};
    }
}

void TestTD::MouseMotion(SDL_Event &event) {
    if (mouseScroll) {
        offset.x -= event.motion.xrel;
        offset.y -= event.motion.yrel;
    }
}

void TestTD::MouseWheel(SDL_Event &event) {
    Point cursor{};
    SDL_GetMouseState(&cursor.x, &cursor.y);
    if (event.wheel.y / abs(event.wheel.y) < 1) {// zoom out
        scale = (int) (scale * 0.8);
    } else {                                     // zoom in
        scale = (int) (scale * (1 / 0.8));
        offset.y += 2 * event.wheel.y / abs(event.wheel.y) * _map._height / 2;
        offset.x += 2 * event.wheel.y / abs(event.wheel.y) * _map._width / 2;
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
    if(globals._pl._creditPoints < 5){
        _buildMenuEntriesInfos.at(1)._status = Status_NotEnoughMoney;
    }else{
        _buildMenuEntriesInfos.at(1)._status = Status_Active;
    }
    if(!pMap->checkPath(CT::getTileInGame(mousePos))){
        _buildMenuEntriesInfos.at(1)._status = Status_Disabled;
    }
}
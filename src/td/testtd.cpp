//
// Created by banoodle on 14.05.23.
//
#include "testtd.h"

#include <utility>
#include "../util/dataHandler.h"
#include "../td/projectiles/arrow.h"

TDGlobals *tdGlobals{};

void TestTD::Init() {
    GameState::Init();
    pGame = &game;
    pMap = &_map;
    DataHandler::load(globals._pl, globals._wh, _map,BasePath"Maps/"+_mapPath);
    tdGlobals = &globals;
    _creditPointDisplay.set("Credit Points :", reinterpret_cast<const int *>(&globals._pl._creditPoints),
                            {windowSize.x - 200, windowSize.y - 100}, 20, BLACK);
    _texMethran = t_cache->get(BasePath"asset/graphic/methran1.png");
    SDL_QueryTexture(_texMethran, nullptr, nullptr, &MethranDst.w, &MethranDst.h);
    //globals._pl._sanity = 10;
    updateUI();
    Update();
}

void TestTD::UnInit() {
    GameState::UnInit();
    for (auto &enemy: globals._enemies) {
        enemy._alive = false;
    }
    globals._towers.clear();
    audioHandler->stopMusic();
}

void TestTD::Render() {
    // Background
    rh->background(BG);
    // Map
    _map.Render(true);
    // Tower
    for (auto &tower: globals._towers) {
        tower->Render();
    }
    //  render Enemies
    for (auto &enemy: globals._enemies) {
        enemy.Render();
    }
    // projectiles and particles
    for (auto &p: tdGlobals->_projectiles) {
        if (p != nullptr) {
            p->Render();
        }
    }

    // render enemy extras (lifeBar or hitBox)
    for (auto &enemy: globals._enemies) {
        enemy.RenderExtras(true);
    }
    // at last render UI
    rh->fillRect(&SanityBar, RED);
    rh->fillRect(&Sanity, GREEN);
    rh->rect(&SanityBar, 4, BLACK);
    // Methran
    rh->texture(_texMethran, &MethranDst);
    // Menu
    rh->fillRect(&_menuBot, EDITOR_UI_BG);
    for (auto &tower: globals._towers) {
        tower->RenderMenu();
    }
    _creditPointDisplay.draw();
    _floatingMenu.Render();
    if (_gameover) {
        rh->background(BLACK, 128);
        rh->CenteredText("Game Over", 70, RED, windowSize.x, windowSize.y);
    }
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

void TestTD::Update() {
    if (!_gameover) {
        _floatingMenu.Update();
        handleFloatingMenuSelection();

        // collision detection
        collision();
        // Update Enemies
        for (auto &enemy: globals._enemies) {
            if (enemy._alive) {
                enemy.Update();
            }
        }
        // calculate sanity bar (only every 10 frames)
        if (frameg % 10 == 0) {
            updateUI();
        }
        //checking for death
        _gameover = globals._pl._sanity <= 0;
        // Update towers
        updateTowers();
        // update projectiles
        updateProjectiles();

        // update "Viewport" / Zoom in or Out / Scroll
        if (_mouseWheel) {
            Game::zoomScreen(_wheelEvent);
            _mouseWheel = false;
        }
        if (_mouseMotion && _mbRight) {
            Game::scrollScreen(_motionEvent);
            _mouseMotion = false;
        }
        // input handling
        if (_mbLeft) {
            bool clickTower = false;
            Point cursor;
            SDL_GetMouseState(&cursor.x, &cursor.y);
            for (auto &t: globals._towers) {
                if (t->isClicked(cursor)) {
                    t->showMenu(&globals._focus);
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
                        _floatingMenu.set(&_buildMenuEntries, CT::getTileCenterInGame(cursor));
                        _floatingMenu.show(&globals._focus);
                        break;
                    default:
                        break;
                }
            }
            _mbLeft = false;
        }
        // add enemy
        if (totalMscg % 100 == 0) {
            Enemy e;
            e.setEnemy({7, 3}, 100, 100, 1);
            addEnemy(e);
        }
        // -------------------------------------------------------------------
    }
}

void TestTD::collision() {
    for (auto &p: globals._projectiles) {
        if (p->_alive) {
            for (auto &e: globals._enemies) {
                if (e._alive && p->collision(&e) && p->_alive) {
                    p->collide();
                }
            }
        }
    }
}

void TestTD::Events() {
    if (globals._focus == nullptr) {
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
        globals._focus->Input();
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
    _buildMenuEntries.clear();
    MenuEntry linkedListTower{MenuEntry_LinkedList, Status_Active, 10};
    MenuEntry pointerTower{MenuEntry_POINTER, Status_Active, 5};
    MenuEntry recursiveTower{MenuEntry_BOOMERANG, Status_Active, 5};
    if (!pMap->checkPath(CT::getMousePosTile())) {
        pointerTower._status = Status_Disabled;
        recursiveTower._status = Status_Disabled;
        linkedListTower._status = Status_Disabled;
    }
    _buildMenuEntries.push_back(pointerTower);
    _buildMenuEntries.push_back(linkedListTower);
    _buildMenuEntries.push_back(recursiveTower);
}



void TestTD::updateUI() {
    SanityBar = {windowSize.x - 100, (int) (windowSize.y * 0.1), 50, (int) (windowSize.y * 0.7)};
    float fSanity = ((float) globals._pl._sanity / (float) globals._pl._maxSanity);
    int sanity_left = (int) ((float) SanityBar.h * fSanity);
    Sanity = SanityBar;
    Sanity.y += SanityBar.h - sanity_left;
    Sanity.h = sanity_left;
    // calculate Methran Size
    float MethrannScaleFactor = 0.35f * (float) windowSize.y / (float) MethranDst.h;
    MethranDst.w = (int) (MethrannScaleFactor * (float) MethranDst.w);
    MethranDst.h = (int) (MethrannScaleFactor * (float) MethranDst.h);
    MethranDst.x = windowSize.x - MethranDst.w - 100;
    MethranDst.y = windowSize.y - MethranDst.h - 100;
    if (fSanity <= 0.1f) {
        MethranDst.x += ((int) totalMscg / 100) % 20 * ((((int) totalMscg % 3) == 1) ? (-1) : 1);
        MethranDst.y += ((int) totalMscg / 100) % 20 * ((((int) totalMscg % 2) == 1) ? (-1) : 1);
    }
    // calculate Menu Size
    _menuBot = {0, windowSize.y - 150, windowSize.x, 150};
}

void TestTD::handleFloatingMenuSelection() {
    if (_floatingMenu.isDone()) {
        Point pos = {(int) _floatingMenu.getPos().x, (int) _floatingMenu.getPos().y};
        switch (_floatingMenu.getSelectedEntry()) {
            case MenuEntry_DEFAULT:
                break;
            case MenuEntry_POINTER: {
                std::shared_ptr<class Tower> tower = std::make_shared<PointerTower>(pos);
                if (buyTower(tower)) {
                    globals._towers.push_back(tower);
                }
                _floatingMenu.reset();
                break;
            }
            case MenuEntry_LinkedList: {
                std::shared_ptr<class Tower> tower = std::make_shared<LinkedListTower>(pos);
                if (buyTower(tower)) {
                    globals._towers.push_back(tower);
                }

                _floatingMenu.reset();
                break;
            }
            case MenuEntry_BOOMERANG: {
                std::shared_ptr<class Tower> tower = std::make_shared<RecursivTower>(pos);
                if (buyTower(tower)) {
                    globals._towers.push_back(tower);
                }
                _floatingMenu.reset();
                break;
            }
            case MenuEntry_Error:
            default:
                break;
        }
    }
}

void TestTD::updateTowers() {
    for (int i = 0; i < (int) globals._towers.size(); i++) {
        globals._towers.at(i)->Update();
        if (globals._towers.at(i)->isDead()) {
            globals._towers.erase(
                    std::remove_if(
                            globals._towers.begin(),
                            globals._towers.end(),
                            [](const std::shared_ptr<class Tower> &mov) { return mov->isDead(); }
                    ),
                    globals._towers.end());
        }
    }
}

void TestTD::updateProjectiles() {
    for (auto & _projectile : globals._projectiles) {
        _projectile->Update();
    }
    globals._projectiles.erase(
            std::remove_if(
                    globals._projectiles.begin(),
                    globals._projectiles.end(),
                    [](const std::shared_ptr<Projectile> &mov) { return !mov->_alive; }
            ),
            globals._projectiles.end());
}


bool TestTD::buyTower(const std::shared_ptr<class Tower> &tower) {
    if (tower->getCosts() > globals._pl._creditPoints) {
        return false;
    }
    if (tower->init(&tdGlobals->_focus)) {
        globals._pl._creditPoints -= tower->getCosts();
        return true;
    }
    return false;
}

TestTD::TestTD(Game &game, string mapPath): GameState(game) {
    _mapPath = std::move(mapPath);
}

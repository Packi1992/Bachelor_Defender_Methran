//
// Created by banoodle on 14.05.23.
//
#include "testtd.h"

#include <utility>
#include "../util/dataHandler.h"

TDGlobals *tdGlobals{};

void TestTD::Init() {
    GameState::Init();
    DataHandler::load(globals._pl, globals._wh, _map, BasePath"Maps/" + *(tdGlobals->_mapPath));
    _creditPointDisplay.set("Credit Points :", reinterpret_cast<const int *>(&globals._pl._creditPoints),
                            {windowSize.x - 200, windowSize.y - 100}, 20, BLACK);

    // use wave handler
    Wave w1;
    GameEvent se{};
    GameEvent boss{};
    se.time = 1000;
    se.SpawnPoint = 0;
    se.count = 1;
    se.speed = 100;
    se.type = Ordinary;
    for (int i = 0; i <= 10; i++) {
        se.time += 500;
        w1.addEvent(se);
    }
    boss.time = se.time + 3000;
    boss.SpawnPoint = 0;
    boss.count = 1;
    boss.speed = 200;
    boss.health = 20;
    boss.type = Boss_Drueberbolz;
    w1.addEvent(boss);

    se.SpawnPoint = 1;
    se.health += 50;
    se.time = 1000;
    Wave w2;
    for (int i = 0; i <= 20; i++) {
        se.time += 500;
        w2.addEvent(se);
    }
    boss.time = se.time + 3000;
    boss.SpawnPoint = 1;
    boss.type = Boss_Frohle_Poehlich;
    boss.health += 100;
    w2.addEvent(boss);

    se.SpawnPoint = 0;
    Wave w3;
    se.health += 100;
    se.time = 1000;
    for (int i = 0; i <= 25; i++) {
        se.time += 500;
        w3.addEvent(se);
    }
    boss.time = se.time + 3000;
    boss.SpawnPoint = 0;
    boss.type = Boss_Frohle_Poehlich;
    boss.health += 100;
    w3.addEvent(boss);

    se.SpawnPoint = 1;
    Wave w4;
    se.health += 200;
    se.time = 1000;
    for (int i = 0; i <= 20; i++) {
        se.time += 500;
        w4.addEvent(se);
    }
    boss.time = se.time + 1000;
    boss.SpawnPoint = 1;
    boss.type = Boss_Drueberbolz;
    boss.health += 100;
    w4.addEvent(boss);

    se.SpawnPoint = 0;
    Wave w5;
    se.health += 300;
    se.time = 1000;
    for (int i = 0; i <= 100; i++) {
        se.time += 500;
        w5.addEvent(se);
    }
    boss.time = se.time + 1000;
    boss.SpawnPoint = 0;
    boss.type = Boss_Frohle_Poehlich;
    boss.health += 100;
    w5.addEvent(boss);

    globals._wh.addWave(w1);
    globals._wh.addWave(w2);
    globals._wh.addWave(w3);
    globals._wh.addWave(w4);
    globals._wh.addWave(w5);
    globals._wh.init();
    updateUI();
    Update();
    //globals._pl._creditPoints=10000;
}

void TestTD::UnInit() {
    GameState::UnInit();
    globals._towers.clear();
    globals._projectiles.clear();
    globals._enemies.clear();
    audioHandler->stopMusic();
    globals._wh.reset();
}

void TestTD::Render() {
    // Background
    rh->background(BG);
    // Map
    _map.RenderBG(true);
    for (int y = 0; y < _map._height; y++) {
        _map.RenderRow(y);
        if (_renderPath)
            _map.RenderPathRow(y);
        // Tower
        for (auto &tower: globals._towers) {
            if (tower->isRow(y))
                tower->Render();
        }
    }

    //  render Enemies
    for (int i = 0; i < (_map._height) * 10; i++) {
        for (auto &enemy: globals._enemies) {
            if (enemy->isRow((float) i * 0.1f))
                enemy->Render();
        }
    }



    // projectiles and particles
    for (auto &p: tdGlobals->_projectiles) {
        if (p != nullptr) {
            p->Render();
        }
    }

    // render enemy extras (lifeBar or hitBox)
    for (auto &enemy: globals._enemies) {
        enemy->RenderExtras(true);
    }
    // at last render UI
    globals._wh.Render();
    rh->fillRect(&SanityBar, RED);
    rh->fillRect(&Sanity, GREEN);
    rh->rect(&SanityBar, 4, BLACK);
    // Methran
    rh->texture(_texMethran, &MethranDst);
    // Menu
    rh->fillRect(&_menuBot, EDITOR_UI_BG);
    _creditPointDisplay.draw();
    for (auto &tower: globals._towers) {
        tower->RenderMenu();
    }
    _floatingMenu.Render();
    if (_gameover) {
        rh->background(BLACK, 128);
        rh->CenteredText("Game Over", 70, RED, windowSize.x, windowSize.y);
    }
    if (!_gameover && globals._wh.isOver()) {
        rh->background(BLACK, 128);
        rh->CenteredText("Congraz, Du hast gewonnen!", 70, GREEN, windowSize.x, windowSize.y);
    }
}

void TestTD::Update() {
    if (!_gameover && !globals._wh.isOver()) {
        _floatingMenu.Update();
        handleFloatingMenuSelection();

        // collision detection
        collision();
        // Update Enemies
        updateEnemeies();

        // Handle new enemies
        globals._wh.Update();
        GameEvent sEvent;
        while (globals._wh.pullEvent(sEvent)) {
            handleEvent(sEvent);
        }
        // calculate sanity bar (only every 10 frames)
        if (frame % 10 == 0) {
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
    }
}

void TestTD::collision() {
    for (auto &p: globals._projectiles) {
        if (p->_alive) {
            for (int i = 0; i < globals._enemies.size(); i++) {
                if (globals._enemies.at(i)->_alive && p->collision(globals._enemies.at(i)) && p->_alive) {
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
                        game.SetNextState(GS_Close);
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
                case SDL_KEYUP:
                    if (event.key.keysym.scancode == SDL_SCANCODE_P)
                        _renderPath = false;
            }
        }
    } else {
        globals._focus->Input();
    }
}

void TestTD::keyDown(SDL_Event &event) {
    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_ESCAPE:
            if (globals.editor)
                game.SetNextState(GS_Editor);
            else
                game.SetNextState(GS_MainMenu);
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
        case SDL_SCANCODE_P:
            _renderPath = true;
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
    MenuEntry hashCanon{MenuEntry_HASHCANON, Status_Active, 5};
    MenuEntry stringTower{MenuEntry_STRINGTOWER, Status_Active, 3};
    if (!pMap->checkPath(CT::getMousePosTile())) {
        pointerTower._status = Status_Disabled;
        recursiveTower._status = Status_Disabled;
        linkedListTower._status = Status_Disabled;
        hashCanon._status = Status_Disabled;
        stringTower._status = Status_Disabled;
    }
    for (auto &entry: globals._pl._usableTowers) {
        switch (entry) {
            case MenuEntry_POINTER:
                _buildMenuEntries.push_back(pointerTower);
                break;
            case MenuEntry_BOOMERANG:
                _buildMenuEntries.push_back(recursiveTower);
                break;
            case MenuEntry_LinkedList:
                _buildMenuEntries.push_back(linkedListTower);
                break;
            case MenuEntry_HASHCANON:
                _buildMenuEntries.push_back(hashCanon);
                break;
            case MenuEntry_STRINGTOWER:
                _buildMenuEntries.push_back(stringTower);
                break;
            default:
                break;
        }
    }
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
        MethranDst.x += ((int) totalMSec / 100) % 20 * ((((int) totalMSec % 3) == 1) ? (-1) : 1);
        MethranDst.y += ((int) totalMSec / 100) % 20 * ((((int) totalMSec % 2) == 1) ? (-1) : 1);
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
            case MenuEntry_HASHCANON: {
                std::shared_ptr<class Tower> tower = std::make_shared<HashCanon>(pos);
                if (buyTower(tower)) {
                    globals._towers.push_back(tower);
                }
                _floatingMenu.reset();
                break;
            }
            case MenuEntry_STRINGTOWER: {
                std::shared_ptr<class Tower> tower = std::make_shared<class StringTower>(pos);
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
    // NO AUTO LOOP! We add Particales in the Update function to the projectiles list.
    for (int i = 0; i < (int) tdGlobals->_projectiles.size(); i++) {
        tdGlobals->_projectiles.at(i)->Update();
    }
    globals._projectiles.erase(
            std::remove_if(
                    globals._projectiles.begin(),
                    globals._projectiles.end(),
                    [](const std::shared_ptr<Projectile> &mov) { return !mov->_alive; }
            ),
            globals._projectiles.end());
}

void TestTD::updateEnemeies() {
    // NO AUTO LOOP! We add Enemies in the Update function to the enemy list.
    for (int i = 0; i < (int) tdGlobals->_enemies.size(); i++) {
        tdGlobals->_enemies.at(i)->Update();
    }
    globals._enemies.erase(
            std::remove_if(
                    globals._enemies.begin(),
                    globals._enemies.end(),
                    [](const std::shared_ptr<Enemy> &mov) { return !mov->_alive; }
            ),
            globals._enemies.end());
}

bool TestTD::buyTower(const std::shared_ptr<class Tower> &tower) {
    if ((uint) tower->getCosts() > globals._pl._creditPoints) {
        return false;
    }
    if (tower->init(&tdGlobals->_focus)) {
        globals._pl._creditPoints -= tower->getCosts();
        return true;
    }
    return false;
}

TestTD::TestTD(Game &game, string mapPath) : GameState(game, GS_TD) {
    tdGlobals = &globals;
    _texMethran = t_cache->get(BasePath"asset/graphic/methran1.png");
    SDL_QueryTexture(_texMethran, nullptr, nullptr, &MethranDst.w, &MethranDst.h);
    pGame = &game;
    pMap = &_map;
    globals._mapPath = new string(std::move(mapPath));
}

void TestTD::handleEvent(const GameEvent &event) {
    switch (event.type) {
        case Boss_Drueberbolz: {
            std::shared_ptr<DrüberBolz> e = std::make_shared<DrüberBolz>();
            e->setEnemy(pMap->getStartPoint(event.SpawnPoint), event.health, event.speed, event.value, event.type);
            globals._enemies.push_back(e);
            break;
        }
        case Boss_Frohle_Poehlich: {
            std::shared_ptr<FrolePöhlich> e = std::make_shared<FrolePöhlich>();
            e->setEnemy(pMap->getStartPoint(event.SpawnPoint), event.health, event.speed, event.value, event.type);
            globals._enemies.push_back(e);
            break;
        }
        case Ordinary: {
            std::shared_ptr<Enemy> e = std::make_shared<Enemy>();
            e->setEnemy(pMap->getStartPoint(event.SpawnPoint), event.health, event.speed, event.value, event.type);
            globals._enemies.push_back(e);
            break;
        }
    }
}

void TDGlobals::setPath(string newMapPath) {
    delete _mapPath;
    _mapPath = new string(std::move(newMapPath));
}

bool TDGlobals::isEnemyBlocking(FPoint tile) {
    for(auto &e: _enemies){
        if((int)e->_pos.x==(int)tile.x && (int)e->_pos.y == (int)tile.y)
            return true;
    }
    return false;
}

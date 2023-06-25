//
// Created by banoodle on 23.05.23.
//
#include "editor.h"
#include "../util/dataHandler.h"
#include "../td/testtd.h"

Editor::Editor(Game &game) : GameState(game, GS_Editor) {}

void Editor::Init() {
    GameState::Init();
    Toolbox = {0, windowSize.y - 100, windowSize.x, 100};
    _buttons.emplace_back("Laden", _fontSize, btn_Load);
    _buttons.emplace_back("Speichern", _fontSize, btn_save);
    _buttons.emplace_back("Pathfinding", _fontSize, btn_pathFinding);
    _buttons.emplace_back("Map-Größe", _fontSize, btn_changeSize);
    _buttons.emplace_back("Game-Settings", _fontSize, btn_playerSettings);
    _buttons.emplace_back("Wave's", _fontSize, btn_waveSettings);
    _buttons.emplace_back("Start Game", _fontSize, btn_startGame);
    for (auto &btn: _buttons) {
        btn.setHighlightedColor(BTN_HIGHLIGHTED);
    }
    audioHandler->playMusic(MusicEditor);
}

void Editor::UnInit() {
    GameState::UnInit();
    audioHandler->stopMusic();
}

void Editor::Update() {
    if (focus == nullptr) {
        // inputhandling
        SDL_GetMouseState(&mousePos.x, &mousePos.y);
        if (_mbLeft)MouseClickLeft();
        if (_mbRight)MouseClickRight();
        if (mapSelector.isFileSelected()) {
            mapName = mapSelector.getSelectedFile();
            DataHandler::load(player, waves, map, mapSelector.getSelectedFile());
            mapSelector.reset();
        }
        if (mapNameInput.isDone()) {
            DataHandler::save(player, waves, map, mapNameInput.getInput());
            mapNameInput.reset();
        }
        if (resizeMap.isDone()) {
            map.resize(resizeMap.getInput());
            resizeMap.reset();
        }
        if (settingsDialog.isDone()) {
            player._sanity = settingsDialog.getSanity();
            player._creditPoints = settingsDialog.getCreditPoints();
            player._usableTowers.clear();
            for (auto entry: settingsDialog.getUsableTowers())
                player._usableTowers.insert(entry);
        }
        // update "Viewport" / Zoom in or Out
        if (_mouseWheel) {
            Game::zoomScreen(_wheelEvent);
            _mouseWheel = false;
        }
        updateButtonPos();
    }
}

void Editor::Render() {
    rh->background(BG);
    // Render map
    map.RenderBG(true);
    for (int y = 0; y < map._height; y++)
        map.RenderRow(y);
    if (showPath)map.RenderPath();
    map.RenderFrontWall();
    // now Render ui
    RenderToolbox();
    if (isLabelActive && labelTimer > 60)
        rh->hint(labelObject, 18, labelPos, BLACK, WHITE);
    for (auto &btn: _buttons)btn.Render();
    mapSelector.Render();
    mapNameInput.Render();
    resizeMap.Render();
    settingsDialog.Render();
}

void Editor::RenderToolbox() {
    Rect tool, symbol;
    tool = {0, 0, 80, 80};
    symbol = {0, 0, 64, 64};
    rh->fillRect(&Toolbox, EDITOR_UI_BG);
    tool.x = 100;
    symbol.x = tool.x + 8;
    tool.y = windowSize.y - 90;
    symbol.y = tool.y + 8;
    for (int i = 0; i < TdTileHandler::TOOLCOUNT; i++) {
        rh->fillRect(&tool, WHITE);
        rh->tile(&symbol, TdTileHandler::getSrcRect(i));
        if (this->selected == i) {
            rh->setColor({0, 0, (u8) rainbowColor, 255});
            rh->rect(&tool, 5);
            rainbowColor += 10;
        }
        tool.x += 90;
        symbol.x = tool.x + 8;
    }
}

void Editor::Events() {
    if (focus == nullptr) {
        SDL_Event event;
        labelTimer++;
        while (SDL_PollEvent(&event)) {
            if (pGame->HandleEvent(event))
                return;
            switch (event.type) {
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                        game.SetNextState(GS_Close);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    switch (event.button.button) {
                        case SDL_BUTTON_RIGHT:
                            _mbRight = true;
                            break;
                        case SDL_BUTTON_LEFT:
                            _mbLeft = true;
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    switch (event.button.button) {
                        case SDL_BUTTON_RIGHT:
                            _mbRight = false;
                            break;
                        case SDL_BUTTON_LEFT:
                            _mbLeft = false;
                            break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    _motionEvent = event;
                    MouseMotion(event);
                    _mouseMotion = true;
                    break;
                case SDL_MOUSEWHEEL:
                    _mouseWheel = true;
                    _wheelEvent = event;
                    break;
                case SDL_KEYDOWN:
                    keyDown(event);
            }
        }
    } else {
        focus->Input();
    }
}

void Editor::MouseMotion(SDL_Event event) {
    isLabelActive = false;
    if (event.motion.y < (Toolbox.y)) {
        labelPos = {event.motion.x, event.motion.y};
        if (_mbLeft) {
            map.setTile(event, selected);
            labelObject = selected;
        } else
            labelObject = map.getObjectAtScreenPos(labelPos);
        isLabelActive = true;
        labelPos.y -= 30;
        labelTimer = 0;
    }
    for (auto &btn: _buttons)
        btn.entered(event);
}

void Editor::keyDown(SDL_Event event) {
    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_ESCAPE:
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
        default:
            break;
    }
}

void Editor::MouseClickLeft() {
    if (_mbLeft) {
        if (mousePos.y < (Toolbox.y)) {
            map.setTile(CT::getTileInGame(mousePos), selected);
            labelObject = selected;
            labelPos = {mousePos.x, mousePos.y - 30};
        } else {
            for (auto &btn: _buttons) {
                if (btn.clicked(mousePos)) {
                    switch ((Buttons) btn.getId()) {
                        case btn_Load:
                            mapSelector.set(BasePath"Maps/", ".map");
                            mapSelector.show(&focus);
                            break;
                        case btn_save:
                            mapNameInput.set("Gib einen Mapnamen ein", "Name", mapName, 50, true);
                            mapNameInput.show(&focus);
                            break;
                        case btn_waveSettings:
                            break;
                        case btn_startGame:
                            DataHandler::save(player, waves, map, "tmp");
                            game.SetNextState(GS_TD);
                            tdGlobals->setPath("tmp.map");
                            tdGlobals->editor = true;
                            break;
                        case btn_changeSize:
                            resizeMap.set(map._width, map._height, true);
                            resizeMap.show(&focus);
                            break;
                        case btn_playerSettings:
                            settingsDialog.set(player, true);
                            settingsDialog.show(&focus);
                            break;
                        case btn_pathFinding:
                            showPath = !showPath;
                            if (showPath)
                                btn.setColor(YELLOW);
                            else
                                btn.setColor(BTN_COLOR);
                            break;
                    }
                    _mbLeft = false;
                    break;
                }
            }
            handleSelection();
        }
    }
}

void Editor::MouseClickRight() {
    if (_mouseMotion) {
        Game::scrollScreen(_motionEvent);
        _mouseMotion = false;
    }
}

void Editor::handleSelection() {
    if (mousePos.y < windowSize.y - 10 && mousePos.y > windowSize.y - 90) {
        int x = mousePos.x - 100;
        if (x > 0 && x < (TdTileHandler::TOOLCOUNT * 90 - 10)) {
            if (x % 90 < 81) {
                selected = TdTileHandler::selectObject(x / 90);
            }
        }
    }
}

void Editor::updateButtonPos() {
    int yPos = windowSize.y - 90;
    int btnHeight = 80;
    int btnWidth = 135;
    int btnOffset = 140;
    Rect save = {windowSize.x - btnOffset, yPos, btnWidth, btnHeight};
    Rect pathfinding = {save.x - btnOffset, yPos, btnWidth, btnHeight};
    Rect changeSize = {pathfinding.x - btnOffset, yPos, btnWidth, btnHeight};
    Rect playerSettings = {changeSize.x - btnOffset, yPos, btnWidth, btnHeight};
    Rect waveSettings = {playerSettings.x - btnOffset, yPos, btnWidth, btnHeight};
    Rect start = {waveSettings.x - btnOffset, yPos, btnWidth, btnHeight};
    for (auto &btn: _buttons) {
        switch ((Buttons) btn.getId()) {
            case btn_Load:
                btn.setSize({5, yPos, 80, btnHeight});
                break;
            case btn_save:
                btn.setSize(save);
                break;
            case btn_waveSettings:
                btn.setSize(waveSettings);
                break;
            case btn_startGame:
                btn.setSize(start);
                break;
            case btn_changeSize:
                btn.setSize(changeSize);
                break;
            case btn_playerSettings:
                btn.setSize(playerSettings);
                break;
            case btn_pathFinding:
                btn.setSize(pathfinding);
                break;
        }
    }
}

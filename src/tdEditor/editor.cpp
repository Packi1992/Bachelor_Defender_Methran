//
// Created by banoodle on 23.05.23.
//
#include "editor.h"

Editor::Editor(Game &game) : GameState(game, GS_Editor) {
    pGame = &game;
    t_tileMap = t_cache->get(BasePath "asset/graphic/td/tileTD.png");
}

void Editor::Init() {
    GameState::Init();
    Toolbox = {0, windowSize.y - 100, windowSize.x, 100};
    int yPos = windowSize.y - 90;
    btn_load.set("Laden", 18, {5, yPos, 80, 80});
    btn_load.setHighlightedColor(BTN_HIGHLIGHTED);
    btn_save.set("Speichern", 18, {windowSize.x - 105, yPos, 100, 80});
    btn_save.setHighlightedColor(BTN_HIGHLIGHTED);
    btn_path.set("Show Path",18,{btn_save.getX()-105,yPos,100,80});
    btn_path.setHighlightedColor(BTN_HIGHLIGHTED);
    btn_change_size.set("Größe ändern", 18, {btn_path.getX() - 135, yPos, 130, 80});
    btn_change_size.setHighlightedColor(BTN_HIGHLIGHTED);
    btn_playerSettings.set("Map Settings", 18, {btn_change_size.getX() - 135, yPos, 130, 80});
    btn_playerSettings.setHighlightedColor(BTN_HIGHLIGHTED);
    audioHandler->playMusic(MusicEditor);
}

void Editor::UnInit() {
    GameState::UnInit();
    audioHandler->stopMusic();
}

void Editor::Update() {
    if (focus == nullptr) {
        if (mapSelector.isFileSelected()) {
            DataHandler::load(player,waves,map,mapSelector.getSelectedFile());
            mapSelector.reset();
        }
        if (mapNameInput.isDone()) {
            DataHandler::save(player,waves,map,mapNameInput.getInput());
            mapNameInput.reset();
        }
        if(resizeMap.isDone()){
            map.resize(resizeMap.getInput());
            resizeMap.reset();
        }
        if(settingsDialog.isDone()){
            player._sanity = settingsDialog.getSanity();
            player._creditPoints = settingsDialog.getCreditPoints();
            player._usableTowers.clear();
            for(auto &entry: settingsDialog.getUsableTowers())
                player._usableTowers.insert(entry);
        }
        // update "Viewport" / Zoom in or Out
        if(_mouseWheel){
            Game::zoomScreen(_wheelEvent);
            _mouseWheel = false;
        }
        if(_mouseMotion && _mbRight){
            Game::scrollScreen(_motionEvent);
            _mouseMotion = false;
        }
    }
}

void Editor::Render() {
    rh->background(BG);
    // Render maps
    map.Render(true,showPath);
    // now Render ui
    Rect tool, symbol;
    tool = {0, 0, 80, 80};
    symbol = {0, 0, 64, 64};
    rh->fillRect(&Toolbox,EDITOR_UI_BG);
    tool.x = 100;
    symbol.x = tool.x + 8;
    tool.y = windowSize.y - 90;
    symbol.y = tool.y + 8;
    for (int i = 0; i < TdTileHandler::TOOLCOUNT; i++) {
        rh->fillRect(&tool,WHITE);
        rh->texture(t_tileMap, &symbol, TdTileHandler::getSrcRect(i));
        if (this->selected == i) {
            rh->setColor({ 0, 0, (u8)rainbowColor, 255});
            rh->rect(&tool,5);
            rainbowColor += 10;
        }
        tool.x += 90;
        symbol.x = tool.x + 8;
    }
    if (isLabelActive && labelTimer > 60) {
        rh->hint(labelObject, 18, labelPos, BLACK, WHITE);
    }
    btn_save.draw();
    btn_load.draw();
    btn_path.draw();
    btn_change_size.draw();
    btn_playerSettings.draw();
    mapSelector.Render();
    mapNameInput.Render();
    resizeMap.Render();
    settingsDialog.Render();
}

void Editor::handleSelection(Event event) {
    if (event.motion.y < windowSize.y - 10 && event.motion.y > windowSize.y - 90) {
        int x = event.motion.x - 100;
        if (x > 0 && x < (TdTileHandler::TOOLCOUNT * 90 - 10)) {
            if (x % 90 < 81) {
                selected = TdTileHandler::selectObject(x / 90);

            }
        }
    }
}

void Editor::Events() {
    if (focus == nullptr) {
        SDL_Event event;
        labelTimer++;
        while (SDL_PollEvent(&event)) {
            if(pGame->HandleEvent(event))
                return;
            switch (event.type) {
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                        game.SetNextState(GS_Close);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    MouseDown(event);
                    break;
                case SDL_MOUSEBUTTONUP:
                    _mbLeft = false;
                    if (event.button.button == SDL_BUTTON_RIGHT && _mbRight)_mbRight = false;
                    break;
                case SDL_MOUSEMOTION:
                    _motionEvent = event;
                    MouseMotion(event);
                    _mouseMotion=true;
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

void Editor::MouseDown(SDL_Event event) {
    if (event.button.button == SDL_BUTTON_LEFT) {
        if (event.motion.y < (Toolbox.y))_mbLeft = true;
        if (_mbLeft) {
            map.setTile(event, selected);
            labelObject = selected;
            labelPos = {event.motion.x, event.motion.y - 30};
        } else {
            if (btn_save.clicked(event)){
                mapNameInput.set("Gib einen Mapnamen ein","Name","neueMap");
                mapNameInput.show(&focus);
            }
            else if (btn_load.clicked(event)){
                mapSelector.set( BasePath"Maps/", ".map");
                mapSelector.show(&focus);
            }else if (btn_path.clicked(event)){
                showPath = !showPath;
                if(showPath)
                    btn_path.setColor(YELLOW);
                else
                    btn_path.setColor(BTN_COLOR);
            }
            else if (btn_change_size.clicked(event)) {
                resizeMap.set(map._width, map._height);
                resizeMap.show(&focus);
            }
            else if (btn_playerSettings.clicked(event)) {
                settingsDialog.set(&player);
                settingsDialog.show(&focus);
            }
            else handleSelection(event);
        }
    } else if (event.button.button == SDL_BUTTON_RIGHT) {
        _mbRight = true;
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
    btn_load.entered(event);
    btn_path.entered(event);
    btn_change_size.entered(event);
    btn_save.entered(event);
    btn_playerSettings.entered(event);
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
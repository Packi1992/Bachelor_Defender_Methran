//
// Created by banoodle on 23.05.23.
//
#include "editor.h"


void Editor::Init() {
    GameState::Init();
    pGame = &game;
    t_tileMap = t_cache->get(BasePath "asset/graphic/td/tileTD.png");
    Toolbox = {0, windowSize.y - 100, windowSize.x, 100};
    int yPos = windowSize.y - 90;
    btn_load.set("Laden", 18, {5, yPos, 80, 80});
    btn_load.setHighlightedColor(BTN_HIGHLIGHTED);
    btn_save.set("Speichern", 18, {windowSize.x - 105, yPos, 100, 80});
    btn_save.setHighlightedColor(BTN_HIGHLIGHTED);
    btn_path.set("Show Path",18,{btn_save.getX()-105,yPos,100,80});
    btn_path.setHighlightedColor(BTN_HIGHLIGHTED);
    btn_change_size.set("Größe ändern", 18, {btn_path.getX() - 135, yPos, 130, 80});
}

void Editor::UnInit() {
    GameState::UnInit();
}

void Editor::Update(const u32 frame, const u32 totalMSec, const float deltaT) {
    if (focus == nullptr) {
        if (mapSelector.isFileSelected()) {
            map.load(mapSelector.getSelectedFile());
            mapSelector.reset();
        }
        if (mapNameInput.isDone()) {
            map.save(mapNameInput.getInput());
            mapNameInput.reset();
        }
    }
}

void Editor::Render(const u32 frame, const u32 totalMSec, const float deltaT) {
    t_cache->drawBackground(BG);
    // Render maps
    map.Render(true,showPath);
    // now Render ui
    Rect tool, symbol;
    tool = {0, 0, 80, 80};
    symbol = {0, 0, 64, 64};

    t_cache->renderFillRect(&Toolbox,EDITOR_UI_BG);
    tool.x = 100;
    symbol.x = tool.x + 8;
    tool.y = windowSize.y - 90;
    symbol.y = tool.y + 8;
    for (int i = 0; i < TdTileHandler::TOOLCOUNT; i++) {
        t_cache->renderFillRect(&tool,WHITE);
        t_cache->render(t_tileMap, &symbol, TdTileHandler::getSrcRect(i, map.getMapTime()));
        if (this->selected == i) {
            t_cache->setRenderColor({ 0, 0, (u8)rainbowColor, 255});
            t_cache->renderRect(&tool,5);
            rainbowColor += 10;
        }
        tool.x += 90;
        symbol.x = tool.x + 8;
    }
    if (isLabelActive && labelTimer > 60) {
        t_cache->drawHint(labelObject, 18, labelPos, BLACK, WHITE);
    }
    btn_save.draw();
    btn_load.draw();
    btn_path.draw();
    btn_change_size.draw();
    mapSelector.Render();
    mapNameInput.Render();
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

void Editor::Events(const u32 frame, const u32 totalMSec, const float deltaT) {
    if (focus == nullptr) {
        SDL_Event event;
        labelTimer++;
        while (SDL_PollEvent(&event)) {
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
            }
        }
    } else {
        focus->Input();
    }
}

void Editor::MouseDown(SDL_Event event) {
    if (event.button.button == SDL_BUTTON_LEFT) {
        if (event.motion.y < (Toolbox.y))mbDown = true;
        if (mbDown) {
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
            else if (btn_change_size.clicked(event))pMap->showSizeDialog();
            else handleSelection(event);
        }
    } else if (event.button.button == SDL_BUTTON_RIGHT) {
        mouseScroll = true;
    }
}

void Editor::MouseMotion(SDL_Event event) {
    isLabelActive = false;
    if (event.motion.y < (Toolbox.y)) {
        labelPos = {event.motion.x, event.motion.y};
        if (mbDown) {
            map.setTile(event, selected);
            labelObject = selected;
        } else
            labelObject = map.getObjectAtScreenPos(labelPos);
        isLabelActive = true;
        labelPos.y -= 30;
        labelTimer = 0;
        if (mouseScroll) {
            offset.x -= event.motion.xrel;
            offset.y -= event.motion.yrel;
        }
    }
    btn_load.entered(event);
    btn_path.entered(event);
    btn_change_size.entered(event);
    btn_save.entered(event);
}

void Editor::keyDown(SDL_Event event) {
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
        default:
            break;
    }
}

void Editor::MouseWheel(SDL_Event event) {
    scale += event.wheel.y;
    int posX,posY;
    SDL_GetMouseState(&posX, &posY);
    offset.y += event.wheel.y / abs(event.wheel.y) * map._height / 2;
    offset.x += event.wheel.y / abs(event.wheel.y) * map._width / 2;
}


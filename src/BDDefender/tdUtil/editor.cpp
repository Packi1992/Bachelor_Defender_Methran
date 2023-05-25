//
// Created by banoodle on 23.05.23.
//
#include "editor.h"
#include "../../util/gui_selector.h"
#include "../../util/nameInputDialog.h"

void Editor::Init() {
    GameState::Init();
    map.set(&offset);
    t_tile = t_cache->getTexture("../asset/graphic/td/tileTD.png");
    Point wSize = game.GetWindowSize();
    Toolbox = {0, wSize.y - 100, wSize.x, 100};
    int yPos = wSize.y - 90

            ;
    btn_load.set( "Laden", 18, {5, yPos, 80, 80});
    btn_save.set( "Speichern", 18, {wSize.x- 105, yPos, 100, 80});
    btn_change_size.set("Größe ändern", 18, {btn_save.getX()-135, yPos, 130, 80});
}

void Editor::Events(const u32 frame, const u32 totalMSec, const float deltaT) {
    SDL_Event event;
    //Point wSize = game.GetWindowSize();
    labelTimer++;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                    game.SetNextState(99);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (event.motion.y < (Toolbox.y))mbDown = true;
                    if (mbDown) {
                        map.set(event, selected);
                        labelObject = selected;
                        labelPos = {event.motion.x, event.motion.y-30};
                    } else {
                        if (btn_save.clicked(event))save();
                        else if (btn_load.clicked(event))load();
                        else if (btn_change_size.clicked(event))map.showSizeDialog();
                        else handleSelection(event);
                    }
                } else if (event.button.button == SDL_BUTTON_RIGHT) {
                    mouseScroll = true;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                mbDown = false;
                if (event.button.button == SDL_BUTTON_RIGHT && mouseScroll)mouseScroll = false;
                break;
            case SDL_MOUSEMOTION:
                isLabelActive = false;
                if (event.motion.y < (Toolbox.y)) {
                    labelPos = {event.motion.x, event.motion.y};
                    if (mbDown) {
                        map.set(event, selected);
                        labelObject = selected;
                    }else
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
                btn_change_size.entered(event);
                btn_save.entered(event);
                break;
            case SDL_MOUSEWHEEL:
                map.scale += event.wheel.y;
                int posX;
                int posY;
                SDL_GetMouseState(&posX, &posY);
                offset.y += event.wheel.y / abs(event.wheel.y) * map.height / 2;
                offset.x += event.wheel.y / abs(event.wheel.y) * map.width / 2;
                break;
            case SDL_KEYDOWN:
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
    }
}

void Editor::UnInit() {
    GameState::UnInit();
}

void Editor::Update(const u32 frame, const u32 totalMSec, const float deltaT) {

}

void Editor::Render(const u32 frame, const u32 totalMSec, const float deltaT) {
    t_cache->drawBackground(BG);
    // draw maps
    map.draw(false);
    // now draw ui
    Rect tool,symbol;
    tool = {0, 0, 80, 80};
    symbol = {0, 0, 64, 64};
    Point wSize = game.GetWindowSize();

    t_cache->setRenderColor(EDITOR_UI_BG);
    SDL_RenderFillRect(render, &Toolbox);



    tool.x = 100;
    symbol.x = tool.x + 8;
    tool.y = wSize.y - 90;
    symbol.y = tool.y + 8;
    for (int i = 0; i < TdTileHandler::TOOLCOUNT; i++) {
        t_cache->setRenderColor(WHITE);
        SDL_RenderFillRect(render, &tool);
        t_cache->render(t_tile, &symbol, TdTileHandler::getSrcRect(i, map.getMapTime()));
        if (this->selected == i) {
            SDL_SetRenderDrawColor(render, 0, 0, rainbowColor, 255);
            SDL_RenderDrawRect(render, &tool);
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
    btn_change_size.draw();
}

void Editor::handleSelection(Event event) {
    Point wSize = game.GetWindowSize();
    if (event.motion.y < wSize.y - 10 && event.motion.y > wSize.y - 90) {
        int x = event.motion.x - 100;
        if (x > 0 && x < (TdTileHandler::TOOLCOUNT * 90 - 10)) {
            if (x % 90 < 81) {
                selected = TdTileHandler::selectObject(x / 90);

            }
        }
    }
}

void Editor::save() {
    std::string returnTxt;
    NameInputDialog nid;
    nid.set(game.GetWindowSize(),"neueMap",50,&returnTxt);
    if(nid.show())
        map.save(returnTxt);
}

void Editor::load() {
    std::cout << "Editor: Start Load Function" <<std::endl;
    GuiSelector ms;
    ms.set(game.GetWindowSize(),"../Maps/",".map");
    ms.show();
    if(ms.isFileSelected()){
        map.load(ms.getSelectedFile());
    }
}


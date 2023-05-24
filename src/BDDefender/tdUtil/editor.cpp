//
// Created by banoodle on 23.05.23.
//
#include "editor.h"
#include "../../util/gui_selector.h"

void Editor::Init() {
    GameState::Init();
    tCache = TextureCache::getCache(render);
    map.set(render, &offset);
    t_tile = tCache->getTexture("../asset/graphic/td/tileTD.png");
    Point wSize = game.GetWindowSize();
    Toolbox = {0, wSize.y - 100, wSize.x, 100};

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
                        //if (btn_save.clicked(event))save();
                        //if (btn_load.clicked(event))load();
                        //if (btn_physik.clicked(event))doPhysics();
                        //if (btn_move.clicked(event))doMovement();
                        //if (btn_change_size.clicked(event))map->showSizeDialog();
                        handleSelection(event);
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
                //btn_load.entered(event);
                //btn_save.entered(event);
                //btn_physik.entered(event);
                //btn_change_size.entered(event);
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
    // draw mapss
    map.draw(true);
    // now draw ui
    Rect tool,symbol;
    tool = {0, 0, 80, 80};
    symbol = {0, 0, 64, 64};
    Point wSize = game.GetWindowSize();
    std::cout << wSize.x <<" "<< wSize.y << std::endl;

    tCache->setRenderColor(EDITOR_UI_BG);
    SDL_RenderFillRect(render, &Toolbox);



    tool.x = 100;
    symbol.x = tool.x + 8;
    tool.y = wSize.y - 90;
    symbol.y = tool.y + 8;
    for (int i = 0; i < 5; i++) {
        tCache->setRenderColor(WHITE);
        SDL_RenderFillRect(render, &tool);
        tCache->render(t_tile, &symbol, TdTileHandler::getSrcRect(i));
        if (this->selected == i) {
            SDL_SetRenderDrawColor(render, 0, 0, rainbowColor, 255);
            SDL_RenderDrawRect(render, &tool);
            rainbowColor += 10;
        }
        tool.x += 90;
        symbol.x = tool.x + 8;
    }
    if (isLabelActive && labelTimer > 60) {
        tCache->drawHint(labelObject, 18, labelPos, BLACK, WHITE);
    }
}

void Editor::handleSelection(Event event) {
    Point wSize = game.GetWindowSize();
    if (event.motion.y < wSize.y - 10 && event.motion.y > wSize.y - 90) {
        int x = event.motion.x - 100;
        if (x > 0 && x < (5 * 90 - 10)) {
            if (x % 90 < 81) {
                selected = TdTileHandler::selectObject(x / 90);

            }
        }
    }
}

void Editor::save() {
    std::string returntxt;
    //NameInputDialog nid(render,"neueMap",50,&returntxt);
    //nid.show();
    map.save(returntxt);
}

void Editor::load() {
    GuiSelector ms;
    ms.set(render,"path",".map");
    ms.show();
    if(ms.isFileSelected()){
        map.load(ms.getSelectedFile());
    }
}


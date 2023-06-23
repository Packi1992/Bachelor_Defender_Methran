//
// Created by banoodle on 10.05.23.
//

#include "worldMap.h"
#include "../util/recthelper.h"
#include "../util/gui/Button.h"
#include "../td/testtd.h"

void WorldMap::Init() {
    audioHandler->playMusic(MusicMainMenu);
}

void WorldMap::UnInit() {
    audioHandler->stopMusic();
    _msBtn_left = false;
}

void WorldMap::Events() {
    if(focus == nullptr) {
        SDL_PumpEvents();
        Event event;
        while (SDL_PollEvent(&event)) {
            if (game.HandleEvent(event))
                continue;
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
                    _msBtn_left = true;
                    break;
                case SDL_KEYDOWN: {
                    const Keysym &what_key = event.key.keysym;
                    if (what_key.scancode == SDL_SCANCODE_F9) {
                        // crash/shutdown, since State #99 does not exist
                        game.SetNextState(GS_Close);
                    }
                }
                default:
                    break;
            }
        }
    }
    else{
        focus->Input();
    }
}

void WorldMap::Update() {
    if(focus== nullptr) {
        if(mapSelector.isFileSelected()){
            tdGlobals->setPath(mapSelector.getSelectedFile());
            mapSelector.reset();
            game.SetNextState(GS_TD);
            return;
        }
        Point mousePos{};
        SDL_GetMouseState(&mousePos.x, &mousePos.y);
        if (_msBtn_left) {
            for (auto &btn: _buttons)
                if (btn.clicked(mousePos)) {
                    switch (btn.getId()) {
                        case btn_w1:
                            tdGlobals->setPath("gameMaps/world1.map");
                            game.SetNextState(GS_TD);
                            break;
                        case btn_w2:
                            tdGlobals->setPath("gameMaps/world2.map");
                            game.SetNextState(GS_TD);
                            break;
                        case btn_w3:
                            tdGlobals->setPath("gameMaps/world3.map");
                            game.SetNextState(GS_TD);
                            break;
                        case btn_w4:
                            tdGlobals->setPath("gameMaps/world4.map");
                            game.SetNextState(GS_TD);
                            break;
                        case btn_w5:
                            tdGlobals->setPath("gameMaps/world5.map");
                            game.SetNextState(GS_TD);
                            break;
                        case btn_Editor:
                            game.SetNextState(GS_Editor);
                            break;
                        case btn_ChooseMap:
                            mapSelector.set( BasePath"Maps/", ".map");
                            mapSelector.show(&focus);
                            break;
                    }
                }
            _msBtn_left = false;
        } else {
            for (auto &btn: _buttons)
                btn.entered(mousePos);
        }
        if (!_buttons.empty()) {
            // buttons will have both 80% (window.height and window.width)
            Point total = {(int) (windowSize.x * 0.8), (int) (windowSize.y * 0.8)};
            int btnHeight = total.y / ((int) _buttons.size() + 1);
            int btnMargin = btnHeight / (int) _buttons.size();
            Point btnStart = {(int) ((windowSize.x - total.x) * 0.5), (int) ((windowSize.y - total.y) * 0.5)};
            for (int i = 0; i < (int) _buttons.size(); i++) {
                _buttons[i].setSize(
                        {btnStart.x, (int) (btnStart.y + (btnHeight * i) + (btnMargin * i) + btnMargin * 0.5), total.x,
                         btnHeight});
            }
        }
    }
    else{
        focus->Update();
    }
}

void WorldMap::Render() {
    const Rect dst_rect{0, 0, windowSize.x, windowSize.y};
    SDL_RenderCopy(render, _image, EntireRect, &dst_rect /* same result as EntireRect */ );
    for (auto &btn: _buttons)
        btn.draw();
    mapSelector.Render();
}

WorldMap::WorldMap(Game &game) : GameState(game, GS_WorldMap) {
    _image = t_cache->get(BasePath "asset/graphic/bg-world.png");
    _buttons.emplace_back("1", _fontSize, btn_w1);
    _buttons.emplace_back("2", _fontSize, btn_w2);
    _buttons.emplace_back("3", _fontSize, btn_w3);
    _buttons.emplace_back("4", _fontSize, btn_w4);
    _buttons.emplace_back("5", _fontSize, btn_w5);
    _buttons.emplace_back("Editor",_fontSize,btn_Editor);
    _buttons.emplace_back("Wähle eine Map", _fontSize,btn_ChooseMap);

}

WorldMap::~WorldMap() {
    _buttons.clear();
    GameState::~GameState();
}
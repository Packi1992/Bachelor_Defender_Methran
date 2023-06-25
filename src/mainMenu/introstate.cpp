//
// Created by banoodle on 10.05.23.
//

#include "introstate.h"
#include "../util/recthelper.h"
#include "../util/gui/Button.h"

void MainMenu::Init() {
    audioHandler->playMusic(MusicMainMenu);
}

void MainMenu::UnInit() {
    audioHandler->stopMusic();
    _msBtn_left = false;
}

void MainMenu::Events() {
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

void MainMenu::Update() {
    Point mousePos{};
    SDL_GetMouseState(&mousePos.x, &mousePos.y);
    if (_msBtn_left) {
        for (auto &btn: _buttons)
            if (btn.clicked(mousePos)) {
                switch (btn.getId()) {
                    case btn_Start:
                        IfDebug {
                            game.SetNextState(GS_WorldMap);
                        }
                        IfNotDebug {
                            // only if first start of Game -> we need a config / save file
                            if (true)
                                game.SetNextState(GS_WorldMap);
                            else
                                game.SetNextState(GS_TD);
                        };
                        break;
                    case btn_Editor:
                        game.SetNextState(GS_Editor);
                        break;
                    case btn_Exit:
                        game.SetNextState(GS_Close);
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
        Point total = {(int) (windowSize.x * 0.6), (int) (windowSize.y * 0.5)};
        int btnHeight = total.y / ((int) _buttons.size() + 1);
        int btnMargin = btnHeight / (int) _buttons.size();
        Point btnStart = {(int) ((windowSize.x - total.x) * 0.5), (int) ((windowSize.y - total.y) * 0.8)};
        for (int i = 0; i < (int) _buttons.size(); i++) {
            _buttons[i].setSize(
                    {btnStart.x, (int) (btnStart.y + (btnHeight * i) + (btnMargin * i) + btnMargin * 0.5), total.x,
                     btnHeight});
        }
    }
}

void MainMenu::Render() {
    const Rect dst_rect{0, 0, windowSize.x, windowSize.y};
    SDL_RenderCopy(render, _image, EntireRect, &dst_rect /* same result as EntireRect */ );
    for (auto &btn: _buttons)
        btn.Render();
}

MainMenu::MainMenu(Game &game) : GameState(game, GS_MainMenu) {
    _image = t_cache->get(BasePath "asset/graphic/bg-main.png");
    _buttons.emplace_back("Start", _fontSize, Buttons::btn_Start, BTN_COLOR, true);
    IfDebug
        _buttons.emplace_back("Editor",_fontSize,Buttons::btn_Editor, BTN_COLOR, true);
    _buttons.emplace_back("Beenden", _fontSize, Buttons::btn_Exit, BTN_COLOR, true);
}

MainMenu::~MainMenu() {
    _buttons.clear();
    GameState::~GameState();
}
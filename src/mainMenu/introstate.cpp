//
// Created by banoodle on 10.05.23.
//

#include "introstate.h"
#include "../util/recthelper.h"
#include "../util/config.h"
#include "../util/gui/Button.h"
#include "../td/testtd.h"

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
                            if (config->worldsFinished == 0) {
                                cout << "no worlds finished!" << endl;
                                game.SetNextState(GS_TD);
                                tdGlobals->setPath("gameMaps/world1.map");
                            } else
                                game.SetNextState(GS_WorldMap);
                        }
                        break;
                    case btn_Editor:
                        game.SetNextState(GS_Editor);
                        break;
                    case btn_Mohrhuhn:
                        game.SetNextState(GS_Moorhuhn);
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
    Rect dst_rect{0, 0, windowSize.x, windowSize.y};
    SDL_RenderCopy(render, _image, EntireRect, &dst_rect /* same result as EntireRect */ );
    rh->background(BLACK, 120);
    dst_rect = {0, (int) ((float) windowSize.y * 0.1f), dst_rect.w, dst_rect.h / 3};
    SDL_RenderCopy(render, _titel, EntireRect, &dst_rect /* same result as EntireRect */ );
    for (auto &btn: _buttons)
        btn.Render();
}

MainMenu::MainMenu(Game &game) : GameState(game, GS_MainMenu) {
    _image = t_cache->get(BasePath "asset/graphic/bg-main.png");
    _titel = t_cache->get(BasePath "asset/graphic/Titel.png");
    _buttons.emplace_back("Start", _fontSize, Buttons::btn_Start, BTN_COLOR, true);
    _buttons.at(_buttons.size() - 1).setHighlightedColor(BTN_HIGHLIGHTED);
    IfDebug {
        _buttons.emplace_back("Editor", _fontSize, Buttons::btn_Editor, BTN_COLOR, true);
        _buttons.at(_buttons.size() - 1).setHighlightedColor(BTN_HIGHLIGHTED);
        //_buttons.emplace_back("Moorhuhn",_fontSize,Buttons::btn_Mohrhuhn, BTN_COLOR, true);
       // _buttons.at(_buttons.size() - 1).setHighlightedColor(BTN_HIGHLIGHTED);
    };
    _buttons.emplace_back("Beenden", _fontSize, Buttons::btn_Exit, BTN_COLOR, true);
    _buttons.at(_buttons.size() - 1).setHighlightedColor(BTN_HIGHLIGHTED);
}

MainMenu::~MainMenu() {
    _buttons.clear();
    GameState::~GameState();
}
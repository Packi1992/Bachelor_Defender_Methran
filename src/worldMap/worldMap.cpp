//
// Created by banoodle on 10.05.23.
//

#include "worldMap.h"
#include "../util/recthelper.h"
#include "../util/gui/Button.h"
#include "../td/testtd.h"
#include "../util/config.h"

void WorldMap::Init() {
    audioHandler->playMusic(MusicMainMenu);
}

void WorldMap::UnInit() {
    audioHandler->stopMusic();
    _msBtn_left = false;
}

void WorldMap::Events() {
    if (focus == nullptr) {
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
                    if (what_key.scancode == SDL_SCANCODE_ESCAPE) {
                        game.SetNextState(GS_MainMenu);
                    }
                }
                default:
                    break;
            }
        }
    } else {
        focus->Input();
    }
}

void WorldMap::Update() {
    if (focus == nullptr) {
        if (mapSelector.isFileSelected()) {
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
                        case btn_w6:
                            tdGlobals->setPath("gameMaps/world6.map");
                            game.SetNextState(GS_TD);
                            break;
                        case btn_w7:
                            tdGlobals->setPath("gameMaps/world7.map");
                            game.SetNextState(GS_TD);
                            break;
                        case btn_w8:
                            tdGlobals->setPath("gameMaps/world8.map");
                            game.SetNextState(GS_TD);
                            break;
                        case btn_Editor:
                            game.SetNextState(GS_Editor);
                            break;
                        case btn_ChooseMap:
                            mapSelector.set(BasePath"Maps/", ".map");
                            mapSelector.show(&focus);
                            break;
                        case btn_backToMain:
                            game.SetNextState(GS_MainMenu);
                            break;
                    }
                    tdGlobals->editor = false;
                }
            _msBtn_left = false;
        } else {
            for (auto &btn: _buttons)
                btn.entered(mousePos);
        }
        if (!_buttons.empty()) {
            // buttons will have both 80% (window.height and window.width)
            int btnSize = (int) ((float) windowSize.x * 0.04f);
            for (auto &_button: _buttons) {
                Rect size = {0, 0, btnSize, btnSize};
                switch ((Buttons) _button.getId()) {

                    case btn_w1:
                        size.x = (int) ((float) windowSize.x * 0.33f);
                        size.y = (int) ((float) windowSize.y * 0.765f);
                        _button.setSize(size);
                        break;
                    case btn_w2:
                        size.x = (int) ((float) windowSize.x * 0.43f);
                        size.y = (int) ((float) windowSize.y * 0.765f);
                        _button.setSize(size);
                        break;
                    case btn_w3:
                        size.x = (int) ((float) windowSize.x * 0.56f);
                        size.y = (int) ((float) windowSize.y * 0.55f);
                        _button.setSize(size);
                        break;
                    case btn_w4:
                        size.x = (int) ((float) windowSize.x * 0.56f);
                        size.y = (int) ((float) windowSize.y * 0.45f);
                        _button.setSize(size);
                        break;
                    case btn_w5:
                        size.x = (int) ((float) windowSize.x * 0.56f);
                        size.y = (int) ((float) windowSize.y * 0.35f);
                        _button.setSize(size);
                        break;
                    case btn_w6:
                        size.x = (int) ((float) windowSize.x * 0.772f);
                        size.y = (int) ((float) windowSize.y * 0.44f);
                        _button.setSize(size);
                        break;
                    case btn_w7:
                        size.x = (int) ((float) windowSize.x * 0.775f);
                        size.y = (int) ((float) windowSize.y * 0.17f);
                        _button.setSize(size);
                        break;
                    case btn_w8:
                        size.x = (int) ((float) windowSize.x * 0.58f);
                        size.y = (int) ((float) windowSize.y * 0.21f);
                        _button.setSize(size);
                        break;
                    case btn_Editor:
                        size.x = (int) ((float) windowSize.x * 0.8f);
                        size.y = (int) ((float) windowSize.y * 0.05f);
                        size.w = (int) ((float) windowSize.x * 0.15f);
                        _button.setSize(size);
                        break;
                    case btn_ChooseMap:
                        size.x = (int) ((float) windowSize.x * 0.05f);
                        size.y = (int) ((float) windowSize.y * 0.05f);
                        size.w = (int) ((float) windowSize.x * 0.20f);
                        _button.setSize(size);
                        break;
                    case btn_backToMain:
                        size.x = (int) ((float) windowSize.x * 0.35f);
                        size.y = (int) ((float) windowSize.y * 0.90f);
                        size.w = (int) ((float) windowSize.x * 0.25f);
                        _button.setSize(size);
                        break;
                }

            }
        }
    } else {
        focus->Update();
    }
}

void WorldMap::Render() {
    const Rect dst_rect{0, 0, windowSize.x, windowSize.y};
    SDL_RenderCopy(render, _image, EntireRect, &dst_rect /* same result as EntireRect */ );
    for (auto &btn: _buttons)
        btn.Render();
    mapSelector.Render();
}

WorldMap::WorldMap(Game &game) : GameState(game, GS_WorldMap) {
    _image = t_cache->get(BasePath "asset/graphic/bg-world.png");
    _buttons.emplace_back("1", _fontSize, btn_w1);
    _buttons.emplace_back("2", _fontSize, btn_w2);
    _buttons.emplace_back("3", _fontSize, btn_w3);
    _buttons.emplace_back("4", _fontSize, btn_w4);
    _buttons.emplace_back("5", _fontSize, btn_w5);
    _buttons.emplace_back("6", _fontSize, btn_w6);
    _buttons.emplace_back("7", _fontSize, btn_w7);
    _buttons.emplace_back("8", _fontSize, btn_w8);
    IfDebug {
        _buttons.emplace_back("Editor", _fontSize, btn_Editor);
        _buttons.emplace_back("Eigene Map", _fontSize, btn_ChooseMap);
    }
    IfNotDebug {
        if (config->worldsFinished >= 7) {
            _buttons.emplace_back("Editor", _fontSize, btn_Editor);
            _buttons.emplace_back("Eigene Map", _fontSize, btn_ChooseMap);
        }
    }
    _buttons.emplace_back("Zurück zum Hauptmenu", _fontSize, btn_backToMain);
    for (auto &btn: _buttons) {
        btn.setInactivColor(BTN_INACTIVE);
        btn.setHighlightedColor(BTN_HIGHLIGHTED);
    }
    updateActiveButtons();
}

WorldMap::~WorldMap() {
    _buttons.clear();
    GameState::~GameState();
}

void WorldMap::updateActiveButtons() {
    IfNotDebug {
        for (auto &btn: _buttons) {
            switch (btn.getId()) {
                case btn_w2:
                    btn.setActive(config->worldsFinished >= 1);
                    break;
                case btn_w3:
                    btn.setActive(config->worldsFinished >= 2);
                    break;
                case btn_w4:
                    btn.setActive(config->worldsFinished >= 3);
                    break;
                case btn_w5:
                    btn.setActive(config->worldsFinished >= 4);
                    break;
                case btn_w6:
                    btn.setActive(config->worldsFinished >= 5);
                    break;
                case btn_w7:
                    btn.setActive(config->worldsFinished >= 6);
                    break;
                case btn_w8:
                    btn.setActive(config->worldsFinished >= 7);
                    break;
                case btn_Editor:
                case btn_ChooseMap:
                    btn.setActive(config->worldsFinished >= 8);
                    btn.setVisible(config->worldsFinished >= 8);
            }
        }
    }
    IfDebug {
        for (auto &btn: _buttons) {
            btn.setActive(true);
        }
    }
}

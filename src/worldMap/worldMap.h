//
// Created by banoodle on 22.06.23.
//
#ifndef SDL_BASEGAME_WORLDMAP_H
#define SDL_BASEGAME_WORLDMAP_H

#include "../util/global.h"
#include "../util/gui/selectorDialog.h"

class Button;

class WorldMap final : public GameState {
protected:
    enum Buttons {
        btn_w1,
        btn_w2,
        btn_w3,
        btn_w4,
        btn_w5,
        btn_w6,
        btn_w7,
        btn_w8,
        btn_Editor,
        btn_ChooseMap,
    };
    Texture *_image = nullptr;
    Music *_music = nullptr;
    Vector<Button> _buttons{};

    int _fontSize = 30;
    bool _msBtn_left = false;

    SelectorDialog mapSelector;
    Gui *focus= nullptr;
public:
    explicit WorldMap(Game &game);

    ~WorldMap() override;

    using GameState::GameState;

    void Init() override;

    void UnInit() override;

    void Events() override;

    void Update() override;

    void Render() override;
};

#endif //SDL_BASEGAME_WORLDMAP_H
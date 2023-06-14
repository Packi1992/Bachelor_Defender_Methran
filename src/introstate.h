//
// Created by banoodle on 14.05.23.
//
#include "global.h"
#include "util/gui/Button.h"

#ifndef SDL_BASEGAME_INTROSTATE_H
#define SDL_BASEGAME_INTROSTATE_H

class IntroState final : public GameState {
protected:
    Texture *image = nullptr;
    Music *music = nullptr;
    Button btn_start;
    Button btn_editor;
    Button btn_exit;

public:
    // ctor
    using GameState::GameState;

    void Init() override;
    void UnInit() override;

    void Events() override;
    void Update() override;
    void Render() override;

    void updateBtnSize();
};
#endif //SDL_BASEGAME_INTROSTATE_H

//
// Created by banoodle on 14.05.23.
//
#ifndef SDL_BASEGAME_INTROSTATE_H
#define SDL_BASEGAME_INTROSTATE_H

#include "../util/global.h"

class Button;

class MainMenu final : public GameState {
protected:
    enum Buttons {
        btn_Start,
        btn_Settings,
        btn_Editor,
        btn_Exit,
        btn_Mohrhuhn,
    };
    Texture *_image = nullptr;
    Texture *_titel = nullptr;
    Music *_music = nullptr;
    Vector<Button> _buttons{};

    int _fontSize = 30;
    bool _msBtn_left = false;
public:
    explicit MainMenu(Game &game);

    ~MainMenu() override;

    using GameState::GameState;

    void Init() override;

    void UnInit() override;

    void Events() override;

    void Update() override;

    void Render() override;
};

#endif //SDL_BASEGAME_INTROSTATE_H
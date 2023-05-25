//
// Created by banoodle on 14.05.23.
//
#include "../global.h"
#include "../gamebase.h"
#include "../recthelper.h"
#include "../util/Button.h"
#include "../util/TextureCache.h"

#ifndef SDL_BASEGAME_INTROSTATE_H
#define SDL_BASEGAME_INTROSTATE_H

class IntroState final : public GameState {
protected:
    Font *font = nullptr;
    Texture *image = nullptr;
    Music *music = nullptr;
    Button btn_start;
    Button btn_editor;
    Button btn_exit;

    static constexpr const Array<Point,8> shadowOffsets = {
            1_up   + 1_left,
            1_up   + 1_right,
            1_down + 1_left,
            1_down + 1_right,
            2_right,
            2_left,
            2_up,
            2_down,
    };
public:
    // ctor
    using GameState::GameState;

    void Init() override;
    void UnInit() override;

    void Events( const u32 frame, const u32 totalMSec, const float deltaT ) override;
    void Update( const u32 frame, const u32 totalMSec, const float deltaT ) override;
    void Render( const u32 frame, const u32 totalMSec, const float deltaT ) override;

    void updateBtnSize(const Point &point);
};
#endif //SDL_BASEGAME_INTROSTATE_H

//
// Created by banoodle on 28.06.23.
//

#ifndef SDL_BACHELORDEFENDER_CREDITS_H
#define SDL_BACHELORDEFENDER_CREDITS_H


#include "../util/gamebase.h"

class Credits: public GameState {
private:
    bool _btnReturn = false;
    u32 _timer=0;
    u32 _lastTimePoint=0;
    Texture *blendedText{};
    Rect textRect{};
    Rect srcRect{};
public:
    explicit Credits(Game &game);
    void Init() override;

    void UnInit() override;

    void Events() override;

    void Update() override;

    void Render() override;
};


#endif //SDL_BACHELORDEFENDER_CREDITS_H

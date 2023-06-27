//
// Created by dex on 6/27/23.
//

#ifndef SDL_BACHELORDEFENDER_METHRANNANIM_H
#define SDL_BACHELORDEFENDER_METHRANNANIM_H

#include "anim.h"

class MethrannAnim : public Anim {
    u16 _animState = 0;
    Texture * _angerSymbol = nullptr;
    Rect _angerRect{};
public:
    MethrannAnim();

    void Render() override;
    void Update() override;
    void UpdateStatic();
    void reset() override;
    bool start() override;

    void nextStep();
};


#endif //SDL_BACHELORDEFENDER_METHRANNANIM_H

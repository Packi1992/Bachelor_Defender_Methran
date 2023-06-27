//
// Created by dex on 6/25/23.
//

#ifndef SDL_BACHELORDEFENDER_GAMEOVERANIM_H
#define SDL_BACHELORDEFENDER_GAMEOVERANIM_H

#include "anim.h"

class GameOverAnim: public Anim {
    Rect _dstRectTL{};
    Rect _dstRectTR{};
    Rect _dstRectBL{};
    Rect _dstRectBR{};
    bool _renderParts = false;
    int _partDirection = 0;
public:
    GameOverAnim();
    void Update() override;
    void Render() override;
    void reset() override;
};



#endif //SDL_BACHELORDEFENDER_GAMEOVERANIM_H

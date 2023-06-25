//
// Created by dex on 6/25/23.
//

#ifndef SDL_BACHELORDEFENDER_GAMEOVERANIM_H
#define SDL_BACHELORDEFENDER_GAMEOVERANIM_H
#include "../../util/global.h"
class GameOverAnim {
private:
    u32 _animTime = 0;
    AnimType _type = Gameover;
    Point _posOnScreen {};
    Rect _dstRect{};
    Rect _dstRectTL{};
    Rect _dstRectTR{};
    Rect _dstRectBL{};
    Rect _dstRectBR{};
    bool _started = false;
    u32 _lastTimePoint = 0;
    bool _renderParts = false;
    uint32_t _partDirection = 0;
    bool _finishAnimation = false;
public:
    GameOverAnim();
    void Update();
    void Render();
    bool isStarted();
    void reset();
};



#endif //SDL_BACHELORDEFENDER_GAMEOVERANIM_H

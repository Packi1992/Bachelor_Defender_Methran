//
// Created by dex on 6/27/23.
//

#ifndef SDL_BACHELORDEFENDER_STUNBELLANIM_H
#define SDL_BACHELORDEFENDER_STUNBELLANIM_H
#include "../../util/global.h"

class StunBellAnim {
private:
    u32 _animTime = 0;
    AnimType _type = Bell;
    Point _posOnScreen {};
    Rect _dstRect{};
    bool _started = false;
    u32 _lastTimePoint = 0;
    bool _finishAnimation = false;
    Texture * _bellImg = nullptr;
    float _fDirection = 0.0f;
    int _direction = 0;
public:
    StunBellAnim();
    void Update();
    void Render();
    bool isStarted();
    bool start();
    void reset();
};

#endif //SDL_BACHELORDEFENDER_STUNBELLANIM_H

//
// Created by dex on 6/27/23.
//

#ifndef SDL_BACHELORDEFENDER_ANIM_H
#define SDL_BACHELORDEFENDER_ANIM_H

#include "../../util/global.h"

class Anim {
protected:
    u32 _animTime = 0;
    AnimType _type = Default_Anim;
    Point _posOnScreen{};
    Rect _dstRect{};
    bool _started = false;
    u32 _lastTimePoint = 0;
    bool _finishAnimation = false;
    Texture *_texture = nullptr;
    float _fDirection = 0.0f;
    int _direction = 0;
public:
    Anim();

    virtual void Update();

    virtual void Render();

    virtual bool isStarted();

    virtual bool start();

    virtual bool stop();

    virtual void reset();
};


#endif //SDL_BACHELORDEFENDER_ANIM_H

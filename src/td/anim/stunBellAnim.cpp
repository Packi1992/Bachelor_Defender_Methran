//
// Created by dex on 6/27/23.
//

#include "stunBellAnim.h"

StunBellAnim::StunBellAnim() : Anim(){
    _type = Bell;
    _texture = t_cache->get(BasePath "asset/graphic/td/bell.png");
}

void StunBellAnim::Update() {
    if (!_finishAnimation) {
        _animTime += totalMSec - _lastTimePoint;
        _lastTimePoint = totalMSec;
        int size = (windowSize.y / 3);
        _posOnScreen = {(int) ((float) windowSize.x * 0.5f), (int) ((float) windowSize.y * 0.5f)};
        _dstRect = {(int) ((float) _posOnScreen.x - (float) size * 0.5f),
                    (int) ((float) _posOnScreen.y - (float) size * 0.5f), size, size};
        u32 step = _animTime;
        if (step < 167) {
            _fDirection += 1.6f;
            _direction = (int) (_fDirection) % 360;
        } else if ((step >= 176) && (step <= 500)) {
            _fDirection += 358.4f;
            _direction = (int) (_fDirection) % 360;
        } else if ((step > 500) && (step <= 883)) {
            _fDirection += 1.6f;
            _direction = (int) (_fDirection) % 360;
        } else {
            _fDirection += 358.4f;
            _direction = (int) (_fDirection) % 360;
        }
        if (_animTime / 100 % 10 >= 9) {
            _finishAnimation = true;
        }
    }
}

bool StunBellAnim::start() {
    if (Anim::start()) {
        float x = (float) (windowSize.y) / float(windowSize.x);
        audioHandler->playSound(SoundBell, x);
    }
    return _started;
}

void StunBellAnim::reset() {
    Anim::reset();
    _fDirection = 0;
}

//
// Created by dex on 6/27/23.
//

#include "stunBellAnim.h"

StunBellAnim::StunBellAnim() {
    _type = Bell;
    _bellImg = t_cache->get(BasePath "asset/graphic/td/bell.png");
}

void StunBellAnim::Update() {
    if (!_finishAnimation) {
        _animTime += totalMSec - _lastTimePoint;
        _lastTimePoint = totalMSec;
        int size = (windowSize.y / 3);
        _posOnScreen = {(int) ((float) windowSize.x * 0.5f), (int) ((float) windowSize.y * 0.5f)};
        _dstRect = {(int) ((float) _posOnScreen.x - (float) size * 0.5f),
                    (int) ((float) _posOnScreen.y - (float) size * 0.5f), size, size};
        if (_animTime / 100 % 10 >= 9) {
            _finishAnimation = true;
        }
        _direction = (360 - (15 * ((_animTime % 2 == 0) ? 1 : -1))) % 360;
    }
}

void StunBellAnim::Render() {
    if (!_finishAnimation) {
        rh->texture(_bellImg, &_dstRect, _direction, TdTileHandler::getAnimSrcRect(_type, 0));
    }
}

bool StunBellAnim::isStarted() {
    return _started;
}

bool StunBellAnim::start() {
    if (!_started) {
        _lastTimePoint = totalMSec;
        _started = true;
        _animTime = 0;
    }
    return _started;
}

void StunBellAnim::reset() {
    _started = false;
    _lastTimePoint = 0;
    _finishAnimation = false;
    _direction = 0;
}

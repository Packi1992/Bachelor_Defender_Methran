//
// Created by dex on 6/27/23.
//

#include "anim.h"

Anim::Anim() {
    _direction = 0;
    _lastTimePoint = totalMSec;
}

void Anim::Update() {

}

void Anim::Render() {
    if (!_finishAnimation) {
        rh->texture(_texture, &_dstRect, _direction, TdTileHandler::getAnimSrcRect(_type, 0));
    }
}

bool Anim::isStarted() {
    return _started;
}

bool Anim::start() {
    if (!_started) {
        _lastTimePoint = totalMSec;
        _started = true;
        _animTime = 0;
    }
    return _started;
}

void Anim::reset() {
    _started = false;
    _lastTimePoint = totalMSec;
    _finishAnimation = false;
    _direction = 0;
}

bool Anim::stop() {
    _finishAnimation = true;
    return true;
}
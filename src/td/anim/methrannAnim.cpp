//
// Created by dex on 6/27/23.
//

#include "methrannAnim.h"
#include "../testtd.h"

MethrannAnim::MethrannAnim() {
    _type = Methrann_Anim;
    _texture = t_cache->get(BasePath"asset/graphic/methran1.png");
    _angerSymbol = t_cache->get(BasePath"asset/graphic/td/anger.png");
    SDL_QueryTexture(_texture, nullptr, nullptr, &_dstRect.w, &_dstRect.h);
}

void MethrannAnim::Update() {
    _lastTimePoint = totalMSec;
    if ((frame % 10) == 0) {
        float MethrannScaleFactor = 0.35f * (float) windowSize.y / (float) _dstRect.h;
        _dstRect.w = (int) (MethrannScaleFactor * (float) _dstRect.w);
        _dstRect.h = (int) (MethrannScaleFactor * (float) _dstRect.h);
        // Low Sanity
        if (_animState == 1) {
            _dstRect.x = windowSize.x - _dstRect.w - 100;
            _dstRect.y = windowSize.y - _dstRect.h - 100;
        } else if(_animState > 1){
            _dstRect.w = (int)((float)_dstRect.w * 3.0f);
            _dstRect.h = (int)((float)_dstRect.h * 3.0f);

            _dstRect.x =(int)((float)(windowSize.x - _dstRect.w) * 0.5f);
            _dstRect.y =(int)((float)windowSize.y - (float)_dstRect.h * 0.8f);
        }
        _angerRect.w = (int) ((float) _dstRect.w * 0.2f);
        _angerRect.h = (int) ((float) _dstRect.w * 0.2f);
        _dstRect.x += ((int) totalMSec / 100) % 20 * ((((int) totalMSec % 3) == 1) ? (-1) : 1);
        _dstRect.y += ((int) totalMSec / 100) % 20 * ((((int) totalMSec % 2) == 1) ? (-1) : 1);
        _direction = ((int) totalMSec / 100) % 20 * ((((int) totalMSec % 2) == 1) ? (-1) : 1);
        int angerPos = (((int)totalMSec / 100)%3);
        switch (angerPos) {
            case 0:
                _angerRect.x = _dstRect.x + 5;
                _angerRect.y = _dstRect.y + 50;
                break;
            case 1:
                _angerRect.x = _dstRect.x + _dstRect.w - 70;
                _angerRect.y = _dstRect.y + 40;
                break;
            default:
                _angerRect.x = _dstRect.x + _dstRect.w / 2;
                _angerRect.y = _dstRect.y + 20;
        }
    }
}

void MethrannAnim::UpdateStatic() {
    float MethrannScaleFactor = 0.35f * (float) windowSize.y / (float) _dstRect.h;
    _dstRect.w = (int) (MethrannScaleFactor * (float) _dstRect.w);
    _dstRect.h = (int) (MethrannScaleFactor * (float) _dstRect.h);
    _dstRect.x = windowSize.x - _dstRect.w - 100;
    _dstRect.y = windowSize.y - _dstRect.h - 100;
}

void MethrannAnim::reset() {
    Anim::reset();
    _animState = 0;
}

bool MethrannAnim::start() {
    if(!_started)
        _animState = 1;
    return Anim::start();
}

void MethrannAnim::Render() {
    Anim::Render();
    if (_animState >= 1) {
        if (!_finishAnimation) {
            rh->texture(_angerSymbol, &_angerRect, _direction, TdTileHandler::getAnimSrcRect(Anger_Anim, 0));
        }
    }
}

void MethrannAnim::nextStep() {
    _animState += 1;
}

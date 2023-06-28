//
// Created by dex on 6/28/23.
//

#include "creditAnim.h"

void CreditAnim::Render() {
    if (!_finishAnimation) {
        Anim::Render();
        int anim = (int) totalMSec;
        rh->tile(&_dstRectD, TdTileHandler::getEnemySrcRect(Boss_Drueberbolz, anim, BOTTOM));
        rh->tile(&_dstRectG, TdTileHandler::getEnemySrcRect(Girl, anim, BOTTOM));
        rh->tile(&_dstRectZ, TdTileHandler::getSrcRect(Goal, anim));
        rh->tile(&_dstRectB, TdTileHandler::getEnemySrcRect(Boy, anim, BOTTOM));
        rh->tile(&_dstRectF, TdTileHandler::getEnemySrcRect(Boss_Frohle_Poehlich, anim, BOTTOM));
        rh->tile(&_dstRun, TdTileHandler::getEnemySrcRect(_etype, anim, (_left)?RIGHT:LEFT), !_left);
    }
}

CreditAnim::CreditAnim() {
    _type = Credit_Anim;
    _texture = t_cache->get(BasePath"asset/graphic/methran1.png");
    SDL_QueryTexture(_texture, nullptr, nullptr, &_dstRect.w, &_dstRect.h);
    _dstRect.x = 0;
}

void CreditAnim::Update() {
    float MethrannScaleFactor = 0.20f * (float) windowSize.y / (float) _dstRect.h;
    _dstRect.w = (int) (MethrannScaleFactor * (float) _dstRect.w);
    _dstRect.h = (int) (MethrannScaleFactor * (float) _dstRect.h);
    _dstRect.y = int((float) windowSize.y * 0.6f);

    _dstRectD = {(int) ((float) windowSize.x * 0.3f), int((float) windowSize.y * 0.8f), 64, 128};
    _dstRectG = {(int) ((float) windowSize.x * 0.4f), int((float) windowSize.y * 0.8f), 64, 128};
    _dstRectZ = {(int) ((float) windowSize.x * 0.5f), int((float) windowSize.y * 0.8f), 64, 64};
    _dstRectB = {(int) ((float) windowSize.x * 0.6f), int((float) windowSize.y * 0.8f), 64, 128};
    _dstRectF = {(int) ((float) windowSize.x * 0.7f), int((float) windowSize.y * 0.8f), 64, 128};
    if(_left){
        _dstRect.x += 4;
    }else{
        _dstRect.x -= 4;
    }

    _dstRun = {0,0,64,128};
    if(_dstRect.x >= (windowSize.x + _dstRect.w + 120)){
        _left = false;
        _etype = Boss_Frohle_Poehlich;
    }else if(_dstRect.x <= -(_dstRect.w + 120)){
        _left = true;
        _etype = Boss_Drueberbolz;
    }
    _dstRun.x = _dstRect.x - 120;
    _dstRun.y = _dstRect.y + 70;
}

void CreditAnim::reset() {
    Anim::reset();
    _left = true;
}
//
// Created by dex on 6/25/23.
//

#include "gameOverAnim.h"

GameOverAnim::GameOverAnim():Anim() {
    _type = Gameover;
}

void GameOverAnim::Update() {
    if (!_finishAnimation) {
        _animTime += totalMSec - _lastTimePoint;
        _lastTimePoint = totalMSec;
        int size = (windowSize.y / 3);
        _posOnScreen = {(int) ((float) windowSize.x * 0.5f), (int) ((float) windowSize.y * 0.5f)};
        _dstRect = {(int) ((float) _posOnScreen.x - (float) size * 0.5f),
                    (int) ((float) _posOnScreen.y - (float) size * 0.5f), size, size};
        if (_animTime / 100 % 10 >= 9 && !_renderParts) {
            _renderParts = true;
            _dstRectTL = {_dstRect.x, _dstRect.y, (int) ((float) _dstRect.w * 0.5f), (int) ((float) _dstRect.h * 0.5f)};
            _dstRectTR = {_dstRect.x + (int) ((float) _dstRect.w * 0.5f), _dstRect.y, (int) ((float) _dstRect.w * 0.5f),
                          (int) ((float) _dstRect.h * 0.5f)};
            _dstRectBL = {_dstRect.x, _dstRect.y + (int) ((float) _dstRect.h * 0.5f), (int) ((float) _dstRect.w * 0.5f),
                          (int) ((float) _dstRect.h * 0.5f)};
            _dstRectBR = {_dstRect.x + (int) ((float) _dstRect.w * 0.5f),
                          _dstRect.y + (int) ((float) _dstRect.h * 0.5f),
                          (int) ((float) _dstRect.w * 0.5f), (int) ((float) _dstRect.h * 0.5f)};
        }
        if (_renderParts) {
            _dstRectTL.x -= 1;
            _dstRectTL.y -= 1;
            _dstRectTR.x += 1;
            _dstRectTR.y -= 1;
            _dstRectBL.x -= 1;
            _dstRectBL.y += 1;
            _dstRectBR.x += 1;
            _dstRectBR.y += 1;
        }
        _finishAnimation = (_dstRectTL.x + _dstRectTL.w < 0 && _dstRectTL.y + _dstRectTL.h < 0);
    }
}

void GameOverAnim::Render() {
    if (!_finishAnimation) {
        if (!_renderParts) {
            rh->tile(&_dstRect, 0, TdTileHandler::getAnimSrcRect(_type, _animTime / 100));
        } else {
            rh->tile(&_dstRectTL, _partDirection % 360, TdTileHandler::getAnimSrcRect(Gameover_Top_Left, 0));
            rh->tile(&_dstRectTR, _partDirection % 360, TdTileHandler::getAnimSrcRect(Gameover_Top_Right, 0));
            rh->tile(&_dstRectBL, _partDirection % 360, TdTileHandler::getAnimSrcRect(Gameover_Bottom_Left, 0));
            rh->tile(&_dstRectBR, _partDirection % 360, TdTileHandler::getAnimSrcRect(Gameover_Bottom_Right, 0));
            _partDirection += 1;
        }
    }
}

void GameOverAnim::reset() {
    Anim::reset();
    _partDirection = 0;
}
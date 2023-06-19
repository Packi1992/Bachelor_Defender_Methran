//
// Created by dex on 6/19/23.
//

#include "smallemy.h"

void Smallemy::Render() const {
    if (_alive) {
        // make dstRect
        Point POS = CT::getPosOnScreen(_pos);
        Rect dstRect = {POS.x, POS.y, (int)((float)scale * 0.5f), (int)((float)(scale+scale) * 0.5f)};
        dstRect.x = (int) (POS.x - dstRect.w * 0.5);
        dstRect.y = (int) (POS.y - dstRect.h * 0.8);
        u32 anim = _forceStun?0:(pGame->isGameover()?0:totalMscg);
        // check if enemy is on screen
        if (Game::onScreen(dstRect)) {
            Direction dir;
            bool flipped = false;
            switch (_dir) {
                case 0:
                    dir = Direction::TOP;
                    flipped = false;
                    break;
                case 90:
                    dir = Direction::RIGHT;
                    flipped = false;
                    break;
                case 180:
                    dir = Direction::BOTTOM;
                    flipped = false;
                    break;
                case 270:
                    dir = Direction::LEFT;
                    flipped = true;
                    break;
                default:
                    break;
            }
            rh->tile(&dstRect, TdTileHandler::getEnemySrcRect(this->_type, anim, dir), flipped);
        }
    }
}

FRect Smallemy::getHitBox() const {
    return {_pos.x - 0.35f* 0.5f, _pos.y - 1.4f* 0.5f, 0.7f * 0.5f, 1.6f * 0.5f};
}

Smallemy::Smallemy(FPoint pos, uint16_t health, uint8_t speed, u8 value, EnemyType type) : Enemy(pos, health, speed,
                                                                                                 value, type) {

}

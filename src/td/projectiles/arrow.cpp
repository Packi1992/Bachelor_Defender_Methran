//
// Created by dex on 6/8/23.
//

#include "arrow.h"
#include "../enemy/enemy.h"

Arrow::Arrow() {
    _type = ProjectileType::ARROW;
}

Arrow::Arrow(Arrow &p, std::shared_ptr<Enemy> e, uint16_t direction) : Projectile(p, e, direction) {

}

void Arrow::Update() {
    if (_targetE != nullptr) {
        if (!_targetE->_alive) {
            _targetE = nullptr;
        } else {
            float alpha = CT::getAngle(_position, _targetE->_pos);
            if (alpha != (float) _direction) {
                // try aiming at enemy
                // alpha = 350 / dir = 10 - left turn would be nice
                if (((int) alpha + 180) % 360 >= (int) _direction) {
                    // go counterclockwise
                    _direction = (uint16_t) ((int) ((float) _direction - _aimSpeed) % 360);
                    if ((float) _direction < alpha) {
                        _direction = (uint16_t) alpha;
                    }
                } else {
                    _direction = (uint16_t) ((int) ((float) _direction + _aimSpeed) % 360);
                    if ((float) _direction > alpha) {
                        _direction = (uint16_t) alpha;
                    }
                }
            }
        }
    }
    Projectile::Update();
}

void Arrow::collide() {
    _alive = false;
    float x = (float) (CT::getPosOnScreen(_position).x) / float(windowSize.x);
    audioHandler->playSound(SoundArrowHit, x);
}

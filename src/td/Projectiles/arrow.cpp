//
// Created by dex on 6/8/23.
//

#include "arrow.h"

Arrow::Arrow() {
    _type=ProjectileType::ARROW;
}

void Arrow::move() {
    Projectile::move();
}

void Arrow::collide() {
    float x = (float)(CT::getPosOnScreen(_position).x) / float(windowSize.x);
    Projectile::collide();
    audioHandler->playSound(SoundArrowHit, x);
}

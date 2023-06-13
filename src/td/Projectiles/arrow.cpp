//
// Created by dex on 6/8/23.
//

#include "arrow.h"

Arrow::Arrow() {
    _type=ProjectileType::ARROW;
}

void Arrow::move(float deltaT) {
    Projectile::move(deltaT);
}

void Arrow::collide(float deltaT) {
    float x = (float)(CT::getPosOnScreen(_position).x) / float(windowSize.x);
    Projectile::collide(deltaT);
    audioHandler->playSound(SoundArrowHit, x);
}

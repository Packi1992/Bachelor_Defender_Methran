//
// Created by dex on 6/8/23.
//

#include "arrow.h"

Arrow::Arrow() {
    _type=ProjectileType::ARROW;
}

Arrow::Arrow(Arrow &p, std::shared_ptr<Enemy> e, uint16_t direction) : Projectile(p, e, direction) {

}

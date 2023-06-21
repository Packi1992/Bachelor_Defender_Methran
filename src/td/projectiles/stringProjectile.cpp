//
// Created by dex on 6/19/23.
//

#include "stringProjectile.h"
#include "../../gamebase.h"
#include "../enemy/enemy.h"

StringProjectile::StringProjectile() {
    _type = ProjectileType::STRINGPROJECTILE;
    _direction = 0;
}

StringProjectile::StringProjectile(StringProjectile &p) : Projectile(p, nullptr, 0) {
    _string = p._string;
    _fontSize = p._fontSize;
    _texture = t_cache->getText(&_string,_fontSize, &_src, GREEN);

}

void StringProjectile::Update() {
    _posOnScreen = CT::getPosOnScreen(_position);
    _diff = (int) (totalMscg - _lastTimePoint);
    for (auto &entry: hitList) {
        entry.hitCooldown -= _diff;
    }
    hitList.erase(
            std::remove_if(
                    hitList.begin(),
                    hitList.end(),
                    [](HitTimer mov) { return mov.hitCooldown <= 0; }
            ),
            hitList.end());
    if (_diff < 0)_diff = 0;
    _lastTimePoint = totalMscg;
    // need to fix travel speed with render time

    if (_ttl != 0) {
        _ttl -= (int) _diff;
        if (_ttl <= 0) {
            _alive = false;
        } else {
            if (((_ttl / 10) % 100) < _tick) {
                _direction += 4;
                _tick--;
            }
        }
    }
    float sizeW = ((float) scale / 64 * (float) _size / 100.0f) * (float) _src.w;
    float sizeH = ((float) scale / 64 * (float) _size / 100.0f) * (float) _src.h;
    //dstRect needs to be changed depending on direction
    float angle = (float) _direction / 180.0f * (float) M_PI;
    float sinAngle = sin(angle);
    float cosAngle = cos(angle);
    _xFix = (int) (-sizeW/2+(cosAngle)*sizeW/2);
    _yFix = (int) (-sizeH/2+(sinAngle)*sizeW/2);
    _end = CT::getPosInGame({_posOnScreen.x + (int)(sizeW*cosAngle),_posOnScreen.y + (int)(sizeW*sinAngle)});
    _dstRect = {_posOnScreen.x + _xFix, _posOnScreen.y + _yFix, (int) sizeW, (int) sizeH};
}

void StringProjectile::collide() {
    float x = (float) (CT::getPosOnScreen(_position).x) / float(windowSize.x);
    audioHandler->playSound(SoundArrowHit, x);
}

bool StringProjectile::collision(std::shared_ptr<Enemy> e) {
    bool inList = false;
    for (auto &entry: hitList) {
        if (entry.enemy == e) {
            inList = true;
            break;
        }
    }
    if (!inList&&CT::collisionLineRect(_position, _end, e->getHitBox())) {
        e->takeDamage(this);
    }
    return true;
}

void StringProjectile::Render() {
    if (_alive && onScreen()) {

        rh->texture(_texture,&_dstRect,_direction);

        //rh->line(_posOnScreen,CT::getPosOnScreen(_end),BLACK);
    }
}


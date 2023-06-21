//
// Created by dex on 6/19/23.
//

#include "stringProjectile.h"
#include "../../gamebase.h"

StringProjectile::StringProjectile() {
    _type = ProjectileType::STRINGPROJECTILE;
    _direction = 0;
}

StringProjectile::StringProjectile(StringProjectile &p) : Projectile(p, nullptr, 0) {
    _string = p._string;
    _texture = t_cache->getText(&_string,12, &_src, GREEN);
}

void StringProjectile::Update() {
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
    if (!inList && Projectile::collision(e)) {
        hitList.push_back({e, 50});
        return true;
    }
    return false;
}

void StringProjectile::Render() {
    if (_alive && onScreen()) {
        Point pos = CT::getPosOnScreen(_position);

        float sizeW = ((float) scale / 64 * (float) _size / 100.0f) * (float) _src.w;
        float sizeH = ((float) scale / 64 * (float) _size / 100.0f) * (float) _src.h;
        //dstRect needs to be changed depending on direction
        float angle = (float) _direction / 180.0f * (float) M_PI;
        float sinAngle = sin(angle);
        float cosAngle = cos(angle);
        int xFix = (int) (-sizeW * 0.5 - sinAngle * sizeW);
        int yFix = (int) ((cosAngle - 1) * 0.5 * sizeH);
        Rect dstRect = {pos.x + xFix, pos.y + yFix, (int) sizeW, (int) sizeH};
        rh->texture(_texture,&dstRect,_direction+270);
        dstRect.y = pos.y;
        dstRect.x = pos.x;
        dstRect.w = 5;
        dstRect.h = 5;
        rh->fillRect(&dstRect, BLACK);
    }
}


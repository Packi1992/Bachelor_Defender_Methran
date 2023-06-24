//
// Created by dex on 6/18/23.
//

#include "baseExplosion.h"

BaseExplosion::BaseExplosion() {
    _type = ProjectileType::BASEEXPLOSION;
    _lastTimePoint = totalMSec;
    _ttl = 1500;
    _speed = 0;
    _damage = 10;
}

void BaseExplosion::Update() {
    _diff = (int) (totalMSec - _lastTimePoint);
    for(auto &entry: hitList){
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
    _lastTimePoint = totalMSec;
    _ttl -= _diff;
    if (_ttl != 0) {
        _ttl -= (int) _diff;
        if (_ttl <= 0) {
            _alive = false;
        }
    }
}

void BaseExplosion::Render() {
    if (_alive && onScreen()) {
        Point pos = CT::getPosOnScreen(_position);

        Rect srcRect = *TdTileHandler::getProjectileSrcRect(_type, totalMSec);
        float sizeW = ((float) scale / 64 * (float) _size / 100.0f) * (float) srcRect.w;
        float sizeH = ((float) scale / 64 * (float) _size / 100.0f) * (float) srcRect.h;
        float angle = (float) _direction / 180.0f * (float) M_PI;
        float sinAngle = sin(angle);
        float cosAngle = cos(angle);
        int xFix = (int) (-sizeW * 0.5 - sinAngle * sizeW);
        int yFix = (int) ((cosAngle - 1) * 0.5 * sizeH);
        Rect dstRect = {pos.x + xFix, pos.y + yFix, (int) sizeW, (int) sizeH};
        rh->tile(&dstRect, 360 - (totalMSec % 360), TdTileHandler::getProjectileSrcRect(_type, totalMSec));
        dstRect.y = pos.y;
        dstRect.x = pos.x;
        dstRect.w = 5;
        dstRect.h = 5;
        rh->fillRect(&dstRect, BLACK);
    }
}

void BaseExplosion::collide() {
}

bool BaseExplosion::collision(std::shared_ptr<Enemy> e) {
    bool inList = false;
    for(auto &entry: hitList){
        if(entry.enemy == e) {
            inList = true;
            break;
        }
    }
    if(!inList && Projectile::collision(e)){
        hitList.push_back({e,250});
        return true;
    }
    return false;
}

BaseExplosion::BaseExplosion(BaseExplosion &p, std::shared_ptr<Enemy> e, uint16_t direction) : Projectile(p, e, direction) {

}

BaseExplosion::BaseExplosion(SDL_FPoint pos, int exdmg) : BaseExplosion(){
    _direction = 0;
    _position = pos;
    _damage = exdmg;
}

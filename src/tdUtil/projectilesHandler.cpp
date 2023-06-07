//
// Created by dex on 5/26/23.
//

#include "projectilesHandler.h"

void ProjectilesHandler::set() {
    this->_texture = t_cache->get(BasePath "asset/graphic/td/tileTD.png");
}

void ProjectilesHandler::Render(const u32 frame, const u32 totalMSec, const float deltaT) {
    for (auto& p : _projectiles) {
        FPoint pos = Map::getPrecisePosOnScreen(p._position);
        int size = (int)((float)scale * (float)p._size / 100.0f);
        if (p._alive && onScreen(pos, size)) {
            Rect dstRect = { (int)pos.x, (int)pos.y, size, size };
            t_cache->render(_texture, &dstRect, p._direction, TdTileHandler::getSrcRect(p._type, totalMSec));
        }
    }
}

void ProjectilesHandler::add(Projectile p) {
    for (int i = 0; i < MAXPROJECTILES; i++) {
        if (!_projectiles[i]._alive) {
            _projectiles[i] = p;
            _projectiles[i]._alive = true;
            return;
        }
    }
    if (overflow >= MAXPROJECTILES)
        overflow = 0;
    _projectiles[overflow] = p;
    _projectiles[overflow++]._alive = true;
}

void ProjectilesHandler::remove(Projectile &p) {
    switch (p._type) {
        case Projectile::ARROW:
            p._alive = false;
            break;
        case Projectile::BULLET:
            break;
        case Projectile::FFIRE:
            p._alive = false;
            break;
        case Projectile::BASEEXPLOSION:
            break;
    }
    return;
}

void ProjectilesHandler::move() {
    for (int i = 0; i < MAXPROJECTILES; i++) {
        if (_projectiles[i]._alive) {
            switch (_projectiles[i]._type) {
                case (Projectile::Type::ARROW):
                    moveArrow(&_projectiles[i]);
                    break;
                case (Projectile::Type::BULLET):
                    moveBullet(&_projectiles[i]);
                    break;
                case (Projectile::Type::BASEEXPLOSION):
                    break;
                case (Projectile::Type::FFIRE):
                    if (_projectiles[i]._moveable)
                        moveFFire(&_projectiles[i]);
                    break;
                default:
                    cout << "Projectile Move-Error: Projectile not valid: " << _projectiles[i]._type << endl;
            }
        }
        //checking if Projectile still alive?
        if (_projectiles[i]._ttl > 0)
            _projectiles[i]._ttl--;
        else
            _projectiles[i]._alive = false;
    }
}

void ProjectilesHandler::moveBullet(Projectile* p) {
    cerr << "Bullet movement is not implemented" << endl;
}

void ProjectilesHandler::moveArrow(Projectile* p) {
    auto direction = (float)(((double)(p->_direction % 360) / 180.0f) * M_PI);
    float speed = (float)(((float)p->_speed) *0.01);
    p->_position.x += (sin(direction) * speed);
    p->_position.y += (cos(direction) * speed);
}

bool ProjectilesHandler::onScreen(FPoint& posOnScreen, int& size) {
    return (posOnScreen.x + size > 0) &&      // left
        (posOnScreen.y + size > 0) &&             // top
        (posOnScreen.y < windowSize.y) &&        // bot
        (posOnScreen.x < windowSize.x);         // right
}

void ProjectilesHandler::moveFFire(ProjectilesHandler::Projectile* p) {
    if (p->_ttl < 30)
        p->_moveable = false;

    auto direction = (float) (((double) (p->_direction % 360) / 180.0f) * M_PI);
    float speed = (float) p->_speed / 100.0f;
    p->_position.x += (sin(direction) * speed);
    p->_position.y += (cos(direction) * speed);
}
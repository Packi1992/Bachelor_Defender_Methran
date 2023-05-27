//
// Created by dex on 5/26/23.
//

#include "projectilesHandler.h"

void ProjectilesHandler::set(Map *m) {
    _map = m;
    this->_texture = t_cache->getTexture("../asset/graphic/td/tileTD.png");
}

void ProjectilesHandler::Render(const u32 frame, const u32 totalMSec, const float deltaT) {
    for (auto &p: _projectiles) {
        if (p._alive) {
            int y = p._position.y - _map->offset->y;
            int x = p._position.x - _map->offset->x;
            int size = (int) ((float) _map->scale * (float) p._size / 100.0f);
            Rect dstRect = {x, y, size, size};
            /*if (!(x + _map->offset->x+ size > 0 && x + _map->offset->x < _map->width * _map->scale) ||
                !(y + _map->offset->y+ size > 0 && y + _map->offset->y < _map->height * _map->scale)) {
                continue;
            }*/
            t_cache->render(this->_texture, &dstRect, p._direction, TdTileHandler::getSrcRect(p._type,_map->getMapTime()));
        }
    }
}

void ProjectilesHandler::add(ProjectilesHandler::Projectile p) {
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
                default:
                    cout << "Projectile Move-Error: Projectile not valid: " << _projectiles[i]._type << endl;
            }
        }
    }
}

void ProjectilesHandler::moveBullet(ProjectilesHandler::Projectile *p) {

}

void ProjectilesHandler::moveArrow(ProjectilesHandler::Projectile *p) {
    float speed = (float)p->_speed / 500.0f;
    float direction = (float)(p->_direction % 360) / 180.0f * M_PI;
    if (_map == nullptr) {
        cerr << "ProjectilesHandler needs a valid Mappointer" << endl;
    }
    speed *= _map->scale;
    p->_position.x += sin(direction) * speed;
    p->_position.y += cos(direction) * speed;
}

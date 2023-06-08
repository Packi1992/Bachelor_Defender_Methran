//
// Created by dex on 5/26/23.
//

#include "projectilesHandler.h"

void ProjectilesHandler::set() {
    this->_texture = t_cache->get(BasePath "asset/graphic/td/tileTD.png");
}

void ProjectilesHandler::Render(const u32 frame, const u32 totalMSec, const float deltaT) {
    for (auto& p : _projectiles) {
        if(p != nullptr){
            FPoint pos = CT::getPosOnScreen(p->_position);
            int size = (int)((float)scale * (float)p->_size / 100.0f);
            if (p->_alive && onScreen(pos, size)) {
                Rect dstRect = { (int)pos.x, (int)(pos.y - (float)size * 0.5f), size, size };
                rh->texture(_texture, &dstRect, p->_direction, TdTileHandler::getSrcRect(p->_type, totalMSec));
                dstRect.y += size * 0.5;
                dstRect.w = 5;
                dstRect.h = 5;
                rh->fillRect(&dstRect, BLACK);
            }
        }
    }
}

void ProjectilesHandler::add(Projectile *p) {
    for (int i = 0; i < MAXPROJECTILES; i++) {
        if (_projectiles[i] == nullptr) {
            _projectiles[i] = p;
            _projectiles[i]->_alive = true;
            return;
        }
    }
    if (overflow >= MAXPROJECTILES)
        overflow = 0;
    delete _projectiles[overflow];
    _projectiles[overflow] = p;
    _projectiles[overflow++]->_alive = true;
}

void ProjectilesHandler::remove(Projectile **p) {
    switch ((*p)->_type) {
        case Projectile::ARROW:
            (*p)->_alive = false;
            break;
        case Projectile::BULLET:
            break;
        case Projectile::FFIRE:
            (*p)->_alive = false;
            break;
        case Projectile::BASEEXPLOSION:
            break;
        case Projectile::DISABLED:
            cerr << "you removed a disabled Projectile";
    }
    if(!(*p)->_alive){
        delete *p;
        *p = nullptr;
    }
}

void ProjectilesHandler::move() {
    for (int i = 0; i < MAXPROJECTILES; i++) {
        if(_projectiles[i] != nullptr ) {
            if (_projectiles[i]->_alive) {
                _projectiles[i]->move();
            }
            //checking if Projectile still alive?
            if (_projectiles[i]->_ttl > 0)
                _projectiles[i]->_ttl--;
            else
                _projectiles[i]->_alive = false;
        }
    }
}

bool ProjectilesHandler::onScreen(Point& posOnScreen, int& size) {
    return (posOnScreen.x + size > 0) &&      // left
        (posOnScreen.y + size > 0) &&             // top
        (posOnScreen.y < windowSize.y) &&        // bot
        (posOnScreen.x < windowSize.x);         // right
}

ProjectilesHandler::~ProjectilesHandler() {
    for (int i = 0; i < MAXPROJECTILES; i++) {
        if (_projectiles[i] != nullptr) {
            delete _projectiles[i];
        }
    }
}

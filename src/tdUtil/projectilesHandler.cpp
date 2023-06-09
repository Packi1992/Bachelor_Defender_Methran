//
// Created by dex on 5/26/23.
//

#include "projectilesHandler.h"
#include "../td/Projectiles/projectile.h"

void ProjectilesHandler::set() {
    this->_texture = t_cache->get(BasePath "asset/graphic/td/tileTD.png");
}

void ProjectilesHandler::Render(const u32 totalMSec) {
    for (auto& p : _projectiles) {
        if(p != nullptr){
            p->Render(totalMSec);
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
    float x = (CT::getPosOnScreen((*p)->_position).x) / float(windowSize.x);
    switch ((*p)->_type) {
        case ProjectileType::ARROW:
            (*p)->_alive = false;
            audioHandler->playSound(SoundArrowHit, x);
            break;
        case ProjectileType::BULLET:
            break;
        case ProjectileType::FFIRE:
            (*p)->_alive = false;
            break;
        case ProjectileType::BASEEXPLOSION:
            break;
        case ProjectileType::DISABLED:
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

ProjectilesHandler::~ProjectilesHandler() {
    for (int i = 0; i < MAXPROJECTILES; i++) {
        if (_projectiles[i] != nullptr) {
            delete _projectiles[i];
        }
    }
}

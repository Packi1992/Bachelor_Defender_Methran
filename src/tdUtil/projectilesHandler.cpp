//
// Created by dex on 5/26/23.
//

#include "projectilesHandler.h"
#include "../td/Projectiles/projectile.h"

void ProjectilesHandler::set() {
    this->_texture = t_cache->get(BasePath "asset/graphic/td/tileTD.png");
}

void ProjectilesHandler::Render() {
    for (auto &p: _projectiles) {
        if (p != nullptr) {
            p->Render();
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

void ProjectilesHandler::collisionDetected(Projectile **p) {

}

void ProjectilesHandler::Update() {
    for (int i = 0; i < MAXPROJECTILES; i++) {
        if (_projectiles[i] != nullptr) {
            if (_projectiles[i]->_alive) {
                _projectiles[i]->move();
            }

            //checking if Projectile still alive?
            cout << "projectile " << i << " ttl: " << _projectiles[i]->_ttl << endl;
            if (--_projectiles[i]->_ttl <= 0) {
                _projectiles[i]->_alive = false;
                delete _projectiles[i];
                _projectiles[i] = nullptr;
            }


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

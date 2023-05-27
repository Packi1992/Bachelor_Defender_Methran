//
// Created by banoodle on 27.05.23.
//

#include "enemyHandler.h"

EnemyHandler::EnemyHandler() {
    this->_texture = t_cache->get("../asset/graphic/td/tileTD.png");
}

void EnemyHandler::Render() {
    for (int i = 0; i < MAXENEMIES; i++) {
        if (_enemies[i]._alive) {
            updateDstRect(_enemies[i]);
            if (onScreen()){
                updateSrcRect(_enemies[i]);
                t_cache->render(_texture, &dstRect, _enemies[i]._dir+180, &srcRect);
            }

        }
    }
}

bool EnemyHandler::onScreen() const {
    return (dstRect.x + dstRect.w > 0) &&        // left
           (dstRect.y + dstRect.h > 0) &&        // top
           (dstRect.y < windowSize.y) &&        // bot
           (dstRect.x < windowSize.x);         // right
}

void EnemyHandler::updateSrcRect(Enemy &e) {
    // get maptime using global
    srcRect = {0, 0, 64, 128};
    switch (e._type) {
        case Ordinary:
        case Fast:
        case Silly:
        case Strong:
        case Boss:
            srcRect.y = 6 * 64;
            break;
    }
}

void EnemyHandler::updateDstRect(Enemy &enemy) {
    Point posOnScreen = enemy._pos;
    dstRect.x = posOnScreen.x-offset.x-scale/2;
    dstRect.y = posOnScreen.y-offset.y-(scale);
    dstRect.w = scale;
    dstRect.h = 2 * scale;
}

void EnemyHandler::Update() {
    for (int i = 0; i < MAXENEMIES; i++) {
        if (_enemies[i]._alive) {
            _enemies[i].Update();
        }
    }
}

void EnemyHandler::UnInit() {
    for (int i = 0; i < MAXENEMIES; i++) {
        _enemies[i]._alive = false;
    }
}

void EnemyHandler::addEnemy(Enemy e) {
    for (int i = 0; i < MAXENEMIES; i++) {
        if (!_enemies[i]._alive) {
            _enemies[i] = e;
            _enemies[i]._alive = true;
            cout << "enemy added" << endl;
            return;

        }
    }
    if (overflow >= MAXENEMIES)
        overflow = 0;
    cout << "Overflow! enemy added anyway" << endl;
    _enemies[overflow] = e;
    _enemies[overflow++]._alive = true;
}



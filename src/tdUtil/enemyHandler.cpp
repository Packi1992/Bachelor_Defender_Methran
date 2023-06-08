//
// Created by banoodle on 27.05.23.
//

#include "enemyHandler.h"

EnemyHandler::EnemyHandler() {
    this->_texture = t_cache->get(BasePath "asset/graphic/td/tileTD.png");
}

void EnemyHandler::Render() {
    for (auto & enemy : _enemies) {
        if (enemy._alive) {
            updateDstRect(enemy);
            if (onScreen()){
                updateSrcRect(enemy);
                t_cache->render(_texture,&dstRect,&srcRect);
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
    // get map time using global
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
    dstRect.w = scale;
    dstRect.h = scale + scale;
    PosOnScreen = CT::getPosOnScreen(enemy._pos);

    dstRect.x = (int)(PosOnScreen.x-dstRect.w*0.5);
    dstRect.y = (int)(PosOnScreen.y-dstRect.h*0.8);

}

void EnemyHandler::Update(const float deltaT) {
    for (auto & enemy : _enemies) {
        if (enemy._alive) {
            enemy.Update(deltaT);
        }
    }
}

void EnemyHandler::UnInit() {
    for (auto & enemy : _enemies) {
        enemy._alive = false;
    }
}

void EnemyHandler::addEnemy(Enemy e) {
    for (auto & enemy : _enemies) {
        if (!enemy._alive) {
            enemy = e;
            enemy._alive = true;
            return;

        }
    }
    if (overflow >= MAXENEMIES)
        overflow = 0;
    _enemies[overflow] = e;
    _enemies[overflow++]._alive = true;
}
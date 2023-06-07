//
// Created by banoodle on 27.05.23.
//

#include "enemyHandler.h"

EnemyHandler::EnemyHandler() {
    this->_texture = t_cache->get(BasePath "asset/graphic/td/tileTD.png");
}

void EnemyHandler::Render() {
    for (int i = 0; i < MAXENEMIES; i++) {
        if (_enemies[i]._alive) {
            updateDstRect(_enemies[i]);
            if (onScreen()){
                updateSrcRect(_enemies[i]);
                //t_cache->renderRect(&dstRect,BLACK);
                //t_cache->render(_texture, &dstRect, _enemies[i]._dir+180, &srcRect);
                t_cache->render(_texture,&dstRect,&srcRect);
                t_cache->renderFillRect(&dstRect, BLACK);
            }
        }
    }
}

bool EnemyHandler::onScreen() const {
    //cout << "dstRect -> " << dstRect.x << " " << dstRect.y << endl;
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
    dstRect.w = scale;
    dstRect.h = scale + scale;
    precisePosOnScreen = Map::getPrecisePosOnScreen(enemy._pos);
    dstRect.x = (int)(precisePosOnScreen.x-dstRect.w/2.0);
    dstRect.y = (int)(precisePosOnScreen.y-dstRect.h*0.8);

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
            return;

        }
    }
    if (overflow >= MAXENEMIES)
        overflow = 0;
    _enemies[overflow] = e;
    _enemies[overflow++]._alive = true;
}

bool EnemyHandler::isPointInside(Point p, Enemy e) {
    updateDstRect(e);
    Point po = {p.x - offset.x,p.y - offset.y};
    bool inside = SDL_PointInRect(&po, &dstRect);
    return inside;
}
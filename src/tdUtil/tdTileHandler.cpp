//
// Created by banoodle on 17.05.23.
//

#include "tdTileHandler.h"

#include "../global.h"

MapObjects TdTileHandler::selectObject(int i) {
    if (i >= 0 && i <= OBJECTCOUNT) {
        return static_cast<MapObjects>(i);
    }
    return Empty;
}

Rect TdTileHandler::src = {0, 0, 0, 0};
int TdTileHandler::localAnimate=0;
int TdTileHandler::TOOLCOUNT = 6;
int TdTileHandler::OBJECTCOUNT = 9;


Rect *TdTileHandler::getSrcRect(MapObjects o, ul animate) {
    src = {0, 0, 64, 64};

    switch (o) {
        case Tower:
        case Empty:
            src.x = 9*64;
            src.y = 0;
            break;
        case Start:
            src.y = 0;
            localAnimate = (int)((animate / 8) % 10);
            if(localAnimate>=5){
                localAnimate = 9-localAnimate;
            }
            src.x = localAnimate  * 64;
            break;
        case Goal:
            localAnimate = (int)(((animate+30) / 8) % 10);
            if(localAnimate>=5){
                localAnimate = 9-localAnimate;
            }
            src.x = localAnimate  * 64;
            src.y = 64;
            break;
        case Table:
            src.x = 0;
            src.y = 128;
            break;
        case Chair:
            src.x = 128;
            src.y = 128;
            break;
        default:
            cerr << "Tile not found, please provide SRC rect in TdTileHandler.cpp" << endl;
    }
    return &src;
}

Rect *TdTileHandler::getSrcRect(int o, ul anim) {
    return getSrcRect(selectObject(o), anim);
}

Rect *TdTileHandler::getEnemySrcRect(EnemyType e, ul anim) {
    // get map time using global
    src = {0, 0, 64, 128};
    switch (e) {
        case Ordinary:
        case Fast:
        case Silly:
        case Strong:
        case Boss:
            src.y = 6 * 64;
            break;
    }
    return &src;
}

Rect *TdTileHandler::getTowerSrcRect(TowerType t, ul anim) {
    src = {0, 0, 64, 64};
    switch (t) {
        case Base:
            src.y = 256;
            return &src;
        case Pointer:
            src.y = 256;
            src.x = 64 + (int)(anim%4)*64;
            return &src;
    }
}

std::string TdTileHandler::getName(MapObjects object) {
    switch (object) {
        case Empty:
            return "Empty";
        case Start:
            return "Start";
        case Goal:
            return "Goal";
        case Table:
            return "Table";
        case Tower:
            return "Tower";
        case Chair:
            return "Chair";
        default:
            return "Error";
    }
}

SDL_Rect *TdTileHandler::getProjectileSrcRect(ProjectileType p, unsigned long anim) {
    src = {0, 0, 64, 64};
    switch(p){
        case ARROW:
            src = {26, 334, 11, 35};
            break;
        case FFIRE:
            localAnimate = (int)((anim / 4) % 2);
            src.x = 64+(localAnimate* 64);
            src.y = 320;
            break;
        case DISABLED:
            cerr << "Projectile Type DISABLED has no srcRect";
            break;
        default:
            cerr << "Type not implemented";
            return nullptr;
    }
    return &src;
}






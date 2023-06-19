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
            localAnimate = (int)((animate / 80) % 10);
            if(localAnimate>=5){
                localAnimate = 9-localAnimate;
            }
            src.x = localAnimate  * 64;
            break;
        case Goal:
            localAnimate = (int)(((animate+30) / 80) % 10);
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

Rect *TdTileHandler::getEnemySrcRect(EnemyType e, ul anim, Direction d) {
    // get map time using global
    src = {0, 0, 64, 128};
    switch (e) {
        case Ordinary:
        case Fast:
        case Silly:
        case Strong:
        case Boss:
            if(d == RIGHT || d == LEFT){
                src.y = 6 * 64;
                src.x = 64 + (int)((anim/100)%10)*64;
            }else if(d == BOTTOM || d == TOP){
                src.y = 6 * 64;
                src.x = 64 + (int)((anim/100)%10)*64;
            }
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
        case RecursivBase:
            src.y = 512;
            return &src;
        case Tower_Boomerang:
            src.y = 512;
            src.x = 64 + (int)(anim%2)*64;
            return &src;
        case Tower_LinkedList:
            src.y = 576;
            src.x = 64 + (int)(anim%8)*64;
            return &src;
        case Tower_LinkedListBase:
            src.y = 576;
            return &src;
        case Hashcanon:
            src.y = 640;
            src.x = (int)(anim%4)*64;
            return &src;
        case StringTower:
            src.y = 704;
            src.x = 0;
            return &src;
        case Hashcanon_Dir:
            src.y = 640;
            src.x = 256;
            return &src;
    }
    return &src;
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
            src = {23, 335, 18, 32};
            break;
        case ARROW_FULLRECT:
            src.x = 0;
            src.y = 320;
            break;
        case LINK:
            src = {26, 334, 11, 35};
            break;
        case BOOMERANG:
            src = {216, 525, 22, 38};
            break;
        case FFIRE:
            localAnimate = (int)((anim / 40) % 2);
            src.x = 64+(localAnimate* 64);
            src.y = 320;
            break;
        case HASHBOMB:
            src = {344, 664, 16, 16};
            break;
        case BASEEXPLOSION:
            src = {384, 640, 64, 64};
            break;
        case STRINGPROJECTILE:
            src = {128, 704, 64, 95};
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






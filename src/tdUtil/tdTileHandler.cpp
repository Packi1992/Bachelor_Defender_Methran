//
// Created by banoodle on 17.05.23.
//

#include "tdTileHandler.h"

TdTileHandler::MapObjects TdTileHandler::selectObject(int i) {
    if (i >= 0 && i <= OBJECTCOUNT) {
        return static_cast<MapObjects>(i);
    }
    return Empty;
}

Rect TdTileHandler::src = {0, 0, 0, 0};
int TdTileHandler::TOOLCOUNT = 6;
int TdTileHandler::OBJECTCOUNT = 8;


Rect *TdTileHandler::getSrcRect(TdTileHandler::MapObjects o, long animate) {
    src = {0, 0, 64, 64};
    int localAnimate;
    switch (o) {
        case Tower:
            localAnimate = (int)((animate / 4) % 5);
            src.x = 64+(localAnimate* 64);
            src.y = 256;
            break;
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
        case ARROW:
            src.x = 128;
            src.y = 128;
            break;
    }
    return &src;
}

Rect *TdTileHandler::getSrcRect(int o, long anim) {
    return getSrcRect(selectObject(o), anim);
}

std::string TdTileHandler::getName(TdTileHandler::MapObjects object) {
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
        case ARROW:
            return "Arrow";
        default:
            return "Error";
    }
}


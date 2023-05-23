//
// Created by banoodle on 17.05.23.
//

#include "tdTileHandler.h"

TdTileHandler::MapObjects TdTileHandler::selectObject(int i) {
    if (i >= 0 && i <= 3) {
        return static_cast<MapObjects>(i);
    }
    return Empty;
}

Rect TdTileHandler::src = {0,0,0,0};

Rect *TdTileHandler::getSrcRect(TdTileHandler::MapObjects o, long anim) {
    src = {0,0,50,50};
    switch (o) {
        case Empty:
            src.x = 0;
            src.y = 0; // 0-49
            break;
        case Start:
            src.x = 0;
            src.y = 50; // 50-99
            break;
        case Goal:
            src.x = 0;
            src.y = 100; // 100-149
            break;
        case Table:
            src.x = 0;
            src.y = 150; // 150-199
            break;
    }
    return &src;
}

Rect *TdTileHandler::getSrcRect(int o, long anim) {
    return getSrcRect(selectObject(o),anim);
}

std::string TdTileHandler::getName(TdTileHandler::MapObjects object) {
    switch(object) {
        case Empty:
            return "Empty";
        case Start:
            return "Start";
        case Goal:
            return "Goal";
        case Table:
            return "Table";
        default:
            return "Error";
    }
}


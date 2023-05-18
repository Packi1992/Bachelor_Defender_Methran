//
// Created by banoodle on 17.05.23.
//

#ifndef SDL_BACHELOR_DEFENDER_TD_TILE_HANDLER_H
#define SDL_BACHELOR_DEFENDER_TD_TILE_HANDLER_H

#include "../../global.h"
#include <string>

// using Tile png with Tile Size 50px x 50px
class tdTileHandler {
public:
    enum MapObjects{
        Empty,
        Start,
        Goal,
        Table
    };
    static MapObjects selectObject(int i);

    static Rect *getSrcRect(MapObjects o, long anim=0);

    static Rect *getSrcRect(int o, long anim=0);

    static std::string getName(MapObjects objects);
private:
    static Rect src;
};


#endif //SDL_BACHELOR_DEFENDER_TD_TILE_HANDLER_H

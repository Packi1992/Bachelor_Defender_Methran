//
// Created by banoodle on 17.05.23.
//

#ifndef SDL_BACHELOR_DEFENDER_TD_TILE_HANDLER_H
#define SDL_BACHELOR_DEFENDER_TD_TILE_HANDLER_H

#include "../global.h"

// using Tile png with Tile Size 50px x 50px
class TdTileHandler {
public:
    static int TOOLCOUNT;
    static int OBJECTCOUNT;
    enum MapObjects{
        Empty,
        Start,
        Goal,
        Table,
        Tower,
        Chair,
        ARROW,
        BULLET,
    };
    static MapObjects selectObject(int i);

    static Rect *getSrcRect(MapObjects o, long anim=0);

    static Rect *getSrcRect(int o, long anim=0);

    static std::string getName(MapObjects objects);
private:
    static Rect src;
};


#endif //SDL_BACHELOR_DEFENDER_TD_TILE_HANDLER_H

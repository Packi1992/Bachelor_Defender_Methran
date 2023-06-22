//
// Created by banoodle on 17.05.23.
//

#ifndef SDL_BACHELOR_DEFENDER_TD_TILE_HANDLER_H
#define SDL_BACHELOR_DEFENDER_TD_TILE_HANDLER_H

#include <SDL_render.h>
#include <string>
#include "../util/enums.h"

// using Tile png with Tile Size 50px x 50px
class TdTileHandler {
public:
    static int TOOLCOUNT;
    static int OBJECTCOUNT;

    static MapObjects selectObject(int i);

    static SDL_Rect *getSrcRect(MapObjects o, unsigned long anim = 0);

    static SDL_Rect *getSrcRect(int o, unsigned long anim = 0);

    static SDL_Rect *getEnemySrcRect(EnemyType e, unsigned long anim = 0, Direction d = RIGHT);

    static SDL_Rect *getProjectileSrcRect(ProjectileType p, unsigned long anim = 0);

    static SDL_Rect *getTowerSrcRect(TowerType t, unsigned long anim = 0);

    static std::string getName(MapObjects objects);

private:
    static SDL_Rect src;
    static int localAnimate;
};


#endif //SDL_BACHELOR_DEFENDER_TD_TILE_HANDLER_H

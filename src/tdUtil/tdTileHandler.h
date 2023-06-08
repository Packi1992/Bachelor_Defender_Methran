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
    enum EnemyType{
        Ordinary,
        Fast,
        Silly,
        Strong,
        Boss,
    };
    enum MapObjects{
        Empty,
        Start,
        Goal,
        Table,
        Tower,
        Chair,
        // Projectiles
        ARROW,
        BULLET,
        // Particles
        BASEEXPLOSION,
        FFIRE,
    };
    enum TowerType{
        Base,
        Pointer,
    };
    static MapObjects selectObject(int i);

    static Rect *getSrcRect(MapObjects o, ul anim=0);
    static Rect *getSrcRect(int o, ul anim=0);

    static Rect *getEnemySrcRect(EnemyType e, ul anim=0);

    static Rect *getTowerSrcRect(TowerType t, ul anim=0);

    static std::string getName(MapObjects objects);

private:
    static Rect src;
};


#endif //SDL_BACHELOR_DEFENDER_TD_TILE_HANDLER_H

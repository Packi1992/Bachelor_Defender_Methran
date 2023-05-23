//
// Created by banoodle on 17.05.23.
//

#ifndef SDL_BASEGAME_MAP_H
#define SDL_BASEGAME_MAP_H

#include "../../global.h"
#include "../../gamebase.h"
#include "tdTileHandler.h"
#include "../../util/TextureCache.h"

class Map {
public:
    Map();

    void load(const std::string &path = "../Maps/testMap.map");

    void save(const std::string &path = "../Maps/neueMap");

    void draw(bool wire = false);
    void drawWire();
    void set(Renderer *render, const Point *offset);

    void set(Event, TdTileHandler::MapObjects);
    TdTileHandler::MapObjects getObjectAtScreenPos(Point p);
    void showSizeDialog();
    SDL_Point getPosOnScreen(Point p);
    TdTileHandler::MapObjects getObject(Point p, bool OutOfBoundsError=true);
    u_long getMapTime();

    int scale = 30;
    int width = 40;
    int height = 20;

private:
    Renderer *render={};
    SDL_Texture *t_tile={};
    TextureCache* t_cache={};
    const Point *offset={};
    u_long time=0;

    std::vector<std::vector<TdTileHandler::MapObjects>> map;
};


#endif //SDL_BASEGAME_MAP_H

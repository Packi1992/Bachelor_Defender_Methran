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

    void showSizeDialog();

    u_long getMapTime();

private:
    Renderer *render={};
    SDL_Texture *t_tile={};
    TextureCache* t_cache={};
    const Point *offset={};
    u_long time=0;
    int scale = 30;
    int width = 40;
    int height = 20;
    std::vector<std::vector<TdTileHandler::MapObjects>> map;
};


#endif //SDL_BASEGAME_MAP_H

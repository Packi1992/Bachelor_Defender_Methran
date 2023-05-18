//
// Created by banoodle on 17.05.23.
//

#ifndef SDL_BASEGAME_MAP_H
#define SDL_BASEGAME_MAP_H

#include "../../global.h"
#include "../../gamebase.h"

class Map {
public:
    Map();

    void load(const std::string &path = "../Maps/testMap.map");

    void save(const std::string &path = "../Maps/neueMap");

    void draw(bool wire = false);

    void setMap(Game *game, std::string path);

    void showSizeDialog();

private:
    SDL_Texture *t_tile;
    int scale = 30;
    int width = 40;
    int height = 20;
    std::vector<std::vector<MapObjects>> map;
};


#endif //SDL_BASEGAME_MAP_H

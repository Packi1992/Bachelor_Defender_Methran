//
// Created by banoodle on 17.05.23.
//

#ifndef SDL_BASEGAME_MAP_H
#define SDL_BASEGAME_MAP_H


#include "../gamebase.h"
#include "tdTileHandler.h"
#include <iostream>
#include <fstream>

class Map {
public:
    Map();

    void load(const std::string &path = "../Maps/testMap.map");

    void save(const std::string &path = "../Maps/neueMap");

    void draw(bool wire = false);
    void drawWire();
    void set(Point *offset);

    void set(Event, TdTileHandler::MapObjects);
    TdTileHandler::MapObjects getObjectAtScreenPos(Point p);
    void showSizeDialog();
    Point getPosOnScreen(Point p);
    TdTileHandler::MapObjects getObject(Point p, bool OutOfBoundsError=true);
    u_long getMapTime();

    int scale = 30;
    int width = 40;
    int height = 20;
    Point *offset={};
private:
    Texture *t_tile={};
    u_long time=0;
    void resizeMap();

    void loadRow(std::string basicString);

    std::vector<std::vector<TdTileHandler::MapObjects>> map;

    void iniOffset();
};


#endif //SDL_BASEGAME_MAP_H

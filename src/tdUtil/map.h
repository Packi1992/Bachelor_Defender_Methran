//
// Created by banoodle on 17.05.23.
//

#ifndef SDL_BASEGAME_MAP_H
#define SDL_BASEGAME_MAP_H


#include "../gamebase.h"
#include "tdTileHandler.h"
#include <fstream>

class Map {
public:
    Map();

    void load(const string &path = "../Maps/neueMap.map");

    void save(const string &path = "../Maps/neueMap");

    void Render(bool wire = false);

    void setTile(Event event, MapObjects object);
    MapObjects getObjectAtScreenPos(Point p);
    void showSizeDialog();
    Point getPosOnScreen(Point p);
    MapObjects getObject(Point p, bool OutOfBoundsError=true);
    [[nodiscard]] u_long getMapTime() const;

    int width = 40;
    int height = 20;
private:
    Texture *t_tileMap={};
    ul time=0;
    void resizeMap();
    void drawWire() const;

    void loadRow(std::string basicString);

    std::vector<std::vector<TdTileHandler::MapObjects>> map;

    void iniOffset();
};


#endif //SDL_BASEGAME_MAP_H

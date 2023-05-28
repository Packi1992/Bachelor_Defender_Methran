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
    void Render(bool wire = false);
    void Update(const u32 frame, const u32 totalMSec, const float deltaT );

    void load(const string &path = "../Maps/neueMap.map");
    void save(const string &path = "../Maps/neueMap");

    static Point getPosOnScreen(Point p);
    static FPoint getPrecisePosOnScreen(FPoint &fp);
    static FPoint getPreciseCenterOfPos(Point &p);
    Point getNextPos(Point p);
    Point getNextPos(FPoint p);

    void setTile(Event event, MapObjects object);
    MapObjects getObjectAtScreenPos(Point p);
    void showSizeDialog();

    MapObjects getObject(Point p, bool OutOfBoundsError=true);
    [[nodiscard]] ul getMapTime() const;

    int _width = 40;
    int _height = 20;

    unsigned long getMapTimeDiff();

private:
    Texture *_tileMap={};
    u32 _time=0;
    float _deltaTime=0;
    u32 _lastTime=0;
    void resizeMap();
    void drawWire() const;

    void loadRow(string basicString);

    Vector<Vector<MapObjects>> _map;
    Vector<Vector<Point>> _pathMap;

    void iniOffset() const;

    void updatePathFinding();
};


#endif //SDL_BASEGAME_MAP_H

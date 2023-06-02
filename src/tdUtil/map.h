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
    void Render(bool wire = false, bool path = false);
    void Update(const u32 frame, const u32 totalMSec, const float deltaT );

    void load(const string &path = BasePath"Maps/neueMap.map");
    void save(const string &path = BasePath"Maps/neueMap");

    static Point getPosOnScreen(Point p);
    static FPoint getPrecisePosOnScreen(FPoint &fp);
    static FPoint getPreciseCenterOfPos(Point &p);
    Point getNextPos(Point p);
    Point getNextPos(FPoint p);

    void setTile(Event event, MapObjects object);
    void setTile(Point p, MapObjects object);
    MapObjects getObjectAtScreenPos(Point p);
    void resize(Point size={-1,-1});

    MapObjects getObject(Point p, bool OutOfBoundsError=true);
    MapObjects getObject(FPoint p, bool OutOfBoundsError=true);
    [[nodiscard]] ul getMapTime() const;

    int _width = 40;
    int _height = 20;

    unsigned long getMapTimeDiff();

private:
    struct PathEntry{
        Point pos;
        bool blocked;
        bool goal;
        bool set;
    };
    Texture *_tileMap={};
    Texture *_blocked={};
    Texture *_arrow{};
    u32 _time=0;
    float _deltaTime=0;
    u32 _lastTime=0;
    void drawWire() const;

    void loadRow(string basicString);

    Vector<Vector<MapObjects>> _map;
    Vector<Vector<PathEntry>> _pathMap;

    void iniOffset() const;

    void updatePathFinding();

    bool isBlocked(int i, int j);

    void evaluatePath(int x, int y);

    void setPathEntry(int x, int y, int i, int y1);

    static u16 getDir(int ex, int ey, int tx, int ty);
};


#endif //SDL_BASEGAME_MAP_H

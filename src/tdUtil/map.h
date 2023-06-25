//
// Created by banoodle on 17.05.23.
//

#ifndef SDL_BASEGAME_MAP_H
#define SDL_BASEGAME_MAP_H


#include "../util/gamebase.h"
#include "tdTileHandler.h"
#include <fstream>

class Map {
public:
    Map();
    ~Map();

    void Render(bool wire = false, bool path = false);

    void Update();

    bool load(const Vector<string> &data);

    string save();

    // used by editor
    Point getNextPos(Point p);

    // used in game
    FPoint getNextPosCentre(FPoint p);

    void setTile(Event &event, MapObjects object);

    void setTile(Point p, MapObjects object);

    MapObjects getObjectAtScreenPos(Point &p);

    void resize(Point size = {-1, -1});

    MapObjects getObject(Point p, bool OutOfBoundsError = true);

    MapObjects getObject(FPoint p, bool OutOfBoundsError = true);

    int _width = 40;
    int _height = 20;

    bool checkPath(Point pos);
    Point getStartPoint(int i);

    bool blockingTile(Point point);

    void RenderBG(bool wire);

    void RenderRow(int row);

    void RenderPath();

    void RenderPathRow(int i);

    void RenderFrontWall();

private:
    struct PathEntry {
        Point pos;
        bool blocked;
        bool goal;
        bool set;
    };

    Vector<Point> _startPoints{};
    Texture *_tileMap = {};
    Texture *_frontWall = {};
    Texture *_blocked = {};
    Texture *_arrow{};

    void drawWire() const;

    void loadRow(string basicString);

    Vector<Vector<MapObjects>> _map;
    Vector<Vector<PathEntry>> _pathMap;

    void iniOffset() const;

    bool updatePathFinding();

    bool isBlocked(int i, int j);

    bool evaluatePath(int x, int y);

    void setPathEntry(int x, int y, int i, int y1);

    static u16 getDir(int ex, int ey, int tx, int ty);

    void CheckEnemiesPath(Point point);
};


#endif //SDL_BASEGAME_MAP_H

//
// Created by banoodle on 17.05.23.
//

#include "map.h"
#include "../td/testtd.h"

Map::Map() {
    this->_height = 8;
    this->_width = 16;
    _tileMap = t_cache->get(BasePath "asset/graphic/td/tileTD.png");
    _blocked = t_cache->get(BasePath "asset/graphic/editor/blocked.png");
    _arrow = t_cache->get(BasePath "asset/graphic/editor/arrow.png");
    this->_map = std::vector(_width, Vector<MapObjects>(_height));
    this->_pathMap = std::vector(_width, Vector<PathEntry>(_height));
}

void Map::resize(Point size) {
    if (!(size.x == -1 && size.y == -1)) {
        _width = size.x;
        _height = size.y;
    }

    cout << "resize Map to Width = " << _width << " Height = " << _height << endl;
    _map.resize(_width);
    _pathMap.resize(_width);
    for (int i = 0; i < _width; i++) {
        _map[i].resize(_height);
        _pathMap[i].resize(_height);
    }
    updatePathFinding();
}

void Map::RenderBG(bool wire) {
    if (wire)
        drawWire();
}

void Map::RenderRow(int row) {
    Rect dstRect;
    int y = (row * scale) - offset.y;
    for (int i = 0; i < _width; i++) {
        int x = (i * scale) - offset.x;
        if (x + scale > 0 && x < windowSize.x && y + scale > 0 && y < windowSize.y) {
            dstRect = {x, y, scale, scale};
            switch (_map[i][row]) {
                case MapObjects::Goal:
                case MapObjects::Tower:
                case MapObjects::Start:
                    rh->texture(_tileMap, &dstRect, TdTileHandler::getSrcRect(MapObjects::Empty));
                    break;
            }
            rh->texture(_tileMap, &dstRect, TdTileHandler::getSrcRect(_map[i][row], totalMSec));
        }
    }
}

void Map::RenderPath() {
    Rect dstRect;
    for (int i = 0; i < _width; i++) {
        int x = (i * scale) - offset.x;
        for (int j = 0; j < _height; j++) {
            int y = (j * scale) - offset.y;
            dstRect = {x, y, scale, scale};
            //Point p= {i,j};
            PathEntry e = _pathMap[i][j];
            if (e.blocked)
                rh->texture(_blocked, &dstRect);
            else if (!e.set && !e.goal) {
                dstRect.x += scale / 6;
                dstRect.y += scale / 6;
                dstRect.w -= scale / 3;
                dstRect.h -= scale / 3;
                rh->fillRect(&dstRect, YELLOW);
                dstRect = {x, y, scale, scale};

            } else if (e.goal) {
                continue;
            } else {
                rh->texture(_arrow, &dstRect, getDir(i, j, e.pos.x, e.pos.y));
            }
        }
    }
}

void Map::RenderPathRow(int yx) {
    Rect dstRect;
    for (int i = 0; i < _width; i++) {
        int x = (i * scale) - offset.x;
        int y = (yx * scale) - offset.y;
        dstRect = {x, y, scale, scale};
        //Point p= {i,j};
        PathEntry e = _pathMap[i][yx];
        if (e.blocked)
            rh->texture(_blocked, &dstRect);
        else if (!e.set && !e.goal) {
            dstRect.x += scale / 6;
            dstRect.y += scale / 6;
            dstRect.w -= scale / 3;
            dstRect.h -= scale / 3;
            rh->fillRect(&dstRect, YELLOW);
            dstRect = {x, y, scale, scale};

        } else if (e.goal) {
            continue;
        } else {
            rh->texture(_arrow, &dstRect, getDir(i, yx, e.pos.x, e.pos.y));
        }

    }
}

void Map::drawWire() const {
    rh->setColor(MAP_GRID);
    Point p1, p2;

    p1.y = -offset.y;
    p2.y = _height * scale - offset.y;
    for (int i = 0; i <= _width; i++) {
        p1.x = p2.x = i * scale - offset.x;
        rh->line(p1, p2);
    }
    p1.x = 0 - offset.x;
    p2.x = _width * scale - offset.x;
    for (int j = 0; j <= _height; j++) {
        p1.y = p2.y = j * scale - offset.y;
        rh->line(p1, p2);
    }
}

string Map::save() {
    // save pMap!
    std::stringstream s;
    //checkPlayerStartSpot();
    s << "WIDTH :" << _width << "\n";
    s << "HEIGHT:" << _height << "\n";
    s << "ARRAY :\n";
    for (int j = 0; j < _height; j++) {
        s << "ROW " << j << ";";
        for (int i = 0; i < _width; i++) {
            s << _map[i][j] << "; ";
        }
        s << "\n";
    }
    return s.str();
}

void Map::loadRow(string line) {
    unsigned long token = line.find(';');
    int row = (int) strtol(line.substr(4, token).c_str(), nullptr, 10);
    for (int i = 0; i < _width; i++) {
        line.erase(0, token + 1);
        token = line.find(';');
        int o = (int) strtol(line.substr(0, token).c_str(), nullptr, 10);
        _map[i][row] = TdTileHandler::selectObject(o);
    }
}

bool Map::load(const Vector<string> &data) {
    bool widthLoaded = false;
    bool heightLoaded = false;
    bool meta = true;
    // now we need to load lines out of Map string
    for (const string &line: data) {
        if (!meta) {
            loadRow(line);
        }
        if (meta && line.substr(0, 7) == ("WIDTH :")) {
            _width = (int) strtol(line.substr(7).c_str(), nullptr, 10);
            widthLoaded = true;
        } else if (meta && (line.substr(0, 7) == ("HEIGHT:"))) {
            _height = (int) strtol(line.substr(7).c_str(), nullptr, 10);
            heightLoaded = true;
        } else if (meta && line.substr(0, 7) == ("ARRAY :")) {
            if (!widthLoaded || !heightLoaded) {
                std::cerr << "Map Data corrupted" << std::endl;
            } else {
                meta = false;
                resize();
            }
        }
    }

    if (!widthLoaded || !heightLoaded) {
        std::cerr << "Map Data corrupted" << std::endl;
    }
    iniOffset();
    updatePathFinding();
    return widthLoaded && heightLoaded && !meta;
}

void Map::setTile(Event &event, MapObjects object) {
    Point p = {event.motion.x, event.motion.y};
    setTile(CT::getTileInGame(p), object);
}

void Map::setTile(Point p, MapObjects object) {
    if (p.x < _width && p.x >= 0 && p.y < _height && p.y >= 0) {
        _map[p.x][p.y] = object;
    }
    updatePathFinding();
    CheckEnemiesPath(p);
}

MapObjects Map::getObjectAtScreenPos(Point &p) {
    return getObject(CT::getTileInGame(p), false);
}

MapObjects Map::getObject(Point p, bool OutOfBoundsError) {
    if (p.y >= 0 && p.y < _height && p.x >= 0 && p.x < _width)
        return _map[p.x][p.y];
    if (OutOfBoundsError)
        cerr << "Out of Map Bounds" << endl;
    return MapObjects::OutOfBounds;
}

MapObjects Map::getObject(FPoint p, bool OutOfBoundsError) {
    Point p_int = {(int) p.x, (int) p.y};
    return getObject(p_int, OutOfBoundsError);
}

void Map::iniOffset() const {
    if (_width * scale < windowSize.x)
        offset.x = -(windowSize.x - _width * scale) / 2;
    if (_height * scale < (windowSize.y - 100))
        offset.y = -(windowSize.y - _height * scale - 100) / 2;
}

void Map::Update() {

}

bool Map::updatePathFinding() {
    _startPoints.clear();
    // clear path array
    for (int j = 0; j < _height; j++) {
        for (int i = 0; i < _width; i++) {
            if (_map[i][j] == MapObjects::Start)
                _startPoints.push_back({i, j});
            _pathMap[i][j].pos = {-1, -1}; //-1/-1 is not set
            _pathMap[i][j].blocked = isBlocked(i, j);
            _pathMap[i][j].goal = _map[i][j] == MapObjects::Goal;
            _pathMap[i][j].set = isBlocked(i, j);
        }
    }
    //  map should have spawn points, and at least one goal
    bool allPathsFound = false;
    bool certificatesConnected = true;
    int loopCounter = 0;
    while (!allPathsFound && loopCounter < _width * _height) {
        loopCounter++;
        allPathsFound = true;
        bool changed = false;
        for (int j = 0; j < _height; j++) {
            for (int i = 0; i < _width; i++) {
                if (!_pathMap[i][j].blocked && !_pathMap[i][j].goal && !_pathMap[i][j].set) {
                    if (evaluatePath(i, j))
                        changed = true;
                    allPathsFound = false;
                }
            }
        }
        if (!changed)
            break;
    }
    for (Point p: _startPoints) {
        if (!_pathMap[p.x][p.y].blocked && !_pathMap[p.x][p.y].goal && !_pathMap[p.x][p.y].set)
            certificatesConnected = false;
    }

    if (!allPathsFound && !certificatesConnected) {
        cerr << "updating Path failed" << endl;
        return false;
    }
    return true;
}

Point Map::getNextPos(Point p) {
    return _pathMap[p.x][p.y].pos;
}

FPoint Map::getNextPosCentre(FPoint p) {
    Point res;
    res.x = (int) p.x;
    res.y = (int) p.y;
    res = getNextPos(res);
    return {(float) res.x + 0.5f, (float) res.y + 0.5f};
}

bool Map::isBlocked(int i, int j) {
    switch (_map[i][j]) {
        case MapObjects::Empty:
        case MapObjects::Start:
        case MapObjects::Goal:
            return false;
        default:
            return true;
    }
}


bool Map::evaluatePath(int x, int y) {
    // look around position if goal is reachable
    // we use 4er neighborhood stuff
    // look if a goal is reachable
    if (x + 1 < _width && _pathMap[x + 1][y].goal) {
        setPathEntry(x, y, x + 1, y);
        return true;
    }
    if (y + 1 < _height && _pathMap[x][y + 1].goal) {
        setPathEntry(x, y, x, y + 1);
        return true;
    }
    if (y - 1 >= 0 && _pathMap[x][y - 1].goal) {
        setPathEntry(x, y, x, y - 1);
        return true;
    }
    if (x - 1 >= 0 && _pathMap[x - 1][y].goal) {
        setPathEntry(x, y, x - 1, y);
        return true;
    }
    // if there is no goal found ... look for other path entries
    if (x + 1 < _width && _pathMap[x + 1][y].set && !_pathMap[x + 1][y].blocked) {
        setPathEntry(x, y, x + 1, y);
        return true;
    }
    if (y + 1 < _height && _pathMap[x][y + 1].set && !_pathMap[x][y + 1].blocked) {
        setPathEntry(x, y, x, y + 1);
        return true;
    }
    if (y - 1 >= 0 && _pathMap[x][y - 1].set && !_pathMap[x][y - 1].blocked) {
        setPathEntry(x, y, x, y - 1);
        return true;
    }
    if (x - 1 >= 0 && _pathMap[x - 1][y].set && !_pathMap[x - 1][y].blocked) {
        setPathEntry(x, y, x - 1, y);
        return true;
    }
    return false;
}

void Map::setPathEntry(int ex, int ey, int tx, int ty) {
    _pathMap[ex][ey].pos = {tx, ty};
    _pathMap[ex][ey].set = true;
}

u16 Map::getDir(int ex, int ey, int tx, int ty) {
    if (ex == tx && ey < ty)
        return 180;
    if (ex == tx && ey > ty)
        return 0;
    if (ex < tx && ey == ty)
        return 90;
    return 270;
}

bool Map::checkPath(Point pos) {

    if (getObject(pos) == MapObjects::Empty) {
        setTile(pos, MapObjects::Tower);
        if (!updatePathFinding()) {
            setTile(pos, MapObjects::Empty);
            return false;
        }
        setTile(pos, MapObjects::Empty);
    }
    return true;
}

bool Map::blockingTile(SDL_Point pos) {
    for (auto &tower: tdGlobals->_towers) {
        if (pos.x == tower->getRenderPos().x && pos.y == tower->getRenderPos().y) {
            return true;
        }
    }

    MapObjects obj = getObject(pos);
    cout << TdTileHandler::getName(obj) << endl;

    switch (obj) {
        case Empty:
        case Table:
            return false;
        default:
            return true;
    }
}

Point Map::getStartPoint(int i) {
    if ((int) _startPoints.size() >= i + 1)
        return _startPoints.at(i);
    return _startPoints.at(0);
}

void Map::CheckEnemiesPath(Point point) {
    for (auto &e: tdGlobals->_enemies) {
        if ((int) e->_nextPos.x == point.x && (int) e->_nextPos.y == point.y){
            switch(e->_dir){
                case 0:
                    e->_nextPos = {(float)point.x+0.5f,(float)point.y-1.5f};
                    break;
                case 90:
                    e->_nextPos = {(float)point.x-0.5f,(float)point.y+0.5f};
                    break;
                case 180:
                    e->_nextPos = {(float)point.x+0.5f,(float)point.y+1.5f};
                    break;
                case 270:
                    e->_nextPos = {(float)point.x-1.5f,(float)point.y+0.5f};
                    break;
            }
        }
    }
}

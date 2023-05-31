//
// Created by banoodle on 17.05.23.
//

#include "map.h"

Map::Map() {
    this->_height = 8;
    this->_width = 16;
    _tileMap = t_cache->get(BasePath "asset/graphic/td/tileTD.png");
    _blocked = t_cache->get(BasePath "asset/graphic/editor/blocked.png");
    _arrow = t_cache->get(BasePath "asset/graphic/editor/arrow.png");
    this->_map = std::vector(_width, Vector<MapObjects>(_height));
    this->_pathMap = std::vector(_width, Vector<PathEntry>(_height));
}

unsigned long Map::getMapTime() const {
    return _time;
}

unsigned long Map::getMapTimeDiff() {
    return _deltaTime;
}

void Map::showSizeDialog() {
    std::cout << "\"pMap showSizeDialog\"not implemented yet";
}

void Map::Render(bool wire, bool pathFinding) {
    _time++;
    if (wire)
        drawWire();
    Rect dstRect;
    for (int i = 0; i < _width; i++) {
        int x = (i * scale) - offset.x;
        for (int j = 0; j < _height; j++) {
            int y = (j * scale) - offset.y;
            dstRect = {x, y, scale, scale};
            t_cache->render(_tileMap, &dstRect, TdTileHandler::getSrcRect(_map[i][j], _time));
        }
    }
    if(pathFinding){
        for (int i = 0; i < _width; i++) {
            int x = (i * scale) - offset.x;
            for (int j = 0; j < _height; j++) {
                int y = (j * scale) - offset.y;
                dstRect = {x, y, scale, scale};
                Point p= {i,j};
                PathEntry e = _pathMap[i][j];
                if(e.blocked)
                    t_cache->render(_blocked,&dstRect);
                else if(!e.set&&!e.goal){
                    dstRect.x+=scale/6;
                    dstRect.y+=scale/6;
                    dstRect.w-=scale/3;
                    dstRect.h-=scale/3;
                    t_cache->renderFillRect(&dstRect,YELLOW);
                    dstRect = {x, y, scale, scale};

                }
                else if(e.goal){
                    continue;
                }
                else{
                    t_cache->render(_arrow,&dstRect,getDir(i,j,e.pos.x,e.pos.y));
                }
            }
        }
    }
}

void Map::drawWire() const {
    t_cache->setRenderColor(MAP_GRID);
    for (int i = 0; i <= _width; i++) {
        int x2;
        int x1 = x2 = i * scale - offset.x;
        int y1 = -offset.y;
        int y2 = _height * scale - offset.y;
        SDL_RenderDrawLine(render, x1, y1, x2, y2);
    }
    for (int j = 0; j <= _height; j++) {
        int y2;
        int y1 = y2 = j * scale - offset.y;
        int x1 = 0 - offset.x;
        int x2 = _width * scale - offset.x;
        SDL_RenderDrawLine(render, x1, y1, x2, y2);
    }
}

void Map::save(const string &path) {
    char name[50];
    strcpy(name, BasePath"Maps/");
    strcat(name, path.c_str());
    // save pMap!
    std::ofstream oStream;
    strcat(name, ".map");
    oStream.open((name));
    //checkPlayerStartSpot();
    oStream << "WIDTH :" << _width << "\n";
    oStream << "HEIGHT:" << _height << "\n";
    oStream << "ARRAY :\n";
    for (int j = 0; j < _height; j++) {
        oStream << "ROW " << j << ";";
        for (int i = 0; i < _width; i++) {
            oStream << _map[i][j] << "; ";
        }
        oStream << "\n";
    }
    oStream.close();
}

void Map::load(const string &path) {
    string line;
    std::ifstream iStream;
    cout << "Load Map: " << path << endl;
    char mnName[50];
    strcpy(mnName, path.c_str());
    iStream.open(mnName);
    bool widthLoaded = false;
    bool heightLoaded = false;
    if (iStream.is_open()) {
        bool meta = true;
        while (getline(iStream, line)) {
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
                    resizeMap();
                }
            }
        }
    }
    if (!widthLoaded || !heightLoaded) {
        std::cerr << "Map Data corrupted" << std::endl;
    }
    iniOffset();
    updatePathFinding();
}

void Map::setTile(Event event, MapObjects object) {
    int x = (event.motion.x + offset.x) / (scale);
    int y = (event.motion.y + offset.y) / (scale);
    setTile({x,y},object);
}

void Map::setTile(Point p, MapObjects object) {
    if (p.x < _width && p.x >= 0 && p.y < _height && p.y >= 0) {
        _map[p.x][p.y] = object;
    }
    updatePathFinding();
}

TdTileHandler::MapObjects Map::getObjectAtScreenPos(Point p) {
    Point pos;
    pos.x = (p.x + offset.x) / (scale);
    pos.y = (p.y + offset.y) / (scale);
    return getObject(pos, false);
}

Point Map::getPosOnScreen(Point p) {
    Point POS = {(p.x * scale), (p.y * scale)};
    return POS - offset;
}

TdTileHandler::MapObjects Map::getObject(Point p, bool OutOfBoundsError) {
    if (p.y >= 0 && p.y < _height && p.x >= 0 && p.x < _width)
        return _map[p.x][p.y];
    if (OutOfBoundsError)
        cerr << "Out of Map Bounds" << endl;
    return MapObjects::Empty;
}

MapObjects Map::getObject(FPoint p, bool OutOfBoundsError) {
    Point res;
    res.x = (int) p.x;
    res.y = (int) p.y;
    return getObject(res);
}

void Map::resizeMap() {
    cout << "resize Map to Width = " << _width << " Height = " << _height << endl;
    _map.resize(_width);
    _pathMap.resize(_width);
    for (int i = 0; i < _width; i++) {
        _map[i].resize(_height);
        _pathMap[i].resize(_height);
    }
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

void Map::iniOffset() const {
    if (_width * scale < windowSize.x)
        offset.x = -(windowSize.x - _width * scale) / 2;
    if (_height * scale < (windowSize.y - 100))
        offset.y = -(windowSize.y - _height * scale - 100) / 2;
}

void Map::Update(const u32 frame, const u32 totalMSec, const float deltaT) {
    _deltaTime = deltaT;
    _time = totalMSec;
}

void Map::updatePathFinding() {
    // mockdata
    // enemies will head right

    // clear path array
    for (int j = 0; j < _height; j++) {
        for (int i = 0; i < _width; i++) {
            _pathMap[i][j].pos = {-1, -1}; //-1/-1 is not set
            _pathMap[i][j].blocked = isBlocked(i,j);
            _pathMap[i][j].goal = _map[i][j] == MapObjects::Goal;
            _pathMap[i][j].set = isBlocked(i,j);
        }
    }
    //  map should have spawn points, and at least one goal
    bool allPathsFound = false;
    int loopCounter = 0;
    while(!allPathsFound && loopCounter<_width*_height){
        loopCounter++;
        allPathsFound = true;
        for (int j = 0; j < _height; j++) {
            for (int i = 0; i < _width; i++) {
                if(!_pathMap[i][j].blocked&&!_pathMap[i][j].goal&&!_pathMap[i][j].set) {
                    evaluatePath(i, j);
                    allPathsFound = false;
                }
            }
        }
    }
    if(!allPathsFound){
        cerr << "updating Path failed" << endl;
    }
}

Point Map::getNextPos(Point p) {
    return _pathMap[p.x][p.y].pos;
}
Point Map::getNextPos(FPoint p) {
    Point res;
    res.x = (int) p.x;
    res.y = (int) p.y;
    return getNextPos(res);
}

FPoint Map::getPrecisePosOnScreen(FPoint &fp) {
    return {fp.x * (float) scale - (float) offset.x,fp.y * (float) scale - (float) offset.y};
}

FPoint Map::getPreciseCenterOfPos(Point &p) {
    return { (float)p.x + 0.5f,(float) p.y + 0.5f};
}

bool Map::isBlocked(int i, int j) {
    switch(_map[i][j]){
        case MapObjects::Empty:
        case MapObjects::Start:
        case MapObjects::Goal:
            return false;
        default:
            return true;
    }
}


void Map::evaluatePath(int x, int y) {
    // look around position if goal is reachable
    // we use 4er neighborhood stuff
    // look if a goal is reachable
    if(x+1 < _width && _pathMap[x+1][y].goal){
        setPathEntry(x,y,x+1,y);
        return;
    }
    if(y+1<_height && _pathMap[x][y+1].goal){
        setPathEntry(x,y,x,y+1);
        return;
    }
    if(y-1>=0 && _pathMap[x][y-1].goal){
        setPathEntry(x,y,x,y-1);
        return;
    }
    if(x-1>=0 && _pathMap[x-1][y].goal){
        setPathEntry(x,y,x-1,y);
        return;
    }
    // if there is no goal found ... look for other path entries
    if(x+1 < _width && _pathMap[x+1][y].set && !_pathMap[x+1][y].blocked){
        setPathEntry(x,y,x+1,y);
        return;
    }
    if(y+1<_height && _pathMap[x][y+1].set && !_pathMap[x][y+1].blocked){
        setPathEntry(x,y,x,y+1);
        return;
    }
    if(y-1>=0 && _pathMap[x][y-1].set && !_pathMap[x][y-1].blocked){
        setPathEntry(x,y,x,y-1);
        return;
    }
    if(x-1>=0 && _pathMap[x-1][y].set && !_pathMap[x-1][y].blocked){
        setPathEntry(x,y,x-1,y);
        return;
    }
}

void Map::setPathEntry(int ex, int ey, int tx, int ty) {
        _pathMap[ex][ey].pos = {tx,ty};
        _pathMap[ex][ey].set = true;
}

u16 Map::getDir(int ex, int ey, int tx, int ty) {
    if(ex == tx && ey < ty)
        return 0;
    if(ex == tx && ey > ty)
        return 180;
    if(ex < tx && ey == ty)
        return 90;
    return 270;
}







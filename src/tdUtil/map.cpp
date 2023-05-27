//
// Created by banoodle on 17.05.23.
//

#include "map.h"

Map::Map() {
    this->_height = 8;
    this->_width = 16;
    _tileMap = t_cache->get("../asset/graphic/td/tileTD.png");
    this->_map = std::vector(_width, Vector<MapObjects>(_height));
    this->_pathMap = std::vector(_width, Vector<Point>(_height));
    updatePathFinding();
}

u_long Map::getMapTime() const {
    return _time;
}

ulong Map::getMapTimeDiff() {
    return _deltaTime;
}

void Map::showSizeDialog() {
    std::cout << "\"pMap showSizeDialog\"not implemented yet";
}

void Map::Render(bool wire) {
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

void Map::save(const std::string &path) {
    char name[50];
    strcpy(name, "../Maps/");
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

void Map::load(const std::string &path) {
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
}

void Map::setTile(Event event, MapObjects object) {
    int x = (event.motion.x + offset.x) / (scale + 1);
    int y = (event.motion.y + offset.y) / (scale + 1);
    if (x < _width && x >= 0 && y < _height && y >= 0) {
        _map[x][y] = object;
    }
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
    ulong token = line.find(';');
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

Point Map::getCenterOfPosInLogic(Point p) {
    int x = (int) (((p.x + 0.5) * scale) / 2.0);
    int y = (int) (((p.y + 0.5) * scale) / 2.0);
    Point POS = {x, y};
    return POS;
}

void Map::Update(const u32 frame, const u32 totalMSec, const float deltaT) {
    _deltaTime = deltaT;
    _time = totalMSec;
    updatePathFinding();
}

void Map::updatePathFinding() {
    // mockdata
    // enemies will head right
    for (int j = 0; j < _height; j++) {
        for (int i = 0; i < _width; i++) {
            _pathMap[i][j] = {i+1,j};
        }
    }

}

Point Map::getNextPos(Point p) {
    return {p.x+1,p.y};
    //return _pathMap[p.x][p.y];

}

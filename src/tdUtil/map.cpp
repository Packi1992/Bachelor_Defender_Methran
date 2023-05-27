//
// Created by banoodle on 17.05.23.
//

#include "map.h"

Map::Map() {
    this->height = 8;
    this->width = 16;
    t_tileMap = t_cache->get("../asset/graphic/td/tileTD.png");
    this->map = std::vector(width, std::vector<TdTileHandler::MapObjects>(height));
}

u_long Map::getMapTime() const {
    return time;
}

void Map::showSizeDialog() {
    std::cout << "\"pMap showSizeDialog\"not implemented yet";
}

void Map::Render(bool wire) {
    time++;
    if (wire)
        drawWire();
    Rect dstRect;
    for (int i = 0; i < width; i++) {
        int x = (i * scale) - offset.x;
        for (int j = 0; j < height; j++) {
            int y = (j * scale) - offset.y;
            dstRect = {x, y, scale, scale};
            t_cache->render(t_tileMap, &dstRect, TdTileHandler::getSrcRect(map[i][j], time));
        }
    }
}

void Map::drawWire() const {
    t_cache->setRenderColor(MAP_GRID);
    for (int i = 0; i <= width; i++) {
        int x2;
        int x1 = x2 = i * scale - offset.x;
        int y1 = -offset.y;
        int y2 = height * scale - offset.y;
        SDL_RenderDrawLine(render, x1, y1, x2, y2);
    }
    for (int j = 0; j <= height; j++) {
        int y2;
        int y1 = y2 = j * scale - offset.y;
        int x1 = 0 - offset.x;
        int x2 = width * scale - offset.x;
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
    oStream << "WIDTH :" << width << "\n";
    oStream << "HEIGHT:" << height << "\n";
    oStream << "ARRAY :\n";
    for (int j = 0; j < height; j++) {
        oStream << "ROW " << j << ";";
        for (int i = 0; i < width; i++) {
            oStream << map[i][j] << "; ";
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
                width = (int) strtol(line.substr(7).c_str(), nullptr, 10);
                widthLoaded = true;
            } else if (meta && (line.substr(0, 7) == ("HEIGHT:"))) {
                height = (int) strtol(line.substr(7).c_str(), nullptr, 10);
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
    if (x < width && x >= 0 && y < height && y >= 0) {
        map[x][y] = object;
    }
}

TdTileHandler::MapObjects Map::getObjectAtScreenPos(Point p) {
    Point pos;
    pos.x = (p.x + offset.x) / (scale);
    pos.y = (p.y + offset.y) / (scale);
    return getObject(pos, false);
}

Point Map::getPosOnScreen(Point p) {
    Point POS = {(p.x * scale) - offset.x, (p.y * scale) - offset.y};
    return POS;
}

TdTileHandler::MapObjects Map::getObject(Point p, bool OutOfBoundsError) {
    if (p.y >= 0 && p.y < height && p.x >= 0 && p.x < width)
        return map[p.x][p.y];
    if (OutOfBoundsError)
        cerr << "Out of Map Bounds" << endl;
    return MapObjects::Empty;
}

void Map::resizeMap() {
    cout << "resize Map to Width = " << width << " Height = " << height << endl;
    map.resize(width);
    for (int i = 0; i < width; i++) {
        map[i].resize(height);
    }
}

void Map::loadRow(string line) {
    ulong token = line.find(';');
    int row = (int) strtol(line.substr(4, token).c_str(), nullptr, 10);
    for (int i = 0; i < width; i++) {
        line.erase(0, token + 1);
        token = line.find(';');
        int o = (int) strtol(line.substr(0, token).c_str(), nullptr, 10);
        map[i][row] = TdTileHandler::selectObject(o);
    }
}

void Map::iniOffset() {
    if (width * scale < windowSize.x)
        offset.x = -(windowSize.x - width * scale) / 2;
    if (height * scale < (windowSize.y - 100))
        offset.y = -(windowSize.y - height * scale - 100) / 2;
}

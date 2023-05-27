//
// Created by banoodle on 17.05.23.
//

#include "map.h"

u_long Map::getMapTime() {
    return time;
}

void Map::showSizeDialog() {
    std::cout << "\"map showSizeDialog\"not implemented yet";
}

void Map::set(Point *pOffset) {
    this->offset = pOffset;
    t_tile = t_cache->get("../asset/graphic/td/tileTD.png");
    this->map = std::vector(width, std::vector<TdTileHandler::MapObjects>(height));
    iniOffset();
}

void Map::draw(bool wire) {
    time++;
    if (wire) {
        drawWire();
    }
    for (int i = 0; i < width; i++) {
        int x = (i * scale) - offset->x;
        for (int j = 0; j < height; j++) {
            int y = (j * scale) - offset->y;
            SDL_Rect dstRect = {x, y, scale, scale};
            SDL_RenderCopy(render, t_tile, TdTileHandler::getSrcRect(map[i][j], time), &dstRect);
        }
    }
}

void Map::drawWire() {
    t_cache->setRenderColor(MAP_GRID);
    for (int i = 0; i <= width; i++) {
        int x2;
        int x1 = x2 = i * scale - offset->x;
        int y1 = -offset->y;
        int y2 = height * scale - offset->y;
        SDL_RenderDrawLine(render, x1, y1, x2, y2);
    }
    for (int j = 0; j <= height; j++) {
        int y2;
        int y1 = y2 = j * scale - offset->y;
        int x1 = 0 - offset->x;
        int x2 = width * scale - offset->x;
        SDL_RenderDrawLine(render, x1, y1, x2, y2);
    }
}

void Map::save(const std::string &path) {

    char name[50];
    strcpy(name,"../Maps/");
    strcat(name, path.c_str());
    // save map!
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
    std::cout << "Load Map: "<< path << std::endl;
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
                std::cout << "start map content" << std::endl;
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

Map::Map() {
    this->height = 8;
    this->width = 16;
    this->scale = 64;
}

void Map::set(Event event, TdTileHandler::MapObjects o) {
    int x = (event.motion.x + offset->x) / (scale + 1);
    int y = (event.motion.y + offset->y) / (scale + 1);
    if (x < width && x >= 0 && y < height && y >= 0) {
        map[x][y] = o;
    }
}

TdTileHandler::MapObjects Map::getObjectAtScreenPos(SDL_Point p) {
    SDL_Point pos;
    pos.x = (p.x + offset->x) / (scale);
    pos.y = (p.y + offset->y) / (scale);
    return getObject(pos, false);
}

Point Map::getPosOnScreen(Point p) {
    Point POS = {(p.x * scale) - offset->x, (p.y * scale) - offset->y};
    return POS;
}

TdTileHandler::MapObjects Map::getObject(Point p, bool OutOfBoundsError) {
    if (p.y >= 0 && p.y < height && p.x >= 0 && p.x < width)
        return map[p.x][p.y];
    if(OutOfBoundsError)
        std::cerr << "Out of Map Bounds" << std::endl;
    return TdTileHandler::MapObjects::Empty;
}

void Map::resizeMap() {
    std::cout << "resize Map to Width = " << width << " Height = " << height << std::endl;
    map.resize(width);
    for (int i = 0; i < width; i++) {
        map[i].resize(height);
    }
}

void Map::loadRow(std::string line) {
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
    Point wSize = pGame->GetWindowSize();
    if(width*scale<wSize.x)
        offset->x = -(wSize.x-width*scale)/2;
    if(height*scale<(wSize.y-100))
        offset->y = -(wSize.y -height*scale-100)/2;
}

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

void Map::set(Renderer *pRender, const Point *pOffset) {
    this->render = pRender;
    this->t_cache = TextureCache::getCache(render);
    this->offset = pOffset;
    std::cout << "\"map set\"not implemented yet";
}

void Map::draw( bool wire) {
    this->offset = offset;
    if(wire){
        drawWire();
    }
    std::cout << "\"map draw\"not implemented yet";
}

void Map::drawWire() {
    t_cache->setRenderColor(MAP_GRID);
    for (int i = 0; i <= width; i++) {
        int x2;
        int x1 = x2 = i * (scale + 1) - offset->x;
        int y1 = -offset->y;
        int y2 = height * (scale + 1) - offset->y;
        SDL_RenderDrawLine(render, x1, y1, x2, y2);
    }
    for (int j = 0; j <= height; j++) {
        int y2;
        int y1 = y2 = j * (scale + 1) - offset->y;
        int x1 = 0 - offset->x;
        int x2 = width * (scale + 1) - offset->x;
        SDL_RenderDrawLine(render, x1, y1, x2, y2);
    }
}

void Map::save(const std::string &path) {
    std::cout << "\"map save\"not implemented yet";
}

void Map::load(const std::string &path) {
    std::cout << "\"Map load\"not implemented yet";
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

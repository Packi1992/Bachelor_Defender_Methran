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
    t_tile = this->t_cache->getTexture("../asset/graphic/td/tileTD.png");
    this->map = std::vector(width, std::vector<TdTileHandler::MapObjects>(height));
    map[0][0] = TdTileHandler::Start;
    map[1][1] = TdTileHandler::Goal;
}

void Map::draw(bool wire) {
    time++;
    if (wire) {
        drawWire();
    }
    for (int i = 0; i < width; i++) {
        int x = (i * scale + i + 1) - offset->x;
        for (int j = 0; j < height; j++) {
            int y = (j * scale + j + 1) - offset->y;
            SDL_Rect dstRect = {x, y, scale, scale};
            SDL_RenderCopy(render, t_tile, TdTileHandler::getSrcRect(map[i][j], time), &dstRect);
        }
    }
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

TdTileHandler::MapObjects Map::getObjectAtScreenPos(SDL_Point p) {
    SDL_Point pos;
    pos.x = (p.x + offset->x) / (scale + 1);
    pos.y = (p.y + offset->y) / (scale + 1);
    return getObject(pos, false);
}

Point Map::getPosOnScreen(Point p) {
    Point POS = {(p.x * scale + p.x + 1) - offset->x, (p.y * scale + p.y + 1) - offset->y};
    return POS;
}

TdTileHandler::MapObjects Map::getObject(Point p, bool OutOfBoundsError) {
    if (p.y >= 0 && p.y < height && p.x >= 0 && p.x < width)
        return map[p.x][p.y];
    if(OutOfBoundsError)
        std::cerr << "Out of Map Bounds" << std::endl;
    return TdTileHandler::MapObjects::Empty;
}

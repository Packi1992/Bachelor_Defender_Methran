
#include "../global.h"
#include "../gamebase.h"
#include "../recthelper.h"
#include "coordinateTransformer.h"

// game base will define global variables like offset and scale (this will be used in calculations)


FPoint CoordinateTransformer::getPosInGame(const Point &p) {
    return {float(p.x + offset.x) / (float) scale, float(p.y + offset.y) / (float) scale};
}

Point CoordinateTransformer::getPosOnScreen(const Point &p) {
    Point POS = {(p.x * scale), (p.y * scale)};
    return POS - offset;
}

Point CoordinateTransformer::getPosOnScreen(const FPoint &p) {
    return {(int) (p.x * (float) scale - (float) offset.x), (int) (p.y * (float) scale - (float) offset.y)};
}

Point CoordinateTransformer::getTileInGame(const Point &p) {
    return {(p.x + offset.x) / (scale), (p.y + offset.y) / (scale)};
}

Point CoordinateTransformer::getTileInGame(const FPoint &p) {
    return {((int) p.x + offset.x) / (scale), ((int) p.y + offset.y) / (scale)};
}

FPoint CoordinateTransformer::getTileCenterInGame(const Point &p) {
    return {float((int) ((p.x + offset.x) / (scale))) + 0.5f, (float) ((int) ((p.y + offset.y) / (scale))) + 0.5f};
}

FRect CoordinateTransformer::getFRectOnScreen(const FRect &fr) {
    return {(fr.x * (float) scale - (float) offset.x), (fr.y * (float) scale - (float) offset.y), fr.w * (float) scale,
            fr.h * (float) scale};
}

float CoordinateTransformer::getAngle(const SDL_Point &p1, const SDL_Point &p2) {
    int y = p1.y - p2.y;
    int x = p1.x - p2.x;
    bool above = false;
    if (y < 0) {
        above = true;
        y = -y;
    }
    if (y == 0) {
        above = true;
    }
    bool left = false;
    if (x < 0) {
        left = true;
        x = -x;
    }
    if (x == 0) {
        left = true;
    }
    float alpha = (float) atan((float) y / (float) x) * 180.0f / (float) M_PI;
    if (above && !left)
        alpha = (float) ((int) (90 - alpha) % 360);
    if (!above && !left)
        alpha += 90;
    if (left && !above) {
        alpha = (float) ((int) (90 - alpha) % 360);
        alpha += 180;
    }
    if (left & above)
        alpha += 270;
    alpha = (float) ((int) (alpha) % 360);
    return alpha;
}

float CoordinateTransformer::getAngle(const SDL_FPoint &p1, const SDL_FPoint &p2) {
    float y = p2.y - p1.y;
    float x = p2.x - p1.x;
    bool above = false;
    if (y < 0) {
        above = true;
        y = -y;
    }
    if (y == 0) {
        above = true;
    }
    bool left = false;
    if (x < 0) {
        left = true;
        x = -x;
    }
    if (x == 0) {
        left = true;
    }
    float alpha = (float) atan(y / x) * 180.0f / (float) M_PI;
    if (above && !left)
        alpha = (float) ((int) (90 - alpha) % 360);
    if (!above && !left)
        alpha += 90;
    if (left && !above) {
        alpha = (float) ((int) (90 - alpha) % 360);
        alpha += 180;
    }
    if (left & above)
        alpha += 270;
    alpha = (float) ((int) (alpha) % 360);
    return alpha;
}

SDL_Point CoordinateTransformer::getMousePosTile() {
    return getTileInGame(Game::getMousePos());
}



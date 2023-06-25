
#include "global.h"
#include "gamebase.h"
#include "recthelper.h"
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

double CoordinateTransformer::getAngle(const DPoint &p1, const DPoint &p2) {
    double y = p2.y - p1.y;
    double x = p2.x - p1.x;
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
    double alpha = atan(y / x) * 180.0 /  M_PI;
    if (above && !left)
        alpha = (90 - alpha);
    if (!above && !left)
        alpha += 90;
    if (left && !above) {
        alpha = 450 - alpha;
        alpha += 180;
    }
    if (left & above)
        alpha -= 90;
    return alpha;
}

SDL_Point CoordinateTransformer::getMousePosTile() {
    return getTileInGame(Game::getMousePos());
}

bool CoordinateTransformer::collisionLineLine(const SDL_FPoint &p11, const SDL_FPoint &p12, const SDL_FPoint &p21,
                                              const SDL_FPoint &p22) {
    float uD = ((p22.y - p21.y) * (p12.x - p11.x) - (p22.x - p21.x) * (p12.y - p11.y));
    if (uD != 0) {
        float uA = ((((p22.x - p21.x) * (p11.y - p21.y)) - ((p22.y - p21.y) * (p11.x - p21.x))) / uD);
        float uB = ((((p12.x - p11.x) * (p11.y - p21.y)) - ((p12.y - p11.y) * (p11.x - p21.x))) / uD);
        if (uA > 0 && uA < 1 && uB > 0 && uB < 1) {
            return true;
        }
    }
    return false;
}

bool CoordinateTransformer::collisionLineRect(const SDL_FPoint &p1, const SDL_FPoint &p2, const SDL_FRect &r) {
    bool top = collisionLineLine(p1, p2, {r.x, r.y}, {r.x + r.w, r.y});
    bool right = collisionLineLine(p1, p2, {r.x + r.w, r.y}, {r.x + r.w, r.y + r.h});
    bool bot = collisionLineLine(p1, p2, {r.x, r.y + r.h}, {r.x + r.w, r.y + r.h});
    bool left = collisionLineLine(p1, p2, {r.x, r.y}, {r.x, r.y + r.h});
    return (left || top || right || bot);
}



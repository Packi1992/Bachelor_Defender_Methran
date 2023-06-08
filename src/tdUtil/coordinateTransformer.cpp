//
// Created by banoodle on 08.06.23.
//
#include "coordinateTransformer.h"

FPoint CoordinateTransformer::getPosInGame(const Point &p) {
    return {float(p.x + offset.x)/(float)scale, float(p.y + offset.y)/(float)scale};
}

Point CoordinateTransformer::getPosOnScreen(const Point &p) {
    Point POS = {(p.x * scale), (p.y * scale)};
    return POS - offset;
}

Point CoordinateTransformer::getPosOnScreen(const FPoint &p) {
    return {(int)(p.x * (float) scale - (float) offset.x),(int)(p.y * (float) scale - (float) offset.y)};
}

Point CoordinateTransformer::getTileInGame(const Point &p) {
    return {(p.x + offset.x) / (scale),(p.y + offset.y) / (scale)};
}

Point CoordinateTransformer::getTileInGame(const FPoint &p) {
    return {((int)p.x + offset.x) / (scale),((int)p.y + offset.y) / (scale)};
}

FPoint CoordinateTransformer::getTileCenterInGame(const Point &p) {
    return {float((int)((p.x + offset.x) / (scale)))+0.5f,(float)((int)((p.y + offset.y) / (scale)))+0.5f};
}



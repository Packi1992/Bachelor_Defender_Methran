//
// Created by banoodle on 08.06.23.
//

#ifndef SDL_BACHELORDEFENDER_COORDINATETRANSFORMER_H
#define SDL_BACHELORDEFENDER_COORDINATETRANSFORMER_H

#include <SDL_render.h>


class CoordinateTransformer {
public:
    // Screen to game
    // get Tile at screen position
    static SDL_Point getTileInGame(const SDL_Point &p);

    static SDL_Point getTileInGame(const SDL_FPoint &p);

    // get center instead of left upper corner
    static SDL_FPoint getTileCenterInGame(const SDL_Point &p);

    // get logical pos - Input should be screen position
    static SDL_FPoint getPosInGame(const SDL_Point &p);

    // game Map to Screen, just for rendering
    static SDL_Point getPosOnScreen(const SDL_Point &p);

    static SDL_Point getPosOnScreen(const SDL_FPoint &p);

    static SDL_FRect getFRectOnScreen(const SDL_FRect &fr);

    static SDL_Point getMousePosTile();

    static float getAngle(const SDL_Point &p1, const SDL_Point &p2);

    static float getAngle(const SDL_FPoint &p1, const SDL_FPoint &p2);

    static bool
    collisionLineLine(const SDL_FPoint &p11, const SDL_FPoint &p12, const SDL_FPoint &p21, const SDL_FPoint &p22);

    static bool collisionLineRect(const SDL_FPoint &p1, const SDL_FPoint &p2, const SDL_FRect &r);
};

#endif //SDL_BACHELORDEFENDER_COORDINATETRANSFORMER_H

//
// Created by banoodle on 08.06.23.
//

#ifndef SDL_BACHELORDEFENDER_COORDINATETRANSFORMER_H
#define SDL_BACHELORDEFENDER_COORDINATETRANSFORMER_H
#include <SDL_render.h>


class CoordinateTransformer{
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


};
#endif //SDL_BACHELORDEFENDER_COORDINATETRANSFORMER_H

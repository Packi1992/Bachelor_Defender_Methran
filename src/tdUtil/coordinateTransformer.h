//
// Created by banoodle on 08.06.23.
//

#ifndef SDL_BACHELORDEFENDER_COORDINATETRANSFORMER_H
#define SDL_BACHELORDEFENDER_COORDINATETRANSFORMER_H
class CoordinateTransformer;
#include "../global.h"
// game base will define global variables like offset and scale (this will be used in calculations)
#include "../gamebase.h"

class CoordinateTransformer{
public:
    // Screen to game
    // get Tile at screen position
    static Point getTileInGame(const Point &p);
    static Point getTileInGame(const FPoint &p);
    // get center instead of left upper corner
    static FPoint getTileCenterInGame(const Point &p);
    // get logical pos - Input should be screen position
    static FPoint getPosInGame(const Point &p);

    // game Map to Screen, just for rendering
    static Point getPosOnScreen(const Point &p);
    static Point getPosOnScreen(const FPoint &p);


};
#endif //SDL_BACHELORDEFENDER_COORDINATETRANSFORMER_H

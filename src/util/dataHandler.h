//
// Created by banoodle on 07.06.23.
//

#ifndef SDL_BACHELORDEFENDER_DATAHANDLER_H
#define SDL_BACHELORDEFENDER_DATAHANDLER_H
class DataHandler;
#include "../tdUtil/waveHandler.h"
#include "../tdUtil/map.h"
#include "../tdUtil/player.h"

class DataHandler{
private:
    enum DataType{
        PLAYER,
        MAP,
        WAVES,
        COUNT,
    };
public:
    static string getTypeName(DataType type);
    static void load(Player &player, WaveHandler &waves, Map &map,const string &path = BasePath"Maps/neueMap.map");
    static void save(Player &player, WaveHandler &waves, Map &map,const string &path = BasePath"Maps/neueMap" );
};
#endif //SDL_BACHELORDEFENDER_DATAHANDLER_H

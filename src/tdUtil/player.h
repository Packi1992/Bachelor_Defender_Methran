//
// Created by banoodle on 07.06.23.
//

#ifndef SDL_BACHELORDEFENDER_PLAYER_H
#define SDL_BACHELORDEFENDER_PLAYER_H


#include "../global.h"

class Player {
public:
    u32 _sanity = 0;
    u32 _maxSanity = 100;
    bool load(const Vector<string>& data);

    std::string save();
};


#endif //SDL_BACHELORDEFENDER_PLAYER_H

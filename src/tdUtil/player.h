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
    uint _creditPoints = 15;
    bool load(const Vector<string>& data);

    std::string save();

    bool buyTower(std::shared_ptr<struct Tower> sharedPtr);
};


#endif //SDL_BACHELORDEFENDER_PLAYER_H

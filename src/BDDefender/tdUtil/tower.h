//
// Created by banoodle on 23.05.23.
//

#ifndef SDL_BACHELORDEFENDER_TOWER_H
#define SDL_BACHELORDEFENDER_TOWER_H

#include "../../gamebase.h"
#include "map.h"

class Tower {
    // Draws the tower
    virtual void draw()=0;
    // Place Tower on Map
    virtual void set(Map map, Point pos)=0;
    // Do one ingame step
    virtual void tick(timer_t callingTime)=0;
    // give costs of tower back
    virtual int getCosts();

};


#endif //SDL_BACHELORDEFENDER_TOWER_H

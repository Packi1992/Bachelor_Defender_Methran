//
// Created by banoodle on 23.05.23.
//

#ifndef BACHELOR_DEFENDER_TOWER_H
#define BACHELOR_DEFENDER_TOWER_H

#include "../gamebase.h"
#include "map.h"

class Tower {
    // Draws the tower
    virtual void draw()=0;
    // Place Tower on Map
    virtual void set(Map map, Point pos)=0;
    // Do one ingame step
    virtual void tick(u32 callingTime)=0;
    // give costs of tower back
    virtual int getCosts();

};


#endif //BACHELOR_DEFENDER_TOWER_H

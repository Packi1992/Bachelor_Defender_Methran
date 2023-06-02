//
// Created by banoodle on 02.06.23.
//

#ifndef SDL_BACHELORDEFENDER_WAVE_H
#define SDL_BACHELORDEFENDER_WAVE_H

#include "../gamebase.h"
#include "enemy.h"


struct SpawnEvent{
    //  Enemy Type, which will be spawned
    EnemyType type=EnemyType::Ordinary;
    //  Spawn Time (0 will be directly spawned)
    u32 time=0;
    //  Amount of Enemies spawned at the same Time
    u8 count=1;
    //  Where to spawn enemies?
    u8 SpawnPoint=0;
    //  value of enemy
    u16 value=1;
};

class Wave{
public:
    // you should be able to pop Spawn Events
    // is it possible to sort a vector with specific element attribute?
    // sort with given time
    explicit Wave(int SpawnCount);
    void addEvent(string Event);
    ~Wave();
    void PollEvent(SpawnEvent *event);
    // index showing wave progress
    int index=0;
private:
    Vector<SpawnEvent> enemies;
};


#endif //SDL_BACHELORDEFENDER_WAVE_H

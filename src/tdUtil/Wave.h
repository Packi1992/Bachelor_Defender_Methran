//
// Created by banoodle on 02.06.23.
//

#ifndef SDL_BACHELORDEFENDER_WAVE_H
#define SDL_BACHELORDEFENDER_WAVE_H

#include "../gamebase.h"
#include "enemy.h"
#include <list>
#include <algorithm>


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
    bool operator< (const SpawnEvent &other) const{
        return time < other.time;
    }

    bool operator== (const SpawnEvent &other) const{
        return (type == other.type)&&
                (time == other.time)&&
                (count == other.count)&&
                (SpawnPoint == other.SpawnPoint)&&
                (value == other.value);
    }

    static SpawnEvent readLine(string EventAsString) {
        cerr << "implement Spawn Event parsing from String";
        return SpawnEvent{};
    }
};

class Wave{
public:
    // you should be able to pop Spawn Events
    // is it possible to sort a vector with specific element attribute?
    // sort with given time
    explicit Wave(int SpawnCount);
    // add Event takes a String should be easier to load
    void addEvent(string Event);
    // add Event kann also handle an actual spawn event
    void addEvent(SpawnEvent Event);
    // simply sets waveStart, it will be used to calculate spawn events
    void startWave(const u32 totalMSec);

    // will be false, if que is empty
    bool PollEvent(SpawnEvent &event);
    void Update(const u32 totalMSec);
    // index showing wave progress
    int index=0;
    ~Wave();
private:
    Vector<SpawnEvent> enemies;    // i want to implement a min heap ...
    std::list<SpawnEvent> pendingEvents;
    u32 waveStart=0;
    bool hasStarted = false;
    bool hasEnded = false;

};


#endif //SDL_BACHELORDEFENDER_WAVE_H

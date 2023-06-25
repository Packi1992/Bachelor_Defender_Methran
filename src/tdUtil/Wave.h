//
// Created by banoodle on 02.06.23.
//

#ifndef SDL_BACHELORDEFENDER_WAVE_H
#define SDL_BACHELORDEFENDER_WAVE_H
#include "../util/global.h"

struct GameEvent{
    GameEvents eventType=GameEvents::GE_Spawn;
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
    u16 health=100;
    u16 speed=100;
    u16 sanity=1;
    u16 duration=0;
    std::string text;

    bool operator< (const GameEvent &other) const{
        return time < other.time;
    }

    bool operator== (const GameEvent &other) const{
        return (type == other.type)&&
                (time == other.time)&&
                (count == other.count)&&
                (SpawnPoint == other.SpawnPoint)&&
                (value == other.value);
    }

    static GameEvent readLine(const string EventAsString);
};
#include "../td/enemy/enemy.h"

class Wave{
public:
    Wave() = default;
    // you should be able to pop Spawn Events
    // is it possible to sort a vector with specific element attribute?
    // sort with given time
    explicit Wave(int EventCount);
    // add Event takes a String should be easier to load
    void addEvent(string Event);
    // add Event kann also handle an actual spawn event
    void addEvent(GameEvent Event);
    // simply sets waveStart, it will be used to calculate spawn events
    void startWave();

    // will be false, if que is empty
    bool PollEvent(GameEvent &event);
    void Update();
    // index showing wave progress
    bool isOver();
    int index=0;
    ~Wave();


    void setName(std::string name);

    string getName();
    long getTotalEnemies();

    bool hasStarted = false;

    void clear();

private:
    Vector<GameEvent> Events{};    // i want to implement a min heap ... but i dont
    List<GameEvent> pendingEvents{};
    u32 _startTimePoint=0;
    string _name{};
    long _totalEnemies{};
    bool hasEnded = false;

};


#endif //SDL_BACHELORDEFENDER_WAVE_H

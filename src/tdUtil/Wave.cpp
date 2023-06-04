//
// Created by banoodle on 02.06.23.
//

#include "Wave.h"

Wave::Wave(int SpawnCount ) {
    enemies.resize(SpawnCount);
}

Wave::~Wave() {
    enemies.clear();
    pendingEvents.clear();
}

void Wave::addEvent(string Event) {
    // we need to define a function to write and load Spawn Events ...
    // maybe inside Struct?
    addEvent(SpawnEvent::readLine(Event));
}

bool Wave::PollEvent(SpawnEvent &event) {
    if(pendingEvents.empty())
        return false;
    event = pendingEvents.front();
    pendingEvents.pop_front();
    return true;
}

void Wave::Update(const u32 totalMSec) {
    u32 now = totalMSec-waveStart;
    for (SpawnEvent event:enemies) {
        if(event.time > now){
            pendingEvents.push_back(event);
        }
    }
    for (SpawnEvent event: pendingEvents){
        for(int i =0 ; i< enemies.size();i++){
            enemies.erase(std::remove(enemies.begin(), enemies.end(),event),enemies.end());
        }
    }
}

void Wave::addEvent(SpawnEvent Event) {
    enemies.push_back(Event);
    std::sort(enemies.begin(),enemies.end());
}

void Wave::startWave(const u32 totalMSec) {
    waveStart = totalMSec;
    hasStarted = true;
}

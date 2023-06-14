//
// Created by banoodle on 02.06.23.
//

#include "Wave.h"

Wave::Wave(int SpawnCount ) {
    Events.resize(SpawnCount);
}

Wave::~Wave() {
    Events.clear();
    pendingEvents.clear();
}

void Wave::addEvent(string Event) {
    // we need to define a function to write and load Spawn Events ...
    // maybe inside Struct?
    if(Event.substr()=="NAME")
    addEvent(SpawnEvent::readLine(Event));
}

void Wave::addEvent(SpawnEvent Event) {
    Events.push_back(Event);
    std::sort(Events.begin(), Events.end());
}

bool Wave::PollEvent(SpawnEvent &event) {
    if(pendingEvents.empty())
        return false;
    event = pendingEvents.front();
    pendingEvents.pop_front();
    return true;
}

void Wave::Update() {
    u32 now = totalMscg-waveStart;
    for (SpawnEvent event:Events) {
        if(event.time > now){
            pendingEvents.push_back(event);
        }
    }
    for (SpawnEvent event: pendingEvents){
        for(int i =0 ; i < (int)Events.size(); i++){
            Events.erase(std::remove(Events.begin(), Events.end(), event), Events.end());
        }
    }
}

void Wave::startWave() {
    waveStart = totalMscg;
    hasStarted = true;
}

bool Wave::isOver() {
    return Events.empty();
}

void Wave::setName(std::string name) {

}

SpeechEvent SpeechEvent::readLine(string input) {
    return SpeechEvent();
}

SpawnEvent SpawnEvent::readLine(string EventAsString) {
    {
        cerr << "implement Spawn Event parsing from String";
        return SpawnEvent{};
    }
}

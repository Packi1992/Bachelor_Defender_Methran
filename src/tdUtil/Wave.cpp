//
// Created by banoodle on 02.06.23.
//

#include "Wave.h"
#include "../td/testtd.h"

#include <utility>

Wave::Wave(int SpawnCount) {
    Events.resize(SpawnCount);
}

Wave::~Wave() {
    Events.clear();
    pendingEvents.clear();
}

void Wave::addEvent(string Event) {
    // we need to define a function to write and load Spawn Events ...
    // maybe inside Struct?
    if (Event.substr() == "NAME")
        addEvent(SpawnEvent::readLine(Event));
}

void Wave::addEvent(SpawnEvent Event) {
    Events.push_back(Event);
    std::sort(Events.begin(), Events.end());
}

bool Wave::PollEvent(SpawnEvent &event) {
    if (pendingEvents.empty())
        return false;
    event = pendingEvents.front();
    pendingEvents.pop_front();
    return true;
}

void Wave::Update() {
    if(hasStarted){
        if(!Events.empty()){
            u32 now = totalMscg - _startTimePoint;
            Events.erase(
                    std::remove_if(
                            Events.begin(),
                            Events.end(),
                            [&now, this](const SpawnEvent &mov) {
                                if (now >= mov.time) {
                                    pendingEvents.push_back(mov);
                                    return true;
                                }
                                return false;
                            }
                    ),
                    Events.end());
        }
        else{
            hasEnded = true;
        }
    }
}

void Wave::startWave() {
    _startTimePoint = totalMscg;
    hasStarted = true;
}

bool Wave::isOver() {
    return hasEnded && tdGlobals->_enemies.empty();
}

void Wave::setName(std::string name) {
    _name = std::move(name);
}

string Wave::getName() {
    return _name;
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

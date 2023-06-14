//
// Created by banoodle on 07.06.23.
//

#ifndef SDL_BACHELORDEFENDER_WAVEHANDLER_H
#define SDL_BACHELORDEFENDER_WAVEHANDLER_H


#include "../global.h"
#include "Wave.h"

class WaveHandler{
public:
    void pullEvent(SpawnEvent &event);
    string getWaveName();

    void addWave(Wave);
    int waveCur = 0;
    void Update();
    std::string save();
    bool load(const Vector<string>& vector1);
    Vector<Wave> waveVec;
};
#endif //SDL_BACHELORDEFENDER_WAVEHANDLER_H

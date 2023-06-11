//
// Created by banoodle on 07.06.23.
//

#include "waveHandler.h"
#include "Wave.h"

void WaveHandler::pullEvent(SpawnEvent &event) {

}

string WaveHandler::getWaveName() {
    return std::string();
}

bool WaveHandler::load(const Vector<string>& vector1) {
    Wave newWave{};
    bool waveStart = false;
    for (string line: vector1) {
        if (line.substr(0, 5) == "WAVE :") {
            waveStart = true;
        }
        if (waveStart && line.substr(0, 5) == "NAME :") {
            newWave.setName(line.substr(5));
        }
        // how should a WAVE start string look like?
        // WAVE : 1
        // NAME : super duper Wave Name
        //
        // SPAWN-EVENT : EnemyType, Time, count, SpawnPoint, value, Sanity, Speed, health
        // EVENT : .. ..
        // WAVE : 2



    }


    return false;
}

std::string WaveHandler::save() {
    return std::string();
}

void WaveHandler::addWave(Wave w) {
    waveVec.push_back(w);
}

void WaveHandler::Update(const u32 totalMSe) {

}

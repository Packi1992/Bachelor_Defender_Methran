//
// Created by banoodle on 07.06.23.
//

#include "waveHandler.h"

void WaveHandler::pullEvent(SpawnEvent &event) {

}

string WaveHandler::getWaveName() {
    return std::string();
}

bool WaveHandler::load(Vector<string> vector1) {
    cerr << "not implemented";
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
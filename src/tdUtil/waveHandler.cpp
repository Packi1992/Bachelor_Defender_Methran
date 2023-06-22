//
// Created by banoodle on 07.06.23.
//

#include "waveHandler.h"
#include "Wave.h"
#include "../td/testtd.h"

bool WaveHandler::pullEvent(GameEvent &event) {
    return _waveVec.at(_waveCur).PollEvent(event);
}

string WaveHandler::getWaveName() {
    return _waveVec.at(_waveCur).getName();
}

bool WaveHandler::load(const Vector<string> &vector1) {
    Wave newWave{};
    bool waveStart = false;
    for (string line: vector1) {
        if (line.substr(0, 5) == "WAVE :") {
            waveStart = true;
        }
        if (waveStart && line.substr(0, 5) == "NAME :") {
            newWave.setName(line.substr(5));
        }
        if (waveStart && line.substr( 0,6) == "SPAWN:"){
            newWave.addEvent(line.substr(5));
        }
        if (waveStart && line.substr(0,8) == "WAVE-END"){
            waveStart = false;
            this->_waveVec.push_back(newWave);
            newWave.clear();
        }
        // how should a WAVE start string look like?
        // WAVE : 1
        // NAME : super-duper Wave Name
        //
        // SPAWN-EVENT : EnemyType, Time, count, SpawnPoint, value, Sanity, Speed, health
        // EVENT : .. ..
        // WAVE-END
        // WAVE : 2



    }
    return false;
}

std::string WaveHandler::save() {
    return std::string();
}

void WaveHandler::addWave(const Wave &w) {
    _waveVec.push_back(w);
}

void WaveHandler::Update() {
    u32 diff = totalMSec - _lastTimePoint;
    _lastTimePoint = totalMSec;
    bool waveIsOver = _waveVec.at(_waveCur).isOver();
    bool lastWave = _waveCur+1 >= (int) _waveVec.size();
    cout << tdGlobals->_enemies.size() << endl;
    cout << (lastWave?"isLastWave":"is not LastWave") << endl;
    cout << (waveIsOver?"Wave is Over":"Wave is running")<< endl;
    _isOver = lastWave && waveIsOver;
    if (!_isOver) {
        if (_pause > diff) {
            _pause -= diff;
            std::ostringstream stringStream;
            stringStream << "Welle " << _waveCur + 1 << " startet in " << (_pause / 1000) << " Sekunden";;
            if (_counterText != stringStream.str()) {
                if (_txtTexture != nullptr)
                    SDL_DestroyTexture(_txtTexture);
                _counterText = stringStream.str();
                _txtTexture = t_cache->getText(&_counterText, 30, &_txtSrcRect, RED);
                _txtDstRect = {(windowSize.x - _txtSrcRect.w) / 2, windowSize.y / 8, _txtSrcRect.w, _txtSrcRect.h};
            }
            _doRenderCounter = true;
        } else {
            _pause = 0;
            _doRenderCounter = false;
            if (!_waveVec.at(_waveCur).hasStarted)
                _waveVec.at(_waveCur).startWave();
            _waveVec.at(_waveCur).Update();
            if (_waveVec.at(_waveCur).isOver()) {
                if (_waveCur < (int) _waveVec.size() - 1) {
                    _waveCur++;
                    tdGlobals->_pl._creditPoints += _waveCur*3;
                    _pause = 15000;
                }
            }
        }
    }
}

void WaveHandler::Render() {
    if (_doRenderCounter && !_isOver)
        rh->texture(_txtTexture, &_txtDstRect);
}

void WaveHandler::init() {
    _lastTimePoint = totalMSec;
    _pause = 15000;
}

bool WaveHandler::isOver() {
    return _isOver;
}

void WaveHandler::reset() {
    _waveCur = 0;
}

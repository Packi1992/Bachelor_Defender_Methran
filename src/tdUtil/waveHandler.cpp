//
// Created by banoodle on 07.06.23.
//

#include "waveHandler.h"
#include "Wave.h"
#include "../td/testtd.h"

bool WaveHandler::pullEvent(GameEvent &event) {
    if (!_waveVec.empty())
        return _waveVec.at(_waveCur).PollEvent(event);
    return false;
}

string WaveHandler::getWaveName() {
    return _waveVec.at(_waveCur).getName();
}

bool WaveHandler::load(const Vector<string> &vector1) {
    Wave newWave{};
    bool waveStart = false;
    for (string line: vector1) {
        if (line.substr(0, 6) == "WAVE :") {
            waveStart = true;
            continue;
        }
        if (waveStart && line.substr(0, 6) == "NAME :") {
            newWave.setName(line.substr(6));
            continue;
        }
        if (waveStart && line.substr(0, 7) == "EVENT :") {
            newWave.addEvent(line.substr(7));
            continue;
        }
        if (waveStart && line.substr(0, 9) == "WAVE-END:") {
            waveStart = false;
            this->_waveVec.push_back(newWave);
            newWave.clear();
        }
        // how should a WAVE start string look like?
        // WAVE : 1
        // NAME : super-duper Wave Name
        //
        // EVENT : EnemyType, Time, count, SpawnPoint, value, Sanity, Speed, health
        // EVENT : .. ..
        // WAVE-END
        // WAVE : 2
    }
    if (_waveVec.empty()) {
        _errorNoWavesLoaded = true;
    }
    return false;
}

std::string WaveHandler::save() {
    std::stringstream s;
    for (auto &wave: _waveVec) {
        s << "WAVE : \n" << "\n";
    }
}

void WaveHandler::addWave(const Wave &w) {
    _waveVec.push_back(w);
}

void WaveHandler::Update() {
    if (!_errorNoWavesLoaded) {
        u32 diff = totalMSec - _lastTimePoint;
        _lastTimePoint = totalMSec;
        bool waveIsOver = _waveVec.at(_waveCur).isOver();
        bool lastWave = _waveCur + 1 >= (int) _waveVec.size();
        //cout << tdGlobals->_enemies.size() << endl;
        //cout << (lastWave?"isLastWave":"is not LastWave") << endl;
        //cout << (waveIsOver?"Wave is Over":"Wave is running")<< endl;
        _isOver = lastWave && waveIsOver;
        if (!_isOver) {
            if (_pause > diff) {
                _pause -= diff;
                std::ostringstream stringStream;
                stringStream << "Welle " << _waveCur + 1 << " startet in " << (_pause / 1000) << " Sekunden";

                if (_counterText != stringStream.str()) {
                    if (_txtTexture != nullptr)
                        SDL_DestroyTexture(_txtTexture);
                    _counterText = stringStream.str();
                    _txtTexture = t_cache->getText(&_counterText, 30, &_txtSrcRect, WHITE);
                    _txtDstRect = {(windowSize.x - _txtSrcRect.w) / 2, windowSize.y / 10, _txtSrcRect.w, _txtSrcRect.h};
                }
                if (_counterText2 != stringStream.str()) {
                    if (_txtTexture != nullptr)
                        SDL_DestroyTexture(_txtTexture2);
                    _counterText2 = stringStream.str();
                    _txtTexture2 = t_cache->getText("Mach dich bereit für die", 30, &_txtSrcRect2, WHITE);
                    _txtDstRect2 = {(windowSize.x - _txtSrcRect2.w) / 2, _txtDstRect.y + _txtDstRect.h + 10,
                                    _txtSrcRect2.w, _txtSrcRect2.h};
                }
                if (_counterText3 != _waveVec.at(_waveCur).getName()) {
                    if (_txtTexture3 != nullptr)
                        SDL_DestroyTexture(_txtTexture3);
                    _counterText3 = stringStream.str();
                    _txtTexture3 = t_cache->getText((_waveVec.at(_waveCur).getName()).c_str(), 30, &_txtSrcRect3,
                                                    WHITE);
                    _txtDstRect3 = {(windowSize.x - _txtSrcRect3.w) / 2, _txtDstRect2.y + _txtDstRect2.h + 10,
                                    _txtSrcRect3.w, _txtSrcRect3.h};
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
                        tdGlobals->_pl._creditPoints += _waveCur * 3;
                        _pause = 15000;
                    }
                }
            }
        }
    }
}

void WaveHandler::Render() {
    if (_doRenderCounter && !_isOver) {
        rh->blendTexture(_txtTexture, &_txtDstRect);
        rh->blendTexture(_txtTexture2, &_txtDstRect2);
        rh->blendTexture(_txtTexture3, &_txtDstRect3);
    }
    if (_errorNoWavesLoaded)
        rh->CenteredText("Es sind keine Wave Daten hinterlegt.", 50, RED, windowSize.x,
                         windowSize.y*0.5f);
        rh->CenteredText("Map Data Korrupted", 50, RED, windowSize.x,
                     windowSize.y*0.7f);
        rh->CenteredText("Verlasse das Game mit [ESC]", 50, RED, windowSize.x,
                     windowSize.y);

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
    _waveVec.clear();
    _pause = 15000;
    _lastTimePoint = totalMSec;
    _doRenderCounter = false;
    _waveCur = 0;
}

void WaveHandler::StartNextWave() {
    _pause = 0;
}

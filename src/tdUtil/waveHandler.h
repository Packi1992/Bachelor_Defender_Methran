//
// Created by banoodle on 07.06.23.
//

#ifndef SDL_BACHELORDEFENDER_WAVEHANDLER_H
#define SDL_BACHELORDEFENDER_WAVEHANDLER_H


#include "../global.h"
#include "Wave.h"

class WaveHandler{
public:
    bool pullEvent(GameEvent &event);
    string getWaveName();

    void addWave(const Wave&);

    void Update();
    void Render();
    std::string save();
    bool load(const Vector<string>& vector1);
    bool isOver();
    void init();
private:
    Vector<Wave> _waveVec;
    u32 _pause = 15000;
    u32 _lastTimePoint=0;
    bool _doRenderCounter=false;
    int _waveCur = 0;
    string _counterText;
    SDL_Rect _txtSrcRect{};
    Texture *_txtTexture{};
    SDL_Rect _txtDstRect{};
    bool _isOver = false;
};
#endif //SDL_BACHELORDEFENDER_WAVEHANDLER_H

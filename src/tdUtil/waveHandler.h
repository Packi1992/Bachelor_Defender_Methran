//
// Created by banoodle on 07.06.23.
//

#ifndef SDL_BACHELORDEFENDER_WAVEHANDLER_H
#define SDL_BACHELORDEFENDER_WAVEHANDLER_H


#include "../util/global.h"
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
    void StartNextWave();
    void reset();

private:
    Vector<Wave> _waveVec;
    u32 _pause = 15000;
    u32 _lastTimePoint=0;
    bool _doRenderCounter=false;
    int _waveCur = 0;
    string _counterText;
    string _counterText2;
    string _counterText3;

    SDL_Rect _txtSrcRect{};
    SDL_Rect _txtSrcRect2{};
    SDL_Rect _txtSrcRect3{};
    Texture *_txtTexture{};
    Texture *_txtTexture2{};
    Texture *_txtTexture3{};
    SDL_Rect _txtDstRect{};
    SDL_Rect _txtDstRect2{};
    SDL_Rect _txtDstRect3{};
    bool _isOver = false;
};
#endif //SDL_BACHELORDEFENDER_WAVEHANDLER_H

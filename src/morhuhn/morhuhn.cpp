//
// Created by banoodle on 27.06.23.
//
#include "../util/gamebase.h"
#include "morhuhn.h"

void Moorhuhn::Init() {
    GameState::Init();
    _lastTimePoint = totalMSec;
    _tileMap = t_cache->get(BasePath "asset/graphic/td/tileTD.png");
    timer.set("Timer: ",&_timerCount,{windowSize.x/2,50},20,WHITE,true);
    killCount.set("Killed Certificates", &_killedCertificates,{100,50},20,WHITE,true);
    _timer = 100000;
}

void Moorhuhn::UnInit() {
    GameState::UnInit();
}

void Moorhuhn::Events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (pGame->HandleEvent(event))
            return;
        switch (event.type) {
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                    game.SetNextState(GS_Close);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                    _mbLeft = true;
                break;
        }
    }
}

void Moorhuhn::Update() {
    // Timer ...
    u32 diff = totalMSec - _lastTimePoint;
    _lastTimePoint = totalMSec;
    SDL_GetMouseState(&_cursor.x, &_cursor.y);
    if (_timer > diff) {
        _timer -= diff;
    }
    else{
        _timer = 0;
    }
    if(_spawnTimer > diff){
        _spawnTimer -=diff;
    }
    else{
        _spawnTimer = 0;
    }
    _timerCount = (int)(_timer /(u32)1000);

    // handle inputs
    if (_mbLeft) {
        _mbLeft = false;
        for (huhn e: _enenmies) {
            if (abs(e.pos.y - _cursor.y) < 30 && abs(e.pos.x - _cursor.x) < 30) {
                e.alive = false;
                _killedCertificates++;
            }
        }
    }

    // update enemies
    for (huhn e: _enenmies) {
        if(e.alive){
            e.pos.x += e.speed * (int)diff;
            e.drift = (int)(50.0*cos((totalMSec%360)/180.0*M_PI));
            if(e.pos.x>windowSize.x+50 || e.pos.x + 50 < 0)
                e.alive = false;
        }
    }
    if(_spawnTimer==0){
        _spawnTimer = (100-_timerCount)*50;
        for (int i = 100; i>_timerCount/5; i--){
            for(huhn e: _enenmies){
                if(!e.alive){
                    e.alive = true;
                    bool left =  totalMSec%2==0;
                    if(left){
                        e.speed = 1;
                        e.pos.x = -49;
                    }
                    else{
                        e.speed = -1;
                        e.pos.x = windowSize.x -1;
                    }
                    e.drift = (int)totalMSec%360;
                    e.pos.y = (int)(windowSize.y * (100/((int)totalMSec%90+1)))+150;
                    e.size = (int)(totalMSec % 3)*30;
                    break;
                }
            }
        }
    }

    // update ui
    ui_bg = {0, 0, windowSize.x, 100};
}

void Moorhuhn::Render() {
    rh->background(BG);
    for (huhn e: _enenmies) {
        if (e.alive) {
            enemy = {e.pos.x,e.pos.y+e.drift,e.size,e.size};
            rh->texture(_tileMap,&enemy,TdTileHandler::getSrcRect(Goal,(&enemy,(e.start+totalMSec)/10)));
        }
    }
    rh->fillRect(&ui_bg,BLACK);
    timer.Render();
    killCount.Render();

}
Moorhuhn::Moorhuhn(Game &game) : GameState(game, GS_Moorhuhn) {
}

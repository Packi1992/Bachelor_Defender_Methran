//
// Created by banoodle on 27.06.23.
//

#ifndef SDL_BACHELORDEFENDER_MORHUHN_H
#define SDL_BACHELORDEFENDER_MORHUHN_H
#include <utility>
#include "../util/dataHandler.h"
#include "../util/config.h"
#include "../util/gui/TextWithValue.h"

struct huhn{
    u32 start=0;
    Point pos{};
    int size=0;
    int speed = 0;
    int drift = 0;
    bool alive = false;
};

struct deathAnim{
    Rect pos{};
    int size=0;
    u32 start=0;
    u32 anim =0;
    bool done= true;
};
class Moorhuhn: public GameState  {
private:
    Texture *_tileMap{};
    Texture *_bg{};
    int _size=60;
    FPoint _hitSize = {0.5f,0.8f};
    Rect _bgRect{};
    huhn _enenmies[100];
    deathAnim _anims[100];
    int _killedCertificates=0;
    int32_t _timer=0;
    int _timerCount=0;
    u32 _lastTimePoint=0;
    u32 _spawnTimer=0;
    bool _mbLeft = false;
    bool _btnReturn = false;
    Point _cursor{};

    Rect ui_bg{};
    Rect enemy{};

    TextWithValue _uiTimer{};
    TextWithValue _uiKillCount{};
    TextWithValue _uiHighscore{};

    string text{};
    bool _end = false;

public:
    explicit Moorhuhn(Game &game);
    void Init() override;

    void UnInit() override;

    void Events() override;

    void Update() override;

    void Render() override;

    void clearArrays();

    bool isHit(huhn &huhn);
};


#endif //SDL_BACHELORDEFENDER_MORHUHN_H

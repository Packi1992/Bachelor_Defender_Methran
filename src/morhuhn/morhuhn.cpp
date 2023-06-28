//
// Created by banoodle on 27.06.23.
//
#include "../util/gamebase.h"
#include "morhuhn.h"

void Moorhuhn::Init() {
    GameState::Init();
    _lastTimePoint = totalMSec;
    _tileMap = t_cache->get(BasePath "asset/graphic/td/tileTD.png");
    _bg = t_cache->get(BasePath "asset/graphic/bg-main.png");
    _uiTimer.set("Zeit übrig: ", &_timerCount, {windowSize.x / 2, 50}, 20, WHITE, true);
    _uiKillCount.set("Vernichtete Zertifikate", &_killedCertificates, {100, 50}, 20, WHITE, true);
    _uiHighscore.set("Highscore: ",&config->highscoreMoorhuhn,{windowSize.x-250,50},20,WHITE,true);
    _timer = 100000;
    _timerCount = 1;
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
            case SDL_KEYDOWN:
                if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                    _btnReturn = true;
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    game.SetNextState(GS_MainMenu);
                }
                break;
        }
    }
}

void Moorhuhn::Update() {
    if (_timer <= 0 && !_end) {
        if(_killedCertificates > config->highscoreMoorhuhn){
            config->highscoreMoorhuhn = _killedCertificates;
            config->safeConfig();
        }
        if (_killedCertificates >= 100) {
            text += "du hast ";
            text += std::to_string(_killedCertificates);
            text += " vernichtet, gut gemacht";
        } else {
            text += "Du konntest leider nicht genug Zertifikate zerstören";
            _gameover = true;
        }
        _end = true;
    }
    if (_timer <= 0 && _btnReturn) {
        if (!_gameover) {
            if (config->worldsFinished < 3) {
                config->worldsFinished = 3;
                config->safeConfig();
            }
            game.SetNextState(GS_WorldMap);
        }

    }
    _btnReturn = false;
    if (_timer > 0) {
        // Timer ...
        u32 diff = totalMSec - _lastTimePoint;
        _lastTimePoint = totalMSec;
        SDL_GetMouseState(&_cursor.x, &_cursor.y);
        if (_timer > diff) {
            _timer -= diff;
        } else {
            _timer = 0;
        }
        if (_spawnTimer > diff) {
            _spawnTimer -= diff;
        } else {
            _spawnTimer = 0;
        }
        _timerCount = (int) (_timer / (u32) 1000);

        // handle inputs
        if (_mbLeft) {
            _mbLeft = false;
            for (huhn &e: _enenmies) {
                if (abs((e.pos.y + e.size / 2) - _cursor.y) < (e.size - 10) &&
                    abs((e.pos.x + e.size / 2) - _cursor.x) < (e.size - 10)) {
                    e.alive = false;
                    _killedCertificates++;
                    for (auto &deathanim: _anims) {
                        if (deathanim.done) {
                            audioHandler->playSound(SoundHashCanon, (float) e.pos.x / (float) windowSize.x);
                            deathanim.done = false;
                            deathanim.start = totalMSec;
                            deathanim.size = e.size;
                            deathanim.pos = {e.pos.x, e.pos.y + e.drift, e.size, e.size};
                            break;
                        }
                    }
                    break;
                }
            }
        }

        // update enemies
        for (huhn &e: _enenmies) {
            if (e.alive) {
                e.pos.x += e.speed * (int) diff / 8;
                e.drift = (int) (((int) (100 - _timerCount) / 10) * 15 * cos((totalMSec / 50 % 360) / 180.0 * M_PI));
                if (e.pos.x > windowSize.x + 50 || e.pos.x + 50 < 0)
                    e.alive = false;
            }
        }
        for (deathAnim &a: _anims) {
            if ((totalMSec - a.start) / 60 > 9)
                a.done = true;
        }
        if (_spawnTimer == 0) {
            _spawnTimer = (_timerCount) * 22;
            if (_timerCount < 50) {
                _spawnTimer = 250;
            }
            for (huhn &e: _enenmies) {
                if (!e.alive) {
                    e.start = totalMSec;
                    e.alive = true;
                    int speedMulti = 1;
                    if (_timerCount < 50)
                        speedMulti = 2;
                    if (_timerCount < 25)
                        speedMulti = 3;
                    bool left = (totalMSec) % 2 == 0;
                    if (left) {
                        e.speed = 1 + ((int) e.start % 3) + speedMulti;
                        e.pos.x = -49;
                    } else {
                        e.speed = -1 - ((int) e.start % 3) - speedMulti;
                        e.pos.x = windowSize.x - 1;
                    }
                    e.drift = (int) (totalMSec - e.start) % 360;
                    e.pos.y = (int) ((float) windowSize.y * (float) (((float) ((int) totalMSec % 60 + 1)) / 100.0f)) +
                              150;
                    e.size = (int) (totalMSec % 3 + 1) * 50;
                    e.pos.x += e.size / 2;
                    e.pos.y -= e.size / 2;
                    break;
                }
            }
        }

        // update ui
        ui_bg = {0, 0, windowSize.x, 100};
        _bgRect = {0, 0, windowSize.x, windowSize.y};
    }
}

void Moorhuhn::Render() {

    SDL_RenderCopy(render, _bg, nullptr, &_bgRect /* same result as EntireRect */ );

    for (int i = 1; i <= 3; i++) {
        for (huhn &e: _enenmies) {
            if (e.alive && e.size == i * 50) {
                enemy = {e.pos.x, e.pos.y + e.drift, e.size, e.size};
                //rh->fillRect(&enemy,BLACK);
                rh->texture(_tileMap, &enemy, TdTileHandler::getSrcRect(Goal, (&enemy, (int) (e.start + totalMSec))));
            }
        }
        for (deathAnim &a: _anims) {
            if (_timerCount > 0 && !a.done)
                rh->texture(_tileMap, &a.pos, TdTileHandler::getAnimSrcRect(Gameover, (totalMSec - a.start) / 60));
        }
    }
    rh->fillRect(&ui_bg, BLACK);
    _uiTimer.Render();
    _uiKillCount.Render();
    _uiHighscore.Render();
    if (_end) {
        if (_gameover) {
            rh->background(BLACK, 128);
            rh->CenteredText("Game Over", 70, RED, windowSize.x, windowSize.y);
            rh->CenteredText("Drücke Enter um fortzufahren", 40, RED, windowSize.x, windowSize.y + 450);
            rh->CenteredText(text, 40, RED, windowSize.x, windowSize.y + 300);
        } else {
            rh->background(BLACK, 128);
            rh->CenteredText("Congraz, Du hast gewonnen!", 70, GREEN, windowSize.x, windowSize.y);
            rh->CenteredText("Drücke Enter um fortzufahren", 40, GREEN, windowSize.x, windowSize.y + 450);
            rh->CenteredText(text, 40, GREEN, windowSize.x, windowSize.y + 300);
        }
    }
}

Moorhuhn::Moorhuhn(Game &game) : GameState(game, GS_Moorhuhn) {
}

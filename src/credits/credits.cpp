//
// Created by banoodle on 28.06.23.
//

#include "credits.h"

constexpr const char * text =
        "                                       --Bachelor Defender Credits --\n\n"
        "Game Design: Giona Mendicino, Jonas Westhofen, Patrick Gehlich\n"
        "Sound Design: Jonas Westhofen, Giona Mendicino, Patrick Gehlich\n"
        "Windows Unterstützung: Jonas Westhofenm, Patrick Gehlich, Giona Mendicino\n"
        "Grafik Design: Angelina Mendicino, Giona Mendicino\n"
        "Mathematik: Patrick Gehlich\n"
        "Refactoring: Patrick Gehlich\n"
        "Animations: Giona Mendicino\n\n"
        "Einen Speziellen Dank an Herrn Dalitz für die bereitstellung von Item Content\n";

void Credits::Init() {
    GameState::Init();
    blendedText = t_cache->getWrappedText(text,36,windowSize.x-200,&srcRect,WHITE);
    _creditAnim.reset();
    _creditAnim.start();
}

void Credits::UnInit() {
    GameState::UnInit();
    _creditAnim.stop();
    _creditAnim.reset();
    SDL_DestroyTexture(blendedText);
}

void Credits::Events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (pGame->HandleEvent(event))
            return;
        switch (event.type) {
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                    game.SetNextState(GS_Close);
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

void Credits::Update() {
    u32 diff = totalMSec - _lastTimePoint;
    _lastTimePoint = totalMSec;
    if (_timer <= 0) {
        if (_btnReturn)
            game.SetNextState(GS_MainMenu);
    } else {
        if (_timer > diff)
            _timer -= diff;
        else
            _timer = 0;
    }
    _btnReturn = false;
    textRect = {100,50,windowSize.x-
                200,srcRect.h};
    _creditAnim.Update();
}

void Credits::Render() {
    rh->background(BLACK);
    rh->texture(blendedText,&textRect);
    _creditAnim.Render();
}

Credits::Credits(Game &game): GameState(game,GS_Credits) {

}

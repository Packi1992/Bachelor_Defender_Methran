//
// Created by banoodle on 10.05.23.
//
#include "bddgame.h"
#include "tdUtil/editor.h"

BddGame::BddGame() :
        Game("Bachelor Defender: Methran und das goldene Zertifikat", {1280, 720},false) {
    allStates = {
            new IntroState(*this, render),
            new TestTD(*this, render),
            new Editor(*this, render),
    };

    SetNextState(0);
}

bool BddGame::HandleEvent(const Event event) {
    return Game::HandleEvent(event);
};
//
// Created by banoodle on 10.05.23.
//
#include "bddgame.h"

BddGame::BddGame() :
        Game("Bachelor Defender: Methran und das goldene Zertifikat", {1920, 1080},false) {
    allStates = {
            new IntroState(*this),
            new TestTD(*this),
            new Editor(*this),
    };

    SetNextState(0);
}

bool BddGame::HandleEvent(const Event event) {
    return Game::HandleEvent(event);
};
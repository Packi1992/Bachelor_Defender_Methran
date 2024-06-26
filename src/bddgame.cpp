//
// Created by banoodle on 10.05.23.
//
#include "bddgame.h"
#include "mainMenu/introstate.h"
#include "td/testtd.h"
#include "tdEditor/editor.h"
#include "worldMap/worldMap.h"
#include "morhuhn/morhuhn.h"
#include "credits/credits.h"

BddGame::BddGame() :
        Game("Bachelor Defender: Methran und das goldene Zertifikat", {2560, 1600}, false) {
    allStates = {
            new MainMenu(*this),
            new TestTD(*this, "gameMaps/world1.map"),
            new Editor(*this),
            new WorldMap(*this),
            new Moorhuhn(*this),
            new Credits(*this),
    };

    Game::SetNextState(GameStates::GS_MainMenu);

}

bool BddGame::HandleEvent(const Event event) {
    return Game::HandleEvent(event);
}


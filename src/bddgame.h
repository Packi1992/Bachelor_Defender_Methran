#pragma once



// gamestates

#include "util/gamebase.h"

class BddGame final : public Game {
public:
    BddGame();

    bool HandleEvent(Event event) override;
};

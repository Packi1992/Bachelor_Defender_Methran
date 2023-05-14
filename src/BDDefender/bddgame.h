#pragma once

#include "../global.h"
#include "../gamebase.h"
#include "../recthelper.h"

// gamestates
#include "introstate.h"
#include "testtd.h"

class BddGame final : public Game {
public:
    BddGame();

    bool HandleEvent(const Event event) override;
};

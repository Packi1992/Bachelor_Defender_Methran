#pragma once

#include "../global.h"
#include "../gamebase.h"
#include "../recthelper.h"

// gamestates
#include "introstate.h"
#include "td/testtd.h"
#include "tdUtil/editor.h"

class BddGame final : public Game {
public:
    BddGame();

    bool HandleEvent(const Event event) override;
};

//
// Created by dex on 6/27/23.
//

#ifndef SDL_BACHELORDEFENDER_STUNBELLANIM_H
#define SDL_BACHELORDEFENDER_STUNBELLANIM_H

#include "anim.h"

class StunBellAnim : public Anim {
private:

public:
    StunBellAnim();

    void Update() override;

    bool start() override;

    void reset() override;
};

#endif //SDL_BACHELORDEFENDER_STUNBELLANIM_H

//
// Created by dex on 6/28/23.
//

#ifndef SDL_BACHELORDEFENDER_CREDITANIM_H
#define SDL_BACHELORDEFENDER_CREDITANIM_H

#include "anim.h"

class CreditAnim: public Anim{
private:
    Rect _dstRectD{};
    Rect _dstRectG{};
    Rect _dstRectB{};
    Rect _dstRectF{};
    Rect _dstRectZ{};
    Rect _dstRun{};
    EnemyType _etype = Boss_Drueberbolz;
    bool _left = true;
public:
    CreditAnim();
    void Render() override;
    void Update() override;
    void reset() override;
};


#endif //SDL_BACHELORDEFENDER_CREDITANIM_H

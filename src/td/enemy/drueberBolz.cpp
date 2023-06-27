#include "drueberBolz.h"
#include "../testtd.h"

DrueberBolz::DrueberBolz() : BossEnemy() {
    _size = 1.2f;
}

DrueberBolz::DrueberBolz(std::shared_ptr<BossEnemy> e)
        : BossEnemy(e) {
    _recursivable = false;
    _type = EnemyType::Boss_Drueberbolz;
}

soundType DrueberBolz::getSoundName() {
    return SoundDrueberbolz;
}

#include "frolePoehlich.h"
#include "../testtd.h"

FrolePoehlich::FrolePoehlich() : BossEnemy() {
    _size = 1.2f;
}

FrolePoehlich::FrolePoehlich(std::shared_ptr<BossEnemy> e)
        : BossEnemy(e) {
    _recursivable = false;
    _sanity *= 3;
    _value *= 3;
    _type = Boss_Frohle_Poehlich;
}

soundType FrolePoehlich::getSoundName() {
    return SoundFrolePoehlich;
}
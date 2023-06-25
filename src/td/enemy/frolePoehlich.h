#ifndef SDL_BASEGAME_FrolePoehlich_H
#define SDL_BASEGAME_FrolePoehlich_H

#include "bossEnemy.h"

class FrolePoehlich : public BossEnemy {
public:
	FrolePoehlich();
	FrolePoehlich(std::shared_ptr<Enemy> e);
	soundType getSoundName() override;
};

#endif //SDL_BASEGAME_FrolePoehlich_H
#ifndef SDL_BASEGAME_BOSSENEMY_H
#define SDL_BASEGAME_BOSSENEMY_H

#include "enemy.h"

class BossEnemy : public Enemy {
public:
	BossEnemy();
	BossEnemy(std::shared_ptr<Enemy> e);
	BossEnemy(std::shared_ptr<BossEnemy> e);
	void takeDamage(Projectile* p) override;
	virtual soundType getSoundName();
	virtual void collide() override;
};

#endif //SDL_BASEGAME_BOSSENEMY_H
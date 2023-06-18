//
// Created by banoodle on 23.05.23.
//

#ifndef SDL_BACHELORDEFENDER_POINTERTOWER_H
#define SDL_BACHELORDEFENDER_POINTERTOWER_H


#include "tower.h"
#include "../projectiles/arrow.h"

class PointerTower : public Tower {
public:
    explicit PointerTower(Point pos);

    // Draws the tower
    void Render() override;

    // Place Tower on Map
    void Update() override;

    ~PointerTower() override;

    int getCosts() override;

    void setCosts(int cp) override;

    // init the Menu
    void showMenu(Gui **focus) override;

private:
    static int _creditPointCosts;
    Arrow _arrow;
};

#endif //SDL_BACHELORDEFENDER_POINTERTOWER_H

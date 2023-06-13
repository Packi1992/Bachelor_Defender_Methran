//
// Created by banoodle on 23.05.23.
//

#ifndef SDL_BACHELORDEFENDER_POINTERTOWER_H
#define SDL_BACHELORDEFENDER_POINTERTOWER_H


#include "tower.h"

class PointerTower : public Tower {
public:
    explicit PointerTower(Point pos);

    // Draws the tower
    void Render(float deltaT) override;

    // Place Tower on Map
    void Update(float deltaT) override;

    ~PointerTower() override;

    uint getCosts() override;

    void setCosts(uint cp) override;

    // init the Menu
    void showMenu(Gui **focus) override;

private:
    static int _creditPointCosts;
};

#endif //SDL_BACHELORDEFENDER_POINTERTOWER_H

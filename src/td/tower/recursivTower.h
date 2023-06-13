//
// Created by dex on 6/10/23.
//

#ifndef SDL_BACHELORDEFENDER_RECURSIVTOWER_H
#define SDL_BACHELORDEFENDER_RECURSIVTOWER_H

#include "tower.h"

class RecursivTower:public Tower {
public:
    explicit RecursivTower(Point pos);

    // Draws the tower
    void Render(float deltaT) override;

    // Place Tower on Map
    void Update(float deltaT) override;

    ~RecursivTower() override;

    uint getCosts() override;

    void setCosts(uint cp) override;

    // init the Menu
    void showMenu(Gui **focus) override;
private:
    static int _creditPointCosts;
    uint _spin = 0;
};


#endif //SDL_BACHELORDEFENDER_RECURSIVTOWER_H

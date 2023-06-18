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
    void Render() override;

    // Place Tower on Map
    void Update() override;

    ~RecursivTower() override;

    int getCosts() override;

    void setCosts(int cp) override;

    // init the Menu
    void showMenu(Gui **focus) override;

    bool updateTower() override;

private:
    static int _creditPointCosts;
    Boomerang _boomerang;
    uint _spin = 0;
};


#endif //SDL_BACHELORDEFENDER_RECURSIVTOWER_H

//
// Created by banoodle on 23.05.23.
//

#ifndef SDL_BACHELORDEFENDER_LinkedListTower_H
#define SDL_BACHELORDEFENDER_LinkedListTower_H


#include "tower.h"

class LinkedListTower : public Tower {
public:
    explicit LinkedListTower(Point pos);

    // Draws the tower
    void Render(float deltaT) override;

    // Place Tower on Map
    void Update(float deltaT) override;

    ~LinkedListTower() override;

    uint getCosts() override;

    void setCosts(uint cp) override;

    // init the Menu
    void showMenu(Gui **focus) override;

private:
    static int _creditPointCosts;
};

#endif //LinkedListTower

//
// Created by dex on 6/18/23.
//

#ifndef SDL_BACHELORDEFENDER_HASHCANON_H
#define SDL_BACHELORDEFENDER_HASHCANON_H

#include "tower.h"

class HashCanon : public Tower {
public:
    explicit HashCanon(Point pos);

    // Draws the tower
    void Render() override;

    // Place Tower on Map
    void Update() override;

    ~HashCanon() override;

    int getCosts() override;

    void setCosts(int cp) override;

    // init the Menu
    void showMenu(Gui **focus) override;

private:
    static int _creditPointCosts;
    Hashbomb _hashbomb;
};
#endif //SDL_BACHELORDEFENDER_HASHCANON_H
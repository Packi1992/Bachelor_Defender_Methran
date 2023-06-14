//
// Created by banoodle on 23.05.23.
//

#ifndef SDL_BACHELORDEFENDER_LinkedListTower_H
#define SDL_BACHELORDEFENDER_LinkedListTower_H


#include "tower.h"
#include "../../util/gui/linkEstablisher.h"

class LinkedListTower : public Tower {
public:
    explicit LinkedListTower(Point pos);

    // Draws the tower
    void Render() override;

    // Place Tower on Map
    void Update() override;

    ~LinkedListTower() override;

    uint getCosts() override;

    void setLink(LinkedListTower *before);

    void setCosts(uint cp) override;

    // init the Menu
    void showMenu(Gui **focus) override;

    bool init(Gui **focus) override;


    void setDead(bool b);

private:
    static int _creditPointCosts;
    LinkEstablisher _le;
    LinkedListTower *_last{};
    LinkedListTower *_next{};
    int _listRange=0;
};

#endif //SDL_BACHELORDEFENDER_LinkedListTower_H
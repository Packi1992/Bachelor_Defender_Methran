//
// Created by banoodle on 23.05.23.
//

#ifndef SDL_BACHELORDEFENDER_LinkedListTower_H
#define SDL_BACHELORDEFENDER_LinkedListTower_H


#include "tower.h"
#include "../../util/gui/linkEstablisher.h"
#include "../projectiles/link.h"

class LinkedListTower : public Tower {
public:
    explicit LinkedListTower(Point pos);

    // Draws the tower
    void Render() override;

    // Place Tower on Map
    void Update() override;

    ~LinkedListTower() override;

    int getCosts() override;
    [[nodiscard]] int getLinkCosts() const;

    void setLink(LinkedListTower *before);

    void setCosts(int cp) override;

    // init the Menu
    void showMenu(Gui **focus) override;

    bool init(Gui **focus) override;


    void setDead(bool b);

    LinkedListTower *getNext();

private:
    static int _creditPointCosts;
    LinkEstablisher _linkEstablisher;
    LinkedListTower *_before{};
    LinkedListTower *_next{};
    int _linkCosts = 2;
    LinkedListTower *_trigger{};
    LinkedListTower *_trigger2{};
    u16 _delay2=0;
    LinkProjectile _link;
    void sell();

    void shoot(LinkedListTower* trigger, u16 delay);
};

#endif //SDL_BACHELORDEFENDER_LinkedListTower_H

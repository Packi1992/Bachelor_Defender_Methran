//
// Created by banoodle on 23.05.23.
//

#ifndef BACHELOR_DEFENDER_TOWER_H
#define BACHELOR_DEFENDER_TOWER_H

#include "../../global.h"
#include "../../util/gui/floatingMenu.h"
class Enemy;
class Gui;
class Tower {
public:
    explicit Tower(Point pos);
    // Draws the tower
    virtual void Render(float deltaT);
    // Place Tower on Map
    virtual void Update(float deltaT);
    // give costs of tower back
    virtual uint getCosts()=0;
    virtual void setCosts(uint cp)=0;
    virtual ~Tower();
    bool isClicked(Point md);
    virtual void showMenu(Gui **focus) = 0;
    void RenderMenu(float deltaT);
    void removeFromMap();
    [[nodiscard]] bool isDead() const;
protected:
    [[nodiscard]] bool inRange(FRect p) const;
    bool aimAtEnemy(FPoint p);
    FPoint _pos{};
    Point _rPos{};
    int _health=0;
    // aim speed in degrees;
    float _aimSpeed=5;
    // direction can be between 0-359
    float _direction = 0;
    float _reloadTime=0.5;
    u8 animate=0;
    float _shootCoolDown = 10;
    u32 _damage = 0;
    Enemy* _targetEnemy{};
    int _range=1;
    bool _alive = true;
    FloatingMenu* _floatingMenu = nullptr;
    Vector<MenuEntry> _menuEntries;
    bool _showRange = false;
};
#include "pointerTower.h"
#include "recursivTower.h"
#endif //BACHELOR_DEFENDER_TOWER_H

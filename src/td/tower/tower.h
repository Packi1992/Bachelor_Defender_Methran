//
// Created by banoodle on 23.05.23.
//

#ifndef BACHELOR_DEFENDER_TOWER_H
#define BACHELOR_DEFENDER_TOWER_H

#include "../../util/global.h"
#include "../../util/gui/floatingMenu.h"

class Enemy;

class Gui;

class Tower {
public:
    [[nodiscard]] bool isRow(int row) const;
    explicit Tower(Point pos);

    virtual bool init(Gui **focus);

    // Draws the tower
    virtual void Render();

    // Place Tower on Map
    virtual void Update();

    // give costs of tower back
    virtual int getCosts() = 0;

    virtual void setCosts(int cp) = 0;

    virtual FPoint getPos();

    virtual Point getRenderPos();

    virtual int getRange();

    virtual ~Tower();

    bool isClicked(Point md);

    virtual void showMenu(Gui **focus) = 0;

    void RenderMenu();

    void removeFromMap();

    virtual bool upgrade();

    [[nodiscard]] bool isDead() const;

    [[nodiscard]] bool inRange(FRect p) const;

protected:


    bool aimAtEnemy(FPoint p);

    FPoint _pos{};
    Point _rPos{};
    int _health = 0;
    // aim speed in degrees;
    float _aimSpeed = 5;
    // direction can be between 0-359
    float _direction = 0;
    int32_t _reloadTime = 1000;
    u8 animate = 0;
    int32_t _shootCoolDown = 1000;
    u32 _damage = 0;
    std::shared_ptr<Enemy> _targetEnemy{};
    int _range = 1;
    bool _alive = true;
    FloatingMenu *_floatingMenu = nullptr;
    Vector<MenuEntry> _menuEntries;
    bool _showRange = false;
    u32 _lastTimePoint = 0;
    int _diff = 0;
    uint _level = 1;
    int _upgradeCosts = 0;
    int _sellingValue = 0;
};

#include "pointerTower.h"
#include "linkedListTower.h"
#include "recursivTower.h"
#include "hashCanon.h"
#include "stringTower.h"

#endif //BACHELOR_DEFENDER_TOWER_H

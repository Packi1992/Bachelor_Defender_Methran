//
// Created by banoodle on 23.05.23.
//

#ifndef BACHELOR_DEFENDER_TOWER_H
#define BACHELOR_DEFENDER_TOWER_H

#include "../../gamebase.h"
#include "../../tdUtil/enemy.h"
#include "../testtd.h"
class Tower {
public:
    explicit Tower(Point pos);
    // Draws the tower
    virtual void Render(float deltaT)=0;
    // Place Tower on Map
    virtual void Update(float deltaT,TestTD::TDglobals &globals)=0;
    // give costs of tower back
    virtual int getCosts()=0;
    virtual ~Tower();
protected:
    [[nodiscard]] bool inRange(FPoint p) const;
    bool aimAtEnemy(FPoint p);
    FPoint _pos{};
    Point _rPos{};
    int _health=0;
    // aim speed in degrees;
    float _aimSpeed=5;
    // direction can be between 0-359
    float _direction = 0;
    float _reloadTime=0;
    float _shootCoolDown = 10;
    u32 _damage = 0;
    Enemy* _targetEnemy{};
    int _range=0;
};
#include "pointerTower.h"

#endif //BACHELOR_DEFENDER_TOWER_H

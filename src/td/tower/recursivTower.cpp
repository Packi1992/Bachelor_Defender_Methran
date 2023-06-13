//
// Created by dex on 6/10/23.
//

#include "recursivTower.h"
#include "../testtd.h"
#include "../Projectiles/boomerang.h"
#include "../../util/gui/floatingMenu.h"

void RecursivTower::Render(float deltaT) {
    Point pos = CT::getPosOnScreen(_rPos);
    Rect dst = {pos.x, pos.y, scale, scale};
    rh->tile(&dst, TdTileHandler::getTowerSrcRect(RecursivBase));
    int anim = ((int) ((_shootCoolDown - _reloadTime))) / 2;
    long animT = (anim > 2) ? 0 : anim;
    static uint d = 0;
    if (_reloadTime <= 0.05f) {
        rh->tile(&dst, ((int) _direction) % 360, TdTileHandler::getTowerSrcRect(Boomerang, 1));
        //rh->tile(&dst, ((int) _direction)% 360, TdTileHandler::getProjectileSrcRect(ARROW));
    } else if (_reloadTime > 0.05 && _reloadTime <= 3.0f) {
        rh->tile(&dst, 360-((int)d%360), TdTileHandler::getTowerSrcRect(Boomerang, 1));
        //rh->tile(&dst, ((int) _direction)% 360, TdTileHandler::getProjectileSrcRect(ARROW));
    } else {
        rh->tile(&dst, ((int) _direction) % 360, TdTileHandler::getTowerSrcRect(Boomerang, animT));
    }
    // range
    FPoint range{0,0};
    for (int angle=0; angle <360; angle+=10){
        float angleF = angle/180.0f*M_PI;
        range.x  = _pos.x + sin(angleF)*_range;
        range.y = _pos.y + cos(angleF)*_range;
        Point range2 = CT::getPosOnScreen(range);
        Rect dst = {range2.x,range2.y,5,5};
        rh->fillRect(&dst,BLACK);

    }
    d+= 160;
}

void RecursivTower::Update(float deltaT) {
    if (_floatingMenu != nullptr) {
        _floatingMenu->Update();
        if (_floatingMenu->isDone()) {
            switch (_floatingMenu->getSelectedEntry()) {
                case MenuEntry_Sell:
                    tdGlobals->_pl._creditPoints += 2;
                    if(pMap->getObject(_rPos) == MapObjects::Tower)
                        pMap->setTile(_rPos, MapObjects::Empty);
                    _alive = false;
                    break;
                default:
                    break;
            }
            delete _floatingMenu;
            _floatingMenu = nullptr;
        }
    }
    if (_targetEnemy == nullptr) {
        for (auto &enemy: tdGlobals->_enemies) {
            if (enemy._alive) {
                if (inRange(enemy.getHitBox())) {
                    //selects first enemy
                    _targetEnemy = &enemy;
                    break;
                }
            }
        }
    } else {
        if (!inRange(_targetEnemy->getHitBox()) || !_targetEnemy->_alive) {
            _targetEnemy = nullptr;
        } else {
            if (aimAtEnemy(_targetEnemy->_pos)) {
                if (_reloadTime <= 0) {
                    _reloadTime = _shootCoolDown;
                    Projectile *p = new class Boomerang();
                    p->_direction = ((int) _direction) % 360;
                    p->_damage = _damage;
                    p->_moveable = true;
                    p->_speed = 10;
                    p->_damage = 10;
                    p->_targetE = _targetEnemy;
                    p->_size = 100;
                    p->_position = _pos;
                    p->_startingPoint = _pos;
                    float x = (float) CT::getPosOnScreen(_pos).x / float(windowSize.x);
                    //audioHandler->playSound(SoundTowerPointer, x);
                    audioHandler->playSound(SoundBoomerangFire, x);
                    tdGlobals->_ph.add(p);
                } else {
                    _reloadTime -= deltaT;
                }
            }
            // enemy target is locked -> change direction to enemy and shoot

        }
    }
}

int RecursivTower::_creditPointCosts = 5;

RecursivTower::RecursivTower(Point pos) : Tower(pos) {
    _health = 200;
    _range = 5;
    _shootCoolDown = 5;
    _damage = 25;
    _aimSpeed = 1;
    if (pMap->getObject(pos) == Empty)
        pMap->setTile(_rPos, MapObjects::Tower);
}

RecursivTower::~RecursivTower() = default;

void RecursivTower::showMenu(Gui **focus) {
    delete _floatingMenu;
    _menuEntries.clear();
    _menuEntries.push_back({MenuEntries::MenuEntry_Sell, Status_Active, 0});
    _menuEntries.push_back({MenuEntries::MenuEntry_Upgrade, Status_Active, 0});
    _floatingMenu = new FloatingMenu(&_menuEntries, _pos);
    _floatingMenu->show(focus);
}

uint RecursivTower::getCosts() {
    return _creditPointCosts;
}

void RecursivTower::setCosts(uint cp) {
    _creditPointCosts = cp;
}

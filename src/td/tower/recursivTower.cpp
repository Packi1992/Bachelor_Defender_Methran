//
// Created by dex on 6/10/23.
//

#include "recursivTower.h"
#include "../testtd.h"
#include "../projectiles/boomerang.h"
#include "../../util/gui/floatingMenu.h"

void RecursivTower::Render() {
    Point pos = CT::getPosOnScreen(_rPos);
    Rect dst = {pos.x, pos.y, scale, scale};
    rh->tile(&dst, TdTileHandler::getTowerSrcRect(RecursivBase));
    int anim = ((int) ((_shootCoolDown - _reloadTime))) / 2;
    long animT = (anim > 2) ? 0 : anim;
    if (_reloadTime <= 50) {
        rh->tile(&dst, ((int) _direction) % 360, TdTileHandler::getTowerSrcRect(Tower_Boomerang, 1));
    } else if (_reloadTime > 50 && _reloadTime <= 3000) {
        rh->tile(&dst, 360 - ((int) _spin % 360), TdTileHandler::getTowerSrcRect(Tower_Boomerang, 1));
    } else {
        rh->tile(&dst, ((int) _direction) % 360, TdTileHandler::getTowerSrcRect(Tower_Boomerang, animT));
    }
    _spin += 160;
    Tower::Render();
}

void RecursivTower::Update() {
    if (_floatingMenu != nullptr) {
        _floatingMenu->Update();
        if (_floatingMenu->isDone()) {
            switch (_floatingMenu->getSelectedEntry()) {
                case MenuEntry_Sell:
                    tdGlobals->_pl._creditPoints += _sellingValue;
                    if (pMap->getObject(_rPos) == MapObjects::Tower)
                        pMap->setTile(_rPos, MapObjects::Empty);
                    _alive = false;
                    break;
                case MenuEntry_Upgrade:
                    if ((int) tdGlobals->_pl._creditPoints >= _upgradeCosts) {
                        tdGlobals->_pl._creditPoints -= _upgradeCosts;
                        upgrade();
                    }
                    break;
                default:
                    break;
            }
            delete _floatingMenu;
            _floatingMenu = nullptr;
            _showRange = false;
        }
    }
    if (_targetEnemy == nullptr) {
        for (auto &enemy: tdGlobals->_enemies) {
            if (enemy->_alive) {
                if (inRange(enemy->getHitBox())) {
                    //selects first enemy
                    _targetEnemy = enemy;
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
                    float x = (float) CT::getPosOnScreen(_pos).x / float(windowSize.x);
                    audioHandler->playSound(SoundRecursivTower, x);
                    tdGlobals->_projectiles.push_back(std::make_shared<Boomerang>(_boomerang, _targetEnemy,(((((int) _direction) % 360)/*+90*/)%360)));
                } else {
                    _reloadTime -= _diff;
                }
            }
            // enemy target is locked -> change direction to enemy and shoot

        }
    }
    Tower::Update();
}

int RecursivTower::_creditPointCosts = 5;

RecursivTower::RecursivTower(Point pos) : Tower(pos) {
    _health = 200;
    _range = 4;
    _shootCoolDown = 6000;
    _damage = 13;
    _aimSpeed = 1;
    _upgradeCosts = 10;
    _sellingValue = 2;
    if (pMap->getObject(pos) == Empty)
        pMap->setTile(_rPos, MapObjects::Tower);

    _boomerang._damage = _damage;
    _boomerang._moveable = true;
    _boomerang._speed = 100;
    _boomerang._size = 100;
    _boomerang._position = _pos;
    _boomerang._startingPoint = _pos;
    _boomerang._freez = false;
    _boomerang._enHittable = false;
}

RecursivTower::~RecursivTower() = default;

void RecursivTower::showMenu(Gui **focus) {
    delete _floatingMenu;
    _menuEntries.clear();
    _menuEntries.push_back({MenuEntries::MenuEntry_Sell, Status_Active, 0});
    if (_level < 3) {
        MenuEntry e = {MenuEntries::MenuEntry_Upgrade, Status_Active, 0};
        if ((int) tdGlobals->_pl._creditPoints < _upgradeCosts) {
            e._status = Status_Disabled;
        }
        _menuEntries.push_back(e);
    }
    _floatingMenu = new FloatingMenu(&_menuEntries, _pos);
    _floatingMenu->show(focus);
    _showRange = true;
}

int RecursivTower::getCosts() {
    return _creditPointCosts;
}

void RecursivTower::setCosts(int cp) {
    _creditPointCosts = cp;
}

bool RecursivTower::upgrade() {
    if(Tower::upgrade()){
        switch (_level) {
            case 2:
                _damage = int((float) _damage * 1.2);
                _boomerang._damage = _damage;
                _boomerang._freez = true;
                _boomerang._stunduration += 200;
                _upgradeCosts*=2;
                _sellingValue*=2;
                break;
            case 3:
                _damage = int((float) _damage * 2);
                _boomerang._damage = _damage;
                _boomerang._stunduration += 200;
                _shootCoolDown -= 500;
                _sellingValue = (int)((float)_sellingValue * 1.5f);
                //_boomerang._enHittable = true;
                break;
            default:
                break;
        }
        return true;
    }else{
        return false;
    }
}
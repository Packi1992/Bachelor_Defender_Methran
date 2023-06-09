//
// Created by banoodle on 23.05.23.
//
#include "pointerTower.h"
#include "../testtd.h"
#include "../projectiles/arrow.h"
#include "../../util/gui/floatingMenu.h"

void PointerTower::Render() {
    Point pos = CT::getPosOnScreen(_rPos);
    Rect dst = {pos.x, pos.y, scale, scale};
    rh->tile(&dst, TdTileHandler::getTowerSrcRect(Base));
    int anim = ((int) ((_shootCoolDown - _reloadTime)));
    long animT = (anim > 4) ? 0 : anim;
    if (_reloadTime <= 1000) {
        rh->tile(&dst, ((int) _direction) % 360, TdTileHandler::getTowerSrcRect(Pointer, 1));
        if(_doubleArrow){
            rh->tile(&dst, ((int) _direction+10) % 360, TdTileHandler::getProjectileSrcRect(ARROW_FULLRECT));
            rh->tile(&dst, ((int) _direction-10) % 360, TdTileHandler::getProjectileSrcRect(ARROW_FULLRECT));
        }
        else
            rh->tile(&dst, ((int) _direction) % 360, TdTileHandler::getProjectileSrcRect(ARROW_FULLRECT));
    } else {
        rh->tile(&dst, ((int) _direction) % 360, TdTileHandler::getTowerSrcRect(Pointer, animT));
    }
    Tower::Render();
}

void PointerTower::Update() {
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
                    audioHandler->playSound(SoundPointerTower, x);
                    if (!_doubleArrow)
                        tdGlobals->_projectiles.push_back(
                                std::make_shared<Arrow>(_arrow, (_level >= 3 ? _targetEnemy : nullptr), ((int) _direction) % 360));
                    else {
                        tdGlobals->_projectiles.push_back(
                                std::make_shared<Arrow>(_arrow, (_level >= 3 ? _targetEnemy : nullptr),
                                                        ((int) _direction + 5) % 360));
                        tdGlobals->_projectiles.push_back(
                                std::make_shared<Arrow>(_arrow, (_level >= 3 ? _targetEnemy : nullptr),
                                                        ((int) (_direction < 5 ? 360 - _direction : _direction) - 5) %
                                                        360));
                    }
                } else {
                    _reloadTime -= _diff;
                }
            }
            // enemy target is locked -> change direction to enemy and shoot
        }
    }
    Tower::Update();
}

int PointerTower::_creditPointCosts = 3;

PointerTower::PointerTower(Point pos) : Tower(pos) {
    _health = 200;
    _range = 4;
    _shootCoolDown = 3000;
    _damage = 30;
    _aimSpeed = 1;
    _upgradeCosts = 5;
    _sellingValue = 2;
    if (pMap->getObject(pos) == Empty){
        pMap->setTile(_rPos, MapObjects::Tower, true);
    }



    _arrow._direction = 0;
    _arrow._damage = _damage;
    _arrow._moveable = true;
    _arrow._speed = 10;
    _arrow._targetE = nullptr;
    _arrow._size = 100;
    _arrow._position = _pos;
}

PointerTower::~PointerTower() = default;

void PointerTower::showMenu(Gui **focus) {
    delete _floatingMenu;
    _menuEntries.clear();
    _menuEntries.push_back({MenuEntries::MenuEntry_Sell, Status_Active, -_sellingValue});
    if (_level < 3) {
        MenuEntry e = {MenuEntries::MenuEntry_Upgrade, Status_Active, _upgradeCosts};
        _menuEntries.push_back(e);
    }
    _floatingMenu = new FloatingMenu(&_menuEntries, _pos);
    _floatingMenu->show(focus);
    _showRange = true;
}

int PointerTower::getCosts() {
    return _creditPointCosts;
}

void PointerTower::setCosts(int cp) {
    _creditPointCosts = cp;
}

bool PointerTower::upgrade() {
    if (Tower::upgrade()) {
        switch (_level) {
            case 2:
                _damage = (u32)((float)_damage * 1.4);
                _arrow._damage = _damage;
                _arrow._speed = 12;
                _doubleArrow = true;
                _range++;
                _upgradeCosts*=2;
                _sellingValue = (int)((float)_sellingValue * 2.0f);
                break;
            case 3:
                _damage = (u32)((float) _damage * 2.3);
                _arrow._damage = _damage;
                _arrow._speed = 18;
                _range++;
                _doubleArrow = true;
                _sellingValue = (int)((float)_sellingValue * 1.5f);
                break;
            default:
                break;
        }
        return true;
    } else {
        return false;
    }
}


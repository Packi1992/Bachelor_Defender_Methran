//
// Created by dex on 6/19/23.
//

#include "stringTower.h"
#include "../testtd.h"
#include "../projectiles/stringProjectile.h"
#include "../../util/gui/floatingMenu.h"

void StringTower::Render() {
    Point pos = CT::getPosOnScreen(_rPos);
    Rect dst = {pos.x, pos.y, scale, scale};
    rh->tile(&dst, TdTileHandler::getTowerSrcRect(TowerType::StringTower));
    Tower::Render();
}

void StringTower::Update() {
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
            if (_reloadTime <= 0) {
                _reloadTime = _shootCoolDown;
                float x = (float) CT::getPosOnScreen(_pos).x / float(windowSize.x);
                audioHandler->playSound(SoundTowerPointer, x);
                audioHandler->playSound(SoundArrowFire, x);
                _stringProjectile._string = strText.at(rand() % (int) strText.size());
                tdGlobals->_projectiles.push_back(
                        std::make_shared<StringProjectile>(_stringProjectile));
            } else {
                _reloadTime -= _diff;
            }
        }
    }
    Tower::Update();
}

int StringTower::_creditPointCosts = 3;

StringTower::StringTower(Point pos) : Tower(pos) {
    _health = 200;
    _range = 2;
    _shootCoolDown = 3000;
    _damage = 2;
    _aimSpeed = 0;
    _upgradeCosts = 8;
    _sellingValue = 2;
    if (pMap->getObject(pos) == Empty)
        pMap->setTile(_rPos, MapObjects::Tower);

    _stringProjectile._direction = 0;
    _stringProjectile._damage = _damage;
    _stringProjectile._moveable = true;
    _stringProjectile._ttl = 1400;
    //_stringProjectile._speed = 10;
    _stringProjectile._targetE = nullptr;
    _stringProjectile._fontSize = 12;
    _stringProjectile._size = 100;
    _stringProjectile._position = _pos;
    _stringProjectile._type = STRINGPROJECTILE;
}

StringTower::~StringTower() = default;

void StringTower::showMenu(Gui **focus) {
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

int StringTower::getCosts() {
    return _creditPointCosts;
}

void StringTower::setCosts(int cp) {
    _creditPointCosts = cp;
}

bool StringTower::upgrade() {
    if (Tower::upgrade()) {
        switch (_level) {
            case 2:
                _damage = int((float) _damage * 1.5);
                _stringProjectile._damage = _damage;
                _upgradeCosts *= 2;
                _sellingValue = (int) ((float) _sellingValue * 1.5f);
                _stringProjectile._fontSize += 5;
                break;
            case 3:
                _damage = int((float) _damage * 1.5);
                _stringProjectile._damage = _damage;
                _sellingValue = (int) ((float) _sellingValue * 1.5f);
                _stringProjectile._fontSize += 5;
                break;
            default:
                break;
        }
        return true;
    } else {
        return false;
    }
}
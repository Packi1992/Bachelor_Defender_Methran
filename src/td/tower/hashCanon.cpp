//
// Created by dex on 6/18/23.
//

#include "hashCanon.h"
#include "../testtd.h"
#include "../projectiles/hashbomb.h"
#include "../../util/gui/floatingMenu.h"

void HashCanon::Render() {
    Point pos = CT::getPosOnScreen(_rPos);
    Rect dst = {pos.x, pos.y, scale, scale};
    int anim = ((int) ((_shootCoolDown - _reloadTime)));
    long animT = (anim > 4) ? 0 : anim;
    if (_reloadTime <= 500) {
        rh->tile(&dst, 0, TdTileHandler::getTowerSrcRect(Hashcanon, animT));
    } else {
        rh->tile(&dst, 0, TdTileHandler::getTowerSrcRect(Hashcanon, 1));
    }
    Tower::Render();
}

void HashCanon::Update() {
    Tower::Update();
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
                audioHandler->playSound(SoundHashCanon, x);
                tdGlobals->_projectiles.push_back(
                        std::make_shared<Hashbomb>(_hashbomb, _targetEnemy));
            } else {
                _reloadTime -= _diff;
            }
            // enemy target is locked -> change direction to enemy and shoot

        }
    }
}

int HashCanon::_creditPointCosts = 6;

HashCanon::HashCanon(Point pos) : Tower(pos) {
    _health = 200;
    _range = 4;
    _shootCoolDown = 5000;
    _damage = 20;
    _aimSpeed = 1;
    _upgradeCosts = 10;
    _sellingValue = 3;
    if (pMap->getObject(pos) == Empty)
        pMap->setTile(_rPos, MapObjects::Tower, true);

    _hashbomb._direction = 0;
    _hashbomb._damage = 0;
    _hashbomb._moveable = true;
    _hashbomb._speed = 100;
    _hashbomb._targetE = nullptr;
    _hashbomb._size = 100;
    _hashbomb._speed = 100;
    _hashbomb._position = _pos;
    _hashbomb._ttl = 0;
    _hashbomb._exrange = 1;
    _hashbomb._exdmg = _damage;
}

HashCanon::~HashCanon() = default;

void HashCanon::showMenu(Gui **focus) {
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

int HashCanon::getCosts() {
    return _creditPointCosts;
}

void HashCanon::setCosts(int cp) {
    _creditPointCosts = cp;
}

bool HashCanon::upgrade() {
    if (Tower::upgrade()) {
        switch (_level) {
            case 2:
                _damage = int((float) _damage * 1.4);
                _hashbomb._exdmg = _damage;
                _hashbomb._speed = 120;
                _hashbomb._ttl = 1700;
                _range = 6;
                _upgradeCosts = (int)((float)_upgradeCosts * 1.8);
                _sellingValue = (int)((float)_sellingValue * 2.0f);
                break;
            case 3:
                _damage = int((float) _damage * 1.4);
                _hashbomb._exdmg = _damage;
                _hashbomb._exrange ++;
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

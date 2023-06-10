//
// Created by banoodle on 23.05.23.
//
#include "pointerTower.h"
#include "../testtd.h"
#include "../Projectiles/arrow.h"
#include "../../util/gui/floatingMenu.h"

void PointerTower::Render(float deltaT) {
    Point pos = CT::getPosOnScreen(_rPos);
    Rect dst = {pos.x, pos.y, scale, scale};
    rh->tile(&dst, TdTileHandler::getTowerSrcRect(Base));
    int anim = ((int) ((_shootCoolDown - _reloadTime))) / 2;
    long animT = (anim > 4) ? 0 : anim;
    if (_reloadTime <= 1) {
        rh->tile(&dst, ((int) _direction) % 360, TdTileHandler::getTowerSrcRect(Pointer, 1));
        //rh->tile(&dst, ((int) _direction)% 360, TdTileHandler::getProjectileSrcRect(ARROW));
    } else {
        rh->tile(&dst, ((int) _direction) % 360, TdTileHandler::getTowerSrcRect(Pointer, animT));
    }
}

void PointerTower::Update(float deltaT) {
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
                    Projectile *p = new Arrow();
                    p->_direction = ((int) _direction) % 360;
                    p->_damage = _damage;
                    p->_moveable = true;
                    p->_speed = 10;
                    p->_targetE = _targetEnemy;
                    p->_size = 100;
                    p->_position = _pos;
                    float x = (float) CT::getPosOnScreen(_pos).x / float(windowSize.x);
                    audioHandler->playSound(SoundTowerPointer, x);
                    audioHandler->playSound(SoundArrowFire, x);
                    tdGlobals->_ph.add(p);
                } else {
                    _reloadTime -= deltaT;
                }
            }
            // enemy target is locked -> change direction to enemy and shoot

        }
    }
}

int PointerTower::_creditPointCosts = 5;

PointerTower::PointerTower(Point pos) : Tower(pos) {
    _health = 200;
    _range = 4;
    _shootCoolDown = 3;
    _damage = 50;
    _aimSpeed = 1;
    if (pMap->getObject(pos) == Empty)
        pMap->setTile(_rPos, MapObjects::Tower);
}

PointerTower::~PointerTower() = default;

void PointerTower::showMenu(Gui **focus) {
    delete _floatingMenu;
    _menuEntries.clear();
    _menuEntries.push_back({MenuEntries::MenuEntry_Sell, Status_Active, 0});
    _menuEntries.push_back({MenuEntries::MenuEntry_Upgrade, Status_Active, 0});
    _floatingMenu = new FloatingMenu(&_menuEntries, _pos);
    _floatingMenu->show(focus);
}

uint PointerTower::getCosts() {
    return _creditPointCosts;
}

void PointerTower::setCosts(uint cp) {
    _creditPointCosts = cp;
}


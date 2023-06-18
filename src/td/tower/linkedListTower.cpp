//
// Created by banoodle on 23.05.23.
//
#include "linkedListTower.h"
#include "../testtd.h"
#include "../projectiles/projectile.h"

void LinkedListTower::Render() {
    Point pos = CT::getPosOnScreen(_rPos);
    Rect dst = {pos.x, pos.y, scale, scale};
    rh->tile(&dst, TdTileHandler::getTowerSrcRect(Tower_LinkedListBase));
    int anim = ((int) ((_shootCoolDown - _reloadTime)));
    long animT = (anim > 8) ? 0 : anim;
    if (_reloadTime <= 1) {
        rh->tile(&dst, ((int) _direction) % 360, TdTileHandler::getTowerSrcRect(Tower_LinkedList, 1));
    } else {
        rh->tile(&dst, ((int) _direction) % 360, TdTileHandler::getTowerSrcRect(Tower_LinkedList, animT));
    }
    _linkEstablisher.Render();
}

void LinkedListTower::Update() {
    // update link costs
    if (_before == nullptr && _next != nullptr) {
        _linkCosts = 1;
        LinkedListTower *cur = _next;
        do {
            _linkCosts++;
            cur = cur->_next;
        } while (cur != nullptr);
        cur = _next;
        do {
            cur->_linkCosts = _linkCosts;
            cur = cur->_next;
        } while (cur != nullptr);
    }
    if (_linkEstablisher.getDialog()) {
        _linkEstablisher.Update();
    }
    if (_floatingMenu != nullptr) {
        _floatingMenu->Update();
        if (_floatingMenu->isDone()) {
            switch (_floatingMenu->getSelectedEntry()) {
                case MenuEntry_Sell:
                    tdGlobals->_pl._creditPoints += 2;
                    if (pMap->getObject(_rPos) == MapObjects::Tower)
                        pMap->setTile(_rPos, MapObjects::Empty);
                    _alive = false;
                    sell();
                    break;
                case MenuEntry_AddLink:

                    if ((int) tdGlobals->_pl._creditPoints >= _linkCosts) {
                        tdGlobals->_pl._creditPoints -= _linkCosts;
                        _linkEstablisher.set(this, false);
                        _linkEstablisher.show(&tdGlobals->_focus);
                    }
                default:
                    break;
            }
            delete _floatingMenu;
            _floatingMenu = nullptr;
        }
    }
    if (_next != nullptr && _before == nullptr) {
        if (_shootCoolDown <= 0) {
            _shootCoolDown = (int) _reloadTime;
            std::shared_ptr<LinkProjectile> lp = std::make_shared<LinkProjectile>();
            lp->set(_reloadTime / 4, _pos, _next->_pos, _damage);
            tdGlobals->_projectiles.push_back(lp);
            _next->shoot(this, _reloadTime / 4);
        } else {
            _shootCoolDown -= _diff;
        }
    }
    if (_trigger != nullptr) {
        if (_shootCoolDown <= 0) {
            _shootCoolDown = (int) _reloadTime;
            if (_trigger == _next) {
                std::shared_ptr<LinkProjectile> lp = std::make_shared<LinkProjectile>();
                lp->set(_reloadTime / 4, _pos, _before->_pos, _damage);
                tdGlobals->_projectiles.push_back(lp);
                _before->shoot(this, _reloadTime / 4);
            } else {
                std::shared_ptr<LinkProjectile> lp = std::make_shared<LinkProjectile>();
                lp->set(_reloadTime / 4, _pos, _next->_pos, _damage);
                tdGlobals->_projectiles.push_back(lp);
                _next->shoot(this, _reloadTime / 4);
            }
            if (_trigger2 != nullptr) {
                _trigger = _trigger2;
                _shootCoolDown = _delay2;
                _trigger2 = nullptr;
            } else {
                _trigger = nullptr;
            }
        } else {
            _shootCoolDown -= _diff;
        }
    }
    Tower::Update();
}

int LinkedListTower::_creditPointCosts = 5;

LinkedListTower::LinkedListTower(Point pos) : Tower(pos) {
    _health = 200;
    _range = 4;
    _reloadTime = 4000;
    _damage = 3;
    _aimSpeed = 1;
    if (pMap->getObject(pos) == Empty)
        pMap->setTile(_rPos, MapObjects::Tower);
}

LinkedListTower::~LinkedListTower() = default;

void LinkedListTower::showMenu(Gui **focus) {
    delete _floatingMenu;
    _menuEntries.clear();
    _menuEntries.push_back({MenuEntries::MenuEntry_AddLink, Status_Active, (uint) _linkCosts});
    _menuEntries.push_back({MenuEntries::MenuEntry_Sell, Status_Active, 0});
    _menuEntries.push_back({MenuEntries::MenuEntry_Upgrade, Status_Active, 0});
    _floatingMenu = new FloatingMenu(&_menuEntries, _pos);
    _floatingMenu->show(focus);
}

int LinkedListTower::getCosts() {
    return _creditPointCosts;
}

void LinkedListTower::setCosts(int cp) {
    _creditPointCosts = (int) cp;
}

bool LinkedListTower::init(Gui **focus) {
    _linkEstablisher.set(this, true);
    _linkEstablisher.show(focus);
    return true;
}

void LinkedListTower::setLink(LinkedListTower *before) {
    _before = before;
    _next = _before->_next;
    _before->_next = this;
    if (_next != nullptr)
        _next->_before = this;
}

void LinkedListTower::setDead(bool b) {
    _alive = !b;
}

void LinkedListTower::sell() {
    if (_before != nullptr) {
        _before->sell();
    } else {
        removeFromMap();
        _alive = false;
        if (_next != nullptr) {
            _next->_before = nullptr;
            _next->sell();
        }
    }
}

LinkedListTower *LinkedListTower::getNext() {
    return _next;
}

void LinkedListTower::shoot(LinkedListTower *trigger, u16 delay) {
    bool shoot = true;
    if (trigger == _before)
        shoot = (_next != nullptr);
    if (trigger == _next)
        shoot = (_before != nullptr);
    if (shoot) {
        if (_trigger != nullptr) {
            _trigger2 = trigger;
            _delay2 = delay;
        } else {
            _trigger = trigger;
            _shootCoolDown = delay;
        }
    }
}

int LinkedListTower::getLinkCosts() const {
    return _linkCosts;
}


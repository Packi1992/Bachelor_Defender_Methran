//
// Created by banoodle on 23.05.23.
//
#include "linkedListTower.h"
#include "../testtd.h"
#include "../Projectiles/projectile.h"
#include "../../util/gui/floatingMenu.h"
#include "../../tdUtil/projectilesHandler.h"

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
    _listRange = 3;
    _le.Render();
}

void LinkedListTower::Update() {
    if(_le.getDialog()){
        _le.Update();
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
                    break;
                default:
                    break;
            }
            delete _floatingMenu;
            _floatingMenu = nullptr;
        }
    }
    if(_next!= nullptr){
        if(_shootCoolDown<=0){
            _shootCoolDown = _reloadTime;
            auto *lp = new LinkProjectile();
            lp->set(0,10,_pos,_next->_pos,200);
            tdGlobals->_ph.add(lp);

        }
        else{
            _shootCoolDown -= deltaTg;
        }
    }
}

int LinkedListTower::_creditPointCosts = 5;

LinkedListTower::LinkedListTower(Point pos) : Tower(pos) {
    _health = 200;
    _range = 4;
    _shootCoolDown = 3;
    _damage = 50;
    _aimSpeed = 1;
    if (pMap->getObject(pos) == Empty)
        pMap->setTile(_rPos, MapObjects::Tower);
}

LinkedListTower::~LinkedListTower() = default;

void LinkedListTower::showMenu(Gui **focus) {
    delete _floatingMenu;
    _menuEntries.clear();
    _menuEntries.push_back({MenuEntries::MenuEntry_Sell, Status_Active, 0});
    _menuEntries.push_back({MenuEntries::MenuEntry_Upgrade, Status_Active, 0});
    _floatingMenu = new FloatingMenu(&_menuEntries, _pos);
    _floatingMenu->show(focus);
}

uint LinkedListTower::getCosts() {
    return _creditPointCosts;
}

void LinkedListTower::setCosts(uint cp) {
    _creditPointCosts = (int)cp;
}

bool LinkedListTower::init(Gui **focus) {
    _le.set(this,true);
    _le.show(focus);
}

void LinkedListTower::setLink(LinkedListTower *before) {
    _last = before;
    _next = _last->_next;
    _last->_next = this;
    if(_next != nullptr)
        _next->_last = this;
}

void LinkedListTower::setDead(bool b) {
    _alive = !b;
}


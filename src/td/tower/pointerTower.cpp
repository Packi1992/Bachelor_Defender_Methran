//
// Created by banoodle on 23.05.23.
//
#include "pointerTower.h"
#include "../testtd.h"

void PointerTower::Render(float deltaT) {
    Point pos = CT::getPosOnScreen(_rPos);
    Rect dst = {pos.x, pos.y, scale, scale};
    rh->tile(&dst, TdTileHandler::getTowerSrcRect(Base));
    int anim = ((int)((_shootCoolDown-_reloadTime)))/2;
    long animT = (anim >4) ? 0 : anim;
    if(_reloadTime<=1) {
        rh->tile(&dst, ((int)_direction)%360,TdTileHandler::getTowerSrcRect(Pointer, 1));
        //rh->tile(&dst, ((int) _direction)% 360, TdTileHandler::getProjectileSrcRect(ARROW));
    }
    else{
        rh->tile(&dst, ((int)_direction)%360,TdTileHandler::getTowerSrcRect(Pointer, animT));
    }
}

void PointerTower::Update(float deltaT) {
    if (_targetEnemy == nullptr) {
        for(auto &enemy: tdGlobals->_enemies){
            if(enemy._alive){
                if(inRange(enemy.getHitBox())){
                    //selects first enemy
                    _targetEnemy = &enemy;
                    break;
                }
            }
        }
    }
    else{
        if(!inRange(_targetEnemy->getHitBox())||!_targetEnemy->_alive){
            _targetEnemy = nullptr;
        }
        else{
            if(aimAtEnemy(_targetEnemy->_pos)){
                if(_reloadTime<=0){
                    _reloadTime = _shootCoolDown;
                    Projectile *p = new Arrow();
                    p->_direction = ((int)_direction)%360;
                    p->_damage = _damage;
                    p->_moveable = true;
                    p->_speed = 10;
                    p->_targetE = _targetEnemy;
                    p->_size = 100;
                    p->_position = _pos;

                    tdGlobals->_ph.add(p);
                }
                else{
                    _reloadTime -=deltaT;
                }
            }
            // enemy target is locked -> change direction to enemy and shoot

        }
    }
}

int PointerTower::getCosts() {
    return 100;
}

PointerTower::PointerTower(Point pos) : Tower(pos) {
    _health = 200;
    _range = 4;
    _shootCoolDown = 3;
    _damage = 100;
    _aimSpeed = 1;
    if (pMap->getObject(pos) == Empty)
        pMap->setTile(_rPos, MapObjects::Tower);
}

PointerTower::~PointerTower() {
    Tower::~Tower();
}


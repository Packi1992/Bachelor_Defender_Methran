//
// Created by banoodle on 23.05.23.
//
#include "pointerTower.h"

void PointerTower::Render(float deltaT) {
    Point pos = CT::getPosOnScreen(_rPos);
    Rect dst = {pos.x, pos.y, scale, scale};
    rh->tile(&dst, TdTileHandler::getTowerSrcRect(TdTileHandler::Base));
    rh->tile(&dst, ((int)_direction)%360,TdTileHandler::getTowerSrcRect(TdTileHandler::Pointer));
}

void PointerTower::Update(float deltaT, TestTD::TDglobals &globals) {
    if (_targetEnemy == nullptr) {
        for(auto &enemy: globals._enemies){
            if(enemy._alive){
                if(inRange(enemy._pos)){
                    //selects first enemy
                    _targetEnemy = &enemy;
                    break;
                }
            }
        }
    }
    else{
        if(!inRange(_targetEnemy->_pos)||!_targetEnemy->_alive){
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

                    globals._ph.add(p);
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
    _shootCoolDown = 1;
    _damage = 100;
    if (pMap->getObject(pos) == TdTileHandler::Empty)
        pMap->setTile(_rPos, TdTileHandler::Tower);
}

PointerTower::~PointerTower() {
    Tower::~Tower();
}


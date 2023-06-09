//
// Created by banoodle on 23.05.23.
//

#include "tower.h"
#include "../../tdUtil/enemy.h"
#include "../../recthelper.h"
#include "../../util/gui/floatingMenu.h"

Tower::Tower(Point pos) {
    _pos = {(float)pos.x+0.5f,(float)pos.y+0.5f};
    _rPos = pos;
    _health = 10;
}

bool Tower::inRange(FRect p) const {
    return _range*_range >= pow((p.x+p.w*0.5)-_pos.x,2)+pow((p.y+p.h*0.5)-_pos.y,2);
}

bool Tower::aimAtEnemy(FPoint p) {
    // calculate enemy direction
    float y = _targetEnemy->_pos.y-_pos.y;
    float x = _targetEnemy->_pos.x-_pos.x;
    bool above=false;
    if(y<0){
        //target is below
        above = true;
        y = -y;
    }
    if(y==0){
        above = true;
    }
    bool left = false;
    if(x<0){
        left = true;
        x =-x;
    }
    if(x==0){
        left = true;
    }
    float alpha = atan(y/x)*180/(float)M_PI;
    if(above&&!left)
        alpha = (float)((int)(90-alpha)%360);
    if(!above&&!left)
        alpha +=90;
    if(left&&!above){
        alpha = (float)((int)(90-alpha)%360);
        alpha +=180;
    }
    if(left&above)
        alpha +=270;
    alpha = (float)((int)(alpha)%360);
    if(alpha == _direction){
        return true;
    }
    else{
        // try aiming at enemy
        // alpha = 350 / dir = 10 - left turn would be nice
        if(((int)alpha+180)%360>=(int)_direction){
            // go counterclockwise
            _direction= (float)((int)(_direction - _aimSpeed)%360);
            if(_direction<alpha){
                _direction=alpha;
            }
        }
        else{
            _direction= (float)((int)(_direction + _aimSpeed)%360);
            if(_direction>alpha){
                _direction=alpha;
            }
        }
        if((int)(_direction-alpha)%360<5)
            return true;
        return false;
    }
}

bool Tower::isClicked(Point md) {
    Point t = CT::getTileInGame(md);
    return (CT::getTileInGame(md) == _rPos);
}

void Tower::RenderMenu(float deltaT){
    if(_floatingMenu != nullptr)
        _floatingMenu->Render();
}

Tower::~Tower() = default;


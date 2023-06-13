//
// Created by banoodle on 23.05.23.
//

#include "tower.h"
#include "../../tdUtil/enemy.h"
#include "../../recthelper.h"
#include "../../util/gui/floatingMenu.h"
#include "../../tdUtil/map.h"

Tower::Tower(Point pos) {
    _pos = {(float) pos.x + 0.5f, (float) pos.y + 0.5f};
    _rPos = pos;
    _health = 10;
}

bool Tower::inRange(FRect p) const {
    return _range * _range >= pow((p.x + p.w * 0.5) - _pos.x, 2) + pow((p.y + p.h * 0.5) - _pos.y, 2);
}

bool Tower::aimAtEnemy(FPoint p) {
    // calculate enemy direction
    float alpha = CT::getAngle(_pos, _targetEnemy->_pos);
    if (alpha == _direction) {
        return true;
    } else {
        // try aiming at enemy
        // alpha = 350 / dir = 10 - left turn would be nice
        if (((int) alpha + 180) % 360 >= (int) _direction) {
            // go counterclockwise
            _direction = (float) ((int) (_direction - _aimSpeed) % 360);
            if (_direction < alpha) {
                _direction = alpha;
            }
        } else {
            _direction = (float) ((int) (_direction + _aimSpeed) % 360);
            if (_direction > alpha) {
                _direction = alpha;
            }
        }
        if ((int) (_direction - alpha) % 360 < 5)
            return true;
        return false;
    }
}

bool Tower::isClicked(Point md) {
    return (CT::getTileInGame(md) == _rPos);
}

void Tower::RenderMenu(float deltaT) {
    if (_floatingMenu != nullptr)
        _floatingMenu->Render();
}

void Tower::removeFromMap() {
    if (pMap->getObject(_rPos) == MapObjects::Tower) {
        pMap->setTile(_rPos, MapObjects::Empty);
    }
}

Tower::~Tower() {
    this->removeFromMap();
}

bool Tower::isDead() const {
    return !_alive;
}

bool Tower::init() {
    return true;
}

void Tower::Render(float deltaT) {
    // range
    if (_showRange) {
        FPoint range{0, 0};
        for (int angle = 0; angle < 360; angle += 10) {
            float angleF = (float) angle / 180.0f * (float) M_PI;
            range.x = _pos.x + sin(angleF) * (float) _range;
            range.y = _pos.y + cos(angleF) * (float) _range;
            Point range2 = CT::getPosOnScreen(range);
            Rect dst = {range2.x, range2.y, 5, 5};
            rh->fillRect(&dst, BLACK);
        }
    }
}

void Tower::Update(float deltaT) {
    if (_floatingMenu != nullptr) {
        if (!_floatingMenu->getDialog())
            _showRange = false;
    }
}


//
// Created by banoodle on 22.06.23.
//

#include "checkSymbol.h"

void CheckSymbol::set(MenuEntry entry, Rect pos) {
    _entry = entry;
    _pos = pos;
}

bool CheckSymbol::clicked(Point p) {
    if(isPointOnBox(p)){
        _checked=!_checked;
    }
    if(_checked)
        _entry._status = Status_Active;
    else
        _entry._status = Status_Disabled;
}

CheckSymbol::CheckSymbol(const CheckSymbol &b) {
    _entry = b._entry;
    _pos = b._pos;
    _checked = b._checked;
}

bool CheckSymbol::isChecked() const {
    if(_entry._status == Status_Disabled)
        return true;
    else
        return false;
}

bool CheckSymbol::isPointOnBox(Point &p) const {
    bool xAxis = this->_pos.x <= p.x && this->_pos.x + this->_pos.w >= p.x;
    bool yAxis = this->_pos.y <= p.y && this->_pos.y + this->_pos.h >= p.y;
    return xAxis && yAxis;
}

void CheckSymbol::Render() {
    rh->symbol(&_pos, _entry);
}

void CheckSymbol::setChecked(bool b) {
    _checked = b;
}

MenuEntries CheckSymbol::getMenuEntry() {
    return _entry._menuEntry;
}

CheckSymbol::CheckSymbol(MenuEntries entry, bool checked) {
    set({entry,checked?Status_Active:Status_Disabled,0},{});
}

void CheckSymbol::setPos(Rect pos) {
    _pos = pos;
}

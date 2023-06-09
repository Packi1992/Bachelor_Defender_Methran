//
// Created by dex on 6/9/23.
//
#include "../../gamebase.h"
#include "floatingmenu.h"

FloatingMenu::FloatingMenu(Vector<MenuEntries> * menuEntries, FPoint pos) {
    _menuTexture = t_cache->get(BasePath "asset/graphic/td/floatingMenu.png");
    _menuEntries = menuEntries;
    _position = pos;
    if(_menuEntries->size() > 6)
        cerr << "Max six entries in menu possible" << endl;
}

void FloatingMenu::setPosition(Point p) {

}

void FloatingMenu::enable() {

}

void FloatingMenu::Render(float deltaT) {
    Point renderPos = CT::getPosOnScreen(_position);
    int size = (int)((float)windowSize.x * 0.15f);
    Rect dst = {renderPos.x - size/2, renderPos.y - size/2, size,  size};
    Rect src = {0,0,192,192};
    int direction = 30;
    for(int i = 0; i < _menuEntries->size() || i == 6; i++){
        rh->texture(_menuTexture,&dst,direction,&src);
        direction = (direction + 300) % 360;
    }
}

void FloatingMenu::Update(float deltaT) {

}

void FloatingMenu::setEntries() {

}

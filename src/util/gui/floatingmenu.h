//
// Created by dex on 6/9/23.
//

#ifndef SDL_BACHELORDEFENDER_FLOATINGMENU_H
#define SDL_BACHELORDEFENDER_FLOATINGMENU_H

#include "../../gamebase.h"
class FloatingMenu {
private:
    bool _activ = false;
    FPoint _position{};
    Texture * _menuTexture{};
    Vector<MenuEntries>* _menuEntries{};
public:
    FloatingMenu(Vector<MenuEntries> * menuEntries, FPoint tileCenter);
    void setPosition(Point p);
    void enable();
    void Render(float deltaT);
    void Update(float deltaT);
    void setEntries();
};


#endif //SDL_BACHELORDEFENDER_FLOATINGMENU_H

//
// Created by banoodle on 25.05.23.
//

#ifndef SDL_BACHELORDEFENDER_GUI_H
#define SDL_BACHELORDEFENDER_GUI_H
class Gui;
#include "../gamebase.h"
class Gui{
public:
    virtual void Input()=0;
    virtual void Render()=0;
    virtual void Update()=0;
    virtual void setFocus(Gui *next)=0;
};
#endif //SDL_BACHELORDEFENDER_GUI_H

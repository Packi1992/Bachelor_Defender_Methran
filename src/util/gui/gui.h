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
    virtual void releaseFocus(bool continueRender);
    void show(Gui **focus);
    void setNextFocus(Gui *next);
    [[nodiscard]] bool getDialog() const;
    [[nodiscard]] bool isActive() const;
protected:
    Event _lastEvent{};
    bool dialog=false;
    Gui **focus{};
    Gui *nextFocus{};
};

#endif //SDL_BACHELORDEFENDER_GUI_H

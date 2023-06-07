//
// Created by banoodle on 27.05.23.
//
#include "gui.h"
void Gui::show(Gui **pFocus) {
    focus = pFocus;
    dialog = true;
    *pFocus = this;
}

void Gui::releaseFocus(Event *event, bool continueRender) {
    if(event != nullptr)
        lastEvent=*event;
    *focus = nextFocus;
    dialog = continueRender;
}

void Gui::setNextFocus(Gui *next) {
    nextFocus = next;
}

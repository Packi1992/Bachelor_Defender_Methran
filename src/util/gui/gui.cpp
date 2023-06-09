//
// Created by banoodle on 27.05.23.
//
#include "gui.h"
void Gui::show(Gui **pFocus) {
    focus = pFocus;
    dialog = true;
    *pFocus = this;
}

void Gui::releaseFocus(bool continueRender) {
    *focus = nextFocus;
    dialog = continueRender;
    nextFocus = nullptr;
}

void Gui::setNextFocus(Gui *next) {
    nextFocus = next;
}

bool Gui::isActive() const {
    return dialog;
}

bool Gui::getDialog() const {
    return dialog;
}
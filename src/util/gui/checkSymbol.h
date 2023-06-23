//
// Created by banoodle on 22.06.23.
//

#ifndef SDL_BACHELORDEFENDER_CHECKSYMBOL_H
#define SDL_BACHELORDEFENDER_CHECKSYMBOL_H
#include "../gamebase.h"
#include "floatingMenu.h"

class CheckSymbol {
private:
    MenuEntry _entry{MenuEntry_Error,Status_Disabled,0};
    Rect _pos{};
    bool _checked=false;
public:
    CheckSymbol() = default;
    CheckSymbol(MenuEntries entry, bool checked);
    MenuEntries getMenuEntry();
    void set(MenuEntry entry,Rect _pos);
    void setPos(Rect pos);
    bool clicked(Point p);
    CheckSymbol(const CheckSymbol &b);
    bool isChecked() const;
    bool isPointOnBox(Point &p) const;
    void Render();

    void setChecked(bool b);
};


#endif //SDL_BACHELORDEFENDER_CHECKSYMBOL_H

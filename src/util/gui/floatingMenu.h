//
// Created by dex on 6/9/23.
//

#ifndef SDL_BACHELORDEFENDER_FLOATINGMENU_H
#define SDL_BACHELORDEFENDER_FLOATINGMENU_H

#include "../../gamebase.h"
#include "gui.h"

class FloatingMenu: public Gui {
public:
    FloatingMenu(Vector<MenuEntries> * menuEntries, FPoint tileCenter);
    void set(Vector<MenuEntries> * menuEntries, FPoint tileCenter);
    FloatingMenu() = default;
    void setPosition(FPoint p);
    void Input() override;
    void Render() override;
    void Update() override;
    bool isDone();
    FPoint getPos();
    void setEntries(Vector<MenuEntries> * menuEntries);
    MenuEntries getSelectedEntry();
    [[nodiscard]] bool onMenu(Point clickPos) const;
    [[nodiscard]] static bool onSymbol(Point click, Point symbol, float symbolRadiant);
    void reset();
private:
    static int getSize();
    FPoint _position{};
    Point _clickPos{};
    int _wheelDiff=0;
    Point _clickRel{};
    bool _mbRightDown = false;
    bool _mbLeftDown = false;

    int _selectedEntry=-1;
    Texture * _menuTexture{};
    Vector<MenuEntries>* _menuEntries{};
};


#endif //SDL_BACHELORDEFENDER_FLOATINGMENU_H

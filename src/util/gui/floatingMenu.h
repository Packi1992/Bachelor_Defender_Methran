//
// Created by dex on 6/9/23.
//

#ifndef SDL_BACHELORDEFENDER_FLOATINGMENU_H
#define SDL_BACHELORDEFENDER_FLOATINGMENU_H

#include "../../gamebase.h"
#include "gui.h"

struct MenuEntry{
    MenuEntries _menuEntry=MenuEntry_DEFAULT;
    Status _status = Status_Active;
    uint _costs = 0;
};

class FloatingMenu: public Gui {
public:
    FloatingMenu(Vector<MenuEntry> * menuEntriesInfos, FPoint tileCenter);
    void set(Vector<MenuEntry> * menuEntriesInfos, FPoint tileCenter);
    FloatingMenu() = default;
    void setPosition(FPoint p);
    void Input() override;
    void Render() override;
    void Update() override;
    bool isDone();
    FPoint getPos();
    void setEntries(Vector<MenuEntry> * menuEntriesInfos);
    MenuEntries getSelectedEntry();
    [[nodiscard]] bool onMenu(Point clickPos) const;
    [[nodiscard]] static bool onSymbol(Point click, Point symbol, float symbolRadiant);
    void reset();
    virtual ~FloatingMenu();
private:
    // zoom handling
    bool _mouseWheel = false;
    SDL_Event _wheelEvent{};
    static int getSize();
    FPoint _position{};
    Point _clickPos{};
    Point _clickRel{};
    bool _mbRightDown = false;
    bool _mbLeftDown = false;

    int _selectedEntry=-1;
    Texture * _menuTexture{};
    Vector<MenuEntry>* _menuEntries{};
};
#endif //SDL_BACHELORDEFENDER_FLOATINGMENU_H
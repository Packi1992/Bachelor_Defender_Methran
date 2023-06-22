//
// Created by banoodle on 22.04.23.
//

#ifndef BOULDERDASH_PLAYERSETTINGS_H
#define BOULDERDASH_PLAYERSETTINGS_H

#include <set>
#include "../gamebase.h"
#include "gui.h"
#include "textbox.h"
#include "Button.h"
#include "checkSymbol.h"
class Player;

class PlayerSettings: public Gui{
public:
    PlayerSettings();
    void set(Player *pl);
    ~PlayerSettings();
    // read values
    int getCreditPoints();
    int getSanity();
    std::set<MenuEntries> getUsableTowers();

    void Input() override;
    void Render() override;
    void Update() override;

    [[nodiscard]] bool isDone() const;

    void reset();

private:
    void iniUI();
    void iniValues();

    // _dialog dest
    Rect _rDialog{};

    // title
    Rect _rTitle{};
    Texture *_texTitle{};

    // buttons
    Button _btn_ok;
    Button _btn_abb;

    // Input handling
    Gui *focus{};
    int _creditPoints=0;
    int _sanity=0;

    // towerText
    Rect _rTowerText{};
    Texture *_texTowerText{};
    Vector<CheckSymbol> _usableTowers;
    TextBox _txtb_sanity;
    TextBox _txtb_creditPoints;

    bool _takeNewValues = false;

    void handleEvent(Event event);
    void selection(Event event);
    void acceptInput();
};


#endif //BOULDERDASH_PLAYERSETTINGS_H

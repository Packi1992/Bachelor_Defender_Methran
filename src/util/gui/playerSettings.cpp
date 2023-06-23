//
// Created by banoodle on 22.04.23.
//

#include "playerSettings.h"
#include "../../tdUtil/player.h"

void PlayerSettings::set(Player pl) {
    _creditPoints = (int) pl._creditPoints;
    _sanity = (int) pl._sanity;
    for (auto &entry: pl._usableTowers) {
        _entries.insert(entry);
        for(auto &e: _usableTowers)
            if(e.getMenuEntry() == entry)e.setChecked(true);
    }
    iniUI();
    iniValues();
}


void PlayerSettings::iniValues() {
    _txtb_sanity.setNumber(_creditPoints);
    _txtb_creditPoints.setNumber(_sanity);
}

void PlayerSettings::iniUI() {
    _rDialog = {windowSize.x / 2 - 250, windowSize.y / 2 - 200, 500, 400};
    // Title
    _texTitle = t_cache->getText("Map Einstellungen", 30, &_rTitle);
    // Align Buttons
    _texTowerText = t_cache->getText("verfügbare Tower", 20, &_rTowerText);

    int btnY = _rDialog.y + _rDialog.h - 50;

    _rTitle.x = _rDialog.x + _rDialog.w / 2 - _rTitle.w / 2;
    _rTitle.y = _rDialog.y + 10;
    _btn_ok.set("OK", 18, {_rDialog.x + _rDialog.w - 100, btnY, 80, 40});
    _btn_abb.set("ABBRUCH", 18, {_rDialog.x + 20, btnY, 100, 40});
    _txtb_sanity.set("Sanity", {_rDialog.x + 70, _rDialog.y + 80}, true);
    _txtb_creditPoints.set("Credit Points", {_rDialog.x + 20, _rDialog.y + 160}, true);
    _rTowerText.x = _rDialog.x + _rDialog.w / 2 - _rTitle.w / 2;
    _rTowerText.y = _rDialog.y + 240;
    int yPos= _rDialog.y + 280;
    int xPos= _rDialog.x +40;
    for (auto &entry: _usableTowers) {
        entry.setPos({xPos,yPos,50,50});
        xPos += 60;
    }
}


void PlayerSettings::Input() {
    if (focus != nullptr)
        focus->Input();
    if (focus == nullptr) {
        Event event;
        while (SDL_PollEvent(&event)) {
            if (pGame->HandleEvent(event))
                return;
            handleEvent(event);
        }
    }
}

void PlayerSettings::handleEvent(Event event) {
    switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            selection(event);
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_ESCAPE:
                    releaseFocus(false);
                    break;
                case SDL_SCANCODE_KP_ENTER:
                    acceptInput();
                    break;
                default:
                    break;
            }
    }
}


void PlayerSettings::selection(Event event) {
    if (event.button.button == SDL_BUTTON_LEFT) { //left mouse button
        if (_txtb_creditPoints.fieldSelected(event)) {
            _txtb_creditPoints.show(&focus);
        }
        if (_txtb_sanity.fieldSelected(event)) {
            _txtb_sanity.show(&focus);
        }
        for (auto &entry: _usableTowers) {
            entry.clicked({event.motion.x,event.motion.y});
        }
        if (_btn_ok.clicked(event)) {
            acceptInput();
        }
        if (_btn_abb.clicked(event)) {
            releaseFocus(false);
            reset();
        }
    }
}

void PlayerSettings::acceptInput() {
    releaseFocus(false);
    _creditPoints = _txtb_sanity.getNumber();
    _sanity = _txtb_creditPoints.getNumber();

    for (auto &entry: _usableTowers) {
        if(entry.isChecked())
            _entries.insert(entry.getMenuEntry());
    }
    _takeNewValues = true;
}

void PlayerSettings::Render() {
    if (dialog) {
        rh->fillRect(&_rDialog, EDITOR_UI_BG);
        rh->texture(_texTitle, &_rTitle);
        _txtb_sanity.Render();
        _txtb_creditPoints.Render();
        _btn_ok.draw();
        _btn_abb.draw();
        rh->texture(_texTowerText,&_rTowerText);

        for (auto &entry: _usableTowers) {
            entry.Render();
        }
        rh->rect(&_rDialog, 3, BLACK);
    }
}

void PlayerSettings::Update() {
}

int PlayerSettings::getCreditPoints() {
    return _sanity;
}

int PlayerSettings::getSanity() {
    return _creditPoints;
}

bool PlayerSettings::isDone() const {
    return _takeNewValues;
}


PlayerSettings::~PlayerSettings() {
    SDL_DestroyTexture(_texTitle);
    _usableTowers.clear();
}

void PlayerSettings::reset() {
    _takeNewValues = false;
    for(auto &e: _usableTowers)
        e.setChecked(false);
    _entries.clear();
}

std::set<MenuEntries> PlayerSettings::getUsableTowers() {
    return _entries;
}

PlayerSettings::PlayerSettings() {
    _usableTowers.emplace_back(MenuEntry_POINTER,false);
    _usableTowers.emplace_back(MenuEntry_BOOMERANG,false);
    _usableTowers.emplace_back(MenuEntry_LinkedList,false);
    _usableTowers.emplace_back(MenuEntry_HASHCANON,false);
    _usableTowers.emplace_back(MenuEntry_STRINGTOWER,false);
}



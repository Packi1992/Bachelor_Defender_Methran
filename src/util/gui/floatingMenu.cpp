//
// Created by dex on 6/9/23.
//
#include "../../recthelper.h"
#include "../../tdUtil/map.h"
#include "floatingMenu.h"
#include "../../td/testtd.h"

void FloatingMenu::Input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        _lastEvent = event;
        if (pGame->HandleEvent(event))
            return;
        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                _clickPos = {event.motion.x, event.motion.y};
                if (event.button.button == SDL_BUTTON_RIGHT) {
                    _mbRightDown = true;
                }
                if (event.button.button == SDL_BUTTON_LEFT) {
                    _mbLeftDown = true;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_RIGHT) {
                    _mbRightDown = false;
                }
                if (event.button.button == SDL_BUTTON_LEFT) {
                    _mbLeftDown = false;
                }
                break;
            case SDL_MOUSEMOTION:
                _clickPos = {event.motion.x, event.motion.y};
                _clickRel = {event.motion.xrel, event.motion.yrel};
                break;
            case SDL_MOUSEWHEEL:
                _mouseWheel = true;
                _wheelEvent = event;
                break;
        }
    }
}

bool FloatingMenu::onSymbol(Point click, Point symbol, float symbolRadiant) {
    return symbolRadiant * symbolRadiant >= pow(click.x - symbol.x, 2) + pow(click.y - symbol.y, 2);
}


bool FloatingMenu::onMenu(Point clickPos) const {
    Point menuPos = CT::getPosOnScreen(_position);
    float size = (float) getSize() * 0.493f;
    auto clickDistanceSquared = (float)(pow(menuPos.x - clickPos.x, 2) + pow(menuPos.y - clickPos.y, 2));
    bool assertDistanceUpper = size * size >= clickDistanceSquared;
    float size2 = size * 0.42f;
    bool assertDistanceBottom = size2 * size2 <= clickDistanceSquared;
    if (_menuEntries->size() == 6)
        return assertDistanceUpper && assertDistanceBottom;

    // if less than 6 entries, lets have a look at the click angle
    int angle = (int) CT::getAngle(clickPos, menuPos);
    int upper_end = 65;
    int bottom_end = upper_end - 70 - ((int) (_menuEntries->size() - 1) * 60);
    if (bottom_end < 0)
        bottom_end += 360;
    bool assertAngle =
            bottom_end > 90 ? angle >= bottom_end || angle <= upper_end : angle >= bottom_end && angle <= upper_end;
    return assertAngle && assertDistanceUpper && assertDistanceBottom;
}


void FloatingMenu::Render() {
    if (dialog) {
        Point renderPos = CT::getPosOnScreen(_position);
        int size = getSize();
        Rect dst = {renderPos.x - size / 2, renderPos.y - size / 2, size, size};
        Rect src = {0, 0, 192, 192};
        // 45 - 85 = 40  from middle position is Button starting at 30 degree going -60
        // Center of Symbol will be  from center size = 192
        // 30′ and 65/192*size should be center of first Symbol
        float distance = 70.0f / 192.0f * (float) size;
        int direction = 30;
        for (int i = 0; i < (int) _menuEntries->size(); i++) {
            rh->texture(_menuTexture, &dst, direction, &src);

            // render center Pos
            int symbolRadiant = (int) (35.f / 192.0f * (float) size);
            Rect center = {1, 1, symbolRadiant, symbolRadiant};
            float angle = (float) direction / 180.0f * (float) M_PI;
            center.x = renderPos.x + (int) (sin(angle) * distance) - symbolRadiant / 2;
            center.y = renderPos.y - (int) (cos(angle) * distance) - symbolRadiant / 2;
            rh->symbol(&center, _menuEntries->at(i));
            direction = (direction + 300) % 360;
        }
    }
}

void FloatingMenu::Update() {
    if (dialog) {
        if (_mbRightDown) {
            offset = offset - _clickRel;
            _clickRel = {};
        }
        // update "Viewport" / Zoom in or Out
        if (_mouseWheel) {
            Game::zoomScreen(_wheelEvent);
            _mouseWheel = false;
        }
        if (_mbLeftDown) {
            if (!onMenu(_clickPos)) {
                SDL_PushEvent(&_lastEvent);
                releaseFocus();
            } else {
                // we need to further investigate if entry is selected
                Point renderPos = CT::getPosOnScreen(_position);
                int size = getSize();
                // 45 - 85 = 40  from middle position is Button starting at 30 degree going -60
                // Center of Symbol will be  from center size = 192
                // 30′ and 65/192*size should be center of first Symbol
                float distance = 70.0f / 192.0f * (float) size;
                float symbolRadiant = 20.f / 192.0f * (float) size;
                int direction = 30;
                Point center{};
                for (int i = 0; i < (int) _menuEntries->size(); i++) {
                    float angle = (float) direction / 180.0f * (float) M_PI;
                    center.x = renderPos.x + (int) (sin(angle) * distance);
                    center.y = renderPos.y - (int) (cos(angle) * distance);
                    direction = (direction + 300) % 360;
                    if (onSymbol(_clickPos, center, symbolRadiant)) {
                        if (_menuEntries->at(i)._status == Status_Active) {
                            releaseFocus();
                            _selectedEntry = _menuEntries->at(i)._menuEntry;
                        }
                    }
                }
            }
        }
        for (MenuEntry &entry: *_menuEntries) {
            if (entry._status != Status_Disabled) {
                if (tdGlobals->_pl._creditPoints < entry._costs)
                    entry._status = Status_NotEnoughMoney;
                else
                    entry._status = Status_Active;
            }
        }
    }
}

bool FloatingMenu::isDone() {
    return (_selectedEntry != -1) && (!dialog);
}

FPoint FloatingMenu::getPos() {
    return _position;
}

MenuEntries FloatingMenu::getSelectedEntry() {
    if (!isDone()) {
        cerr << "no selection done" << endl;
        return MenuEntries::MenuEntry_Error;
    } else {
        return static_cast<MenuEntries>(_selectedEntry);
    }
}

int FloatingMenu::getSize() {
    int size = (int) ((float) windowSize.x * 0.15f) / 64 * scale;
    if (size < 150)
        size = 150;
    return size;
}

void FloatingMenu::reset() {
    dialog = false;
    _selectedEntry = -1;
    _mbLeftDown = false;
    _mouseWheel = false;
    _mbRightDown = false;

}

FloatingMenu::FloatingMenu(Vector<MenuEntry> *menuEntriesInfos, FPoint pos) {
    set(menuEntriesInfos, pos);
}

void FloatingMenu::set(Vector<MenuEntry> *menuEntriesInfos, FPoint pos) {
    _menuTexture = t_cache->get(BasePath "asset/graphic/td/floatingMenu.png");
    setEntries(menuEntriesInfos);
    setPosition(pos);
}

void FloatingMenu::setEntries(Vector<MenuEntry> *menuEntriesInfos) {
    _menuEntries = menuEntriesInfos;
    if (_menuEntries->size() > 6)
        cerr << "Max six entries in menu possible" << endl;
}

void FloatingMenu::setPosition(FPoint p) {
    _position = p;
}

FloatingMenu::~FloatingMenu() = default;

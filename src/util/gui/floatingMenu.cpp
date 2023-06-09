//
// Created by dex on 6/9/23.
//
#include "../../recthelper.h"
#include "../../gamebase.h"
#include "../../tdUtil/map.h"
#include "floatingMenu.h"

void FloatingMenu::Input() {
    SDL_Event event;
    _lastEvent = event;
    while (SDL_PollEvent(&event)) {
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
                _wheelDiff = event.wheel.y;
                break;
        }
    }
}

bool FloatingMenu::onSymbol(Point click, Point symbol, float symbolRadiant) {
    return symbolRadiant * symbolRadiant >= pow(click.x - symbol.x, 2) + pow(click.y - symbol.y, 2);
}


bool FloatingMenu::onMenu(Point clickPos) const {
    Point menuPos = CT::getPosOnScreen(_position);
    float size = (float) getSize() * 0.5f;
    return size * size >= pow(menuPos.x - clickPos.x, 2) + pow(menuPos.y - clickPos.y, 2);
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
        for (int i = 0; i < _menuEntries->size() || i == 6; i++) {
            rh->texture(_menuTexture, &dst, direction, &src);

            // render center Pos
            Rect center = {1, 1, 5, 5,};
            float angle = (float) direction / 180.0f * (float) M_PI;
            center.x = renderPos.x + (int) (sin(angle) * distance);
            center.y = renderPos.y - (int) (cos(angle) * distance);
            rh->fillRect(&center, BLACK);
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
        if (_wheelDiff != 0) {
            Point cursor{};
            SDL_GetMouseState(&cursor.x, &cursor.y);
            if (_wheelDiff / abs(_wheelDiff) < 1) {// zoom out
                scale = (int) (scale * 0.8);
            } else {                                     // zoom in
                scale = (int) (scale * (1 / 0.8));
                offset.y += 2 * _wheelDiff / abs(_wheelDiff) * pMap->_height / 2;
                offset.x += 2 * _wheelDiff / abs(_wheelDiff) * pMap->_width / 2;
            }
            _wheelDiff = 0;
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
                    for (int i = 0; i < _menuEntries->size() || i == 6; i++) {
                        // render center Pos
                        float angle = (float) direction / 180.0f * (float) M_PI;
                        center.x = renderPos.x + (int) (sin(angle) * distance);
                        center.y = renderPos.y - (int) (cos(angle) * distance);
                        direction = (direction + 300) % 360;
                        if (onSymbol(_clickPos, center, symbolRadiant)) {
                            cout << "Symbol " << i << " clicked!" << endl;
                            releaseFocus();
                            _selectedEntry = _menuEntries->at(i);
                        }
                    }
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
    _wheelDiff = 0;
    _mbRightDown = false;

}

FloatingMenu::FloatingMenu(Vector<MenuEntries> *menuEntries, FPoint pos) {
    set(menuEntries, pos);
}

void FloatingMenu::set(Vector<MenuEntries> *menuEntries, FPoint pos) {
    _menuTexture = t_cache->get(BasePath "asset/graphic/td/floatingMenu.png");
    setEntries(menuEntries);
    setPosition(pos);
}

void FloatingMenu::setEntries(Vector<MenuEntries> *menuEntries) {
    _menuEntries = menuEntries;
    if (_menuEntries->size() > 6)
        cerr << "Max six entries in menu possible" << endl;
}

void FloatingMenu::setPosition(FPoint p) {
    _position = p;
}





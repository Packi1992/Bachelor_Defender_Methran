//
// Created by banoodle on 13.06.23.
//
#include "linkEstablisher.h"
#include "../../td/tower/linkedListTower.h"
#include "../../recthelper.h"

void LinkEstablisher::set(LinkedListTower *srcTower, bool first) {
    _tower = srcTower;
    _first = first;

}

void LinkEstablisher::Input() {
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
            case SDL_KEYDOWN:
                if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
                    releaseFocus();
                }
        }
    }
}

void LinkEstablisher::Render() {
    if(dialog){
        Point cursor;
        SDL_GetMouseState(&cursor.x,&cursor.y);
        Rect dst = {cursor.x, cursor.y, scale, scale};
        rh->tile(&dst, TdTileHandler::getTowerSrcRect(Base));
        rh->tile(&dst, ((int) 0) % 360, TdTileHandler::getTowerSrcRect(Tower_LinkedList, 0));
    }
}

void LinkEstablisher::Update() {
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
            Point click = CT::getPosOnScreen(_clickPos);
        }
    }
}

bool LinkEstablisher::isDone() const {
    return false;
}

void LinkEstablisher::handleEvent(Event event) {

}

void LinkEstablisher::acceptInput() {

}


//
// Created by banoodle on 13.06.23.
//
#include "linkEstablisher.h"
#include "../../td/tower/linkedListTower.h"
#include "../../recthelper.h"
#include "../../gamebase.h"
#include "../../tdUtil/map.h"
#include "../../td/testtd.h"

void LinkEstablisher::set(LinkedListTower *srcTower, bool first) {
    _tower = srcTower;
    _first = first;
    calcLinkPosition();

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
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    _tower->removeFromMap();
                    _tower->setDead(true);
                    tdGlobals->_pl._creditPoints += _tower->getCosts();
                    releaseFocus();
                }
        }
    }
}

void LinkEstablisher::Render() {
    if (dialog) {
        // draw tower on dest pos
        if(_cursorRenderPos.x >= 0 && _cursorRenderPos.x < pMap->_width && _cursorRenderPos.y >= 0 && _cursorRenderPos.y < pMap->_height) {
            rh->tile(&_towerLinkRect, TdTileHandler::getTowerSrcRect(Tower_LinkedListBase));
            rh->tile(&_towerLinkRect, ((int) 0) % 360, TdTileHandler::getTowerSrcRect(Tower_LinkedList, 0));
        }
        t_color markerColor = RED;
        if (_isLinkInRange) {
            markerColor = GREEN;
        }

        FPoint range{0, 0};
        for (int angle = 0; angle < 360; angle += 10) {
            float angleF = (float) angle / 180.0f * (float) M_PI;
            range.x = (float) _tower->getPos().x + sin(angleF) * (float) _tower->getRange();
            range.y = (float) _tower->getPos().y + cos(angleF) * (float) _tower->getRange();
            if(range.x>0 && range.x < pMap->_width && range.y > 0 && range.y < pMap->_height){
                Point range2 = CT::getPosOnScreen(range);
                Rect dstMarker = {range2.x, range2.y, 5, 5};
                rh->fillRect(&dstMarker, markerColor);
            }
        }
        if (_isLinkInRange) {
            Point towerCenter = CT::getPosOnScreen(_tower->getPos());
            Point newTowerCenter = CT::getPosOnScreen(_cursorCenterPos);
            rh->line(towerCenter,newTowerCenter,GREEN);
        }
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
            if(_isLinkInRange){
                std::shared_ptr<class Tower> tower = std::make_shared<LinkedListTower>(_cursorRenderPos);
                tdGlobals->_towers.push_back(tower);
                std::shared_ptr<LinkedListTower> lTower = std::dynamic_pointer_cast<LinkedListTower>(tdGlobals->_towers.at(tdGlobals->_towers.size()-1));
                lTower->setLink(_tower);
                releaseFocus();
            }
        }
        calcLinkPosition();
    }
}

bool LinkEstablisher::isDone() const {
    return false;
}

void LinkEstablisher::handleEvent(Event event) {

}

void LinkEstablisher::acceptInput() {

}

void LinkEstablisher::calcLinkPosition() {
    // get mouse pos
    SDL_GetMouseState(&_cursorRenderPos.x, &_cursorRenderPos.y);
    _cursorCenterPos = CT::getTileCenterInGame(_cursorRenderPos);
    _cursorRenderPos = CT::getTileInGame(_cursorRenderPos);
    // check if tower link is in range
    FRect destRect = {_cursorCenterPos.x - 0.25f, _cursorCenterPos.y - 0.25f, 0.5f, 0.5f};
    _isLinkInRange = _tower->inRange(destRect);
    Point dst = CT::getPosOnScreen(_cursorRenderPos);
    _towerLinkRect = {dst.x,dst.y,scale,scale};

}


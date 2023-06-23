//
// Created by banoodle on 13.06.23.
//

#ifndef SDL_BACHELORDEFENDER_LINKESTABLISHER_H
#define SDL_BACHELORDEFENDER_LINKESTABLISHER_H
#include "gui.h"
#include "../gamebase.h"
class LinkedListTower;
class LinkEstablisher: public Gui{
public:
    void set(LinkedListTower *srcTower, bool first);
    void Input() override;
    void Render() override;
    void Update() override;
    [[nodiscard]] static bool isDone() ;

    void releaseFocus(bool continueRender) override;
    void handleEvent(Event event);
    void acceptInput();
private:
    LinkedListTower *_last{};
    LinkedListTower *_next{};
    bool _first=false;
    // zoom handling
    bool _mouseWheel = false;
    SDL_Event _wheelEvent{};
    Point _clickRel{};
    bool _mbRightDown = false;
    bool _mbLeftDown = false;
    bool _escape = false;

    // link calculations
    void calcLinkPosition();

    Point _cursorRenderPos{};
    Rect _towerLinkRect{};
    Rect _towerNextLinkRect{};
    FPoint _cursorCenterPos{};
    bool _isLinkInRange=false;
    bool _isLinkNextInRange=false;
    bool _blockingPath = false;




};
#endif //SDL_BACHELORDEFENDER_LINKESTABLISHER_H

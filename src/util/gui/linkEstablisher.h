//
// Created by banoodle on 13.06.23.
//

#ifndef SDL_BACHELORDEFENDER_LINKESTABLISHER_H
#define SDL_BACHELORDEFENDER_LINKESTABLISHER_H
#include "gui.h"
#include "../../gamebase.h"
class LinkedListTower;
class LinkEstablisher: public Gui{
public:
    void set(LinkedListTower *srcTower, bool first);
    void Input() override;
    void Render() override;
    void Update() override;
    [[nodiscard]] bool isDone() const;

    void handleEvent(Event event);
    void acceptInput();
private:
    LinkedListTower *_tower{};
    bool _first=false;
    // zoom handling
    bool _mouseWheel = false;
    SDL_Event _wheelEvent{};
    static int getSize();
    FPoint _position{};
    Point _clickPos{};
    Point _clickRel{};
    bool _mbRightDown = false;
    bool _mbLeftDown = false;
    bool _escape = false;
};
#endif //SDL_BACHELORDEFENDER_LINKESTABLISHER_H

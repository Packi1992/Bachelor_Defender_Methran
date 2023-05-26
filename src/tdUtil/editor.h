//
// Created by banoodle on 23.05.23.
//

#ifndef SDL_BACHELORDEFENDER_EDITOR_H
#define SDL_BACHELORDEFENDER_EDITOR_H

#include "../gamebase.h"
#include "../util/TextureCache.h"
#include "tdTileHandler.h"
#include "map.h"
#include "../util/Button.h"
#include "../util/gui/selector.h"
#include "../util/nameInputDialog.h"

class Editor: public GameState{
protected:
    TdTileHandler::MapObjects selected=TdTileHandler::Empty;
    Texture *t_tile= nullptr;
    Button btn_load;
    Button btn_save;
    Button btn_change_size;
    Selector mapSelector;
    Gui *focus= nullptr;
    Map map;
    Point offset={};
    int rainbowColor=0;
    bool isLabelActive=false;
    int labelTimer=0;
    TdTileHandler::MapObjects labelObject;
    Point labelPos={};
    Rect Toolbox = {};
    bool mbDown=false;
    bool mouseScroll=false;
    void handleSelection(Event event);
    void save();
    void load();
public:

    // ctor
    using GameState::GameState;

    void Init() override;
    void UnInit() override;

    void Events( const u32 frame, const u32 totalMSec, const float deltaT ) override;
    void Update( const u32 frame, const u32 totalMSec, const float deltaT ) override;
    void Render( const u32 frame, const u32 totalMSec, const float deltaT ) override;

    void MouseDown(SDL_Event event);

    void MouseMotion(SDL_Event event);

    void keyDown(SDL_Event event);

    void MouseWheel(SDL_Event event);
};
#endif //SDL_BACHELORDEFENDER_EDITOR_H

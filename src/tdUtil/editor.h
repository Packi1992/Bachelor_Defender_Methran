//
// Created by banoodle on 23.05.23.
//

#ifndef SDL_BACHELORDEFENDER_EDITOR_H
#define SDL_BACHELORDEFENDER_EDITOR_H

class Editor;
#include "../gamebase.h"
#include "../util/TextureCache.h"
#include "tdTileHandler.h"
#include "map.h"
#include "../util/gui/Button.h"
#include "../util/gui/selectorDialog.h"
#include "../util/gui/inputDialog.h"

class Editor: public GameState{
protected:
    Texture *t_tileMap= nullptr;
    Map map;
    bool mbDown=false;
    bool mouseScroll=false;

    // label hint
    bool isLabelActive=false;
    int labelTimer=0;
    Point labelPos={};
    MapObjects labelObject;

    // window handling
    Gui *focus= nullptr;
    SelectorDialog mapSelector;
    InputDialog mapNameInput;

    // buttons
    Button btn_load;
    Button btn_save;
    Button btn_path;
    bool showPath=false;
    //Button btn_change_size;
    int rainbowColor=0;

    // Tile SelectorDialog
    Rect Toolbox = {};
    MapObjects selected=TdTileHandler::Empty;
    void handleSelection(Event event);
public:

    // ctor
    using GameState::GameState;

    void Init() override;
    void UnInit() override;

    void Update( const u32 frame, const u32 totalMSec, const float deltaT ) override;
    void Render( const u32 frame, const u32 totalMSec, const float deltaT ) override;

    // event handling
    void Events( const u32 frame, const u32 totalMSec, const float deltaT ) override;
    void MouseDown(SDL_Event event);
    void MouseMotion(SDL_Event event);
    void keyDown(SDL_Event event);
    void MouseWheel(SDL_Event event);
};
#endif //SDL_BACHELORDEFENDER_EDITOR_H

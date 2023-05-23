//
// Created by banoodle on 23.05.23.
//

#ifndef SDL_BACHELORDEFENDER_EDITOR_H
#define SDL_BACHELORDEFENDER_EDITOR_H

#include "../../gamebase.h"
#include "../../util/TextureCache.h"
#include "tdTileHandler.h"
#include "map.h"

class Editor: public GameState{
protected:
    TdTileHandler::MapObjects selected=TdTileHandler::Empty;
    TextureCache *tCache = nullptr;
    Texture *t_tile= nullptr;
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
public:

    // ctor
    using GameState::GameState;

    void Init() override;
    void UnInit() override;

    void Events( const u32 frame, const u32 totalMSec, const float deltaT ) override;
    void Update( const u32 frame, const u32 totalMSec, const float deltaT ) override;
    void Render( const u32 frame, const u32 totalMSec, const float deltaT ) override;

};
#endif //SDL_BACHELORDEFENDER_EDITOR_H

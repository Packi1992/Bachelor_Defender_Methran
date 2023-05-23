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
    TextureCache *tcache = nullptr;
    Map map;
    Point offset={};
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

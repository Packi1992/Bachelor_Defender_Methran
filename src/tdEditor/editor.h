//
// Created by banoodle on 23.05.23.
//

#ifndef SDL_BACHELORDEFENDER_EDITOR_H
#define SDL_BACHELORDEFENDER_EDITOR_H

class Editor;
#include "../util/gamebase.h"
#include "../util/TextureCache.h"
#include "../tdUtil/tdTileHandler.h"
#include "../tdUtil/map.h"
#include "../util/gui/Button.h"
#include "../util/gui/selectorDialog.h"
#include "../util/gui/inputDialog.h"
#include "../util/gui/sizeDialog.h"
#include "../util/dataHandler.h"
#include "../util/gui/playerSettings.h"

class Editor: public GameState{
protected:
    Texture *t_tileMap= nullptr;
    Map map{};
    WaveHandler waves{};
    Player player{};

    // label hint
    bool isLabelActive=false;
    int labelTimer=0;
    Point labelPos={};
    MapObjects labelObject{};

    // window handling
    Gui *focus= nullptr;
    SelectorDialog mapSelector;
    InputDialog mapNameInput;
    SizeDialog resizeMap;
    PlayerSettings settingsDialog;

    // buttons
    Button btn_load;
    Button btn_save;
    Button btn_change_size;
    Button btn_path;
    Button btn_playerSettings;
    bool showPath=false;

    int rainbowColor=0;

    // Tile SelectorDialog
    Rect Toolbox = {};
    MapObjects selected=Empty;
    void handleSelection(Event event);

    // zooming
    bool _mouseWheel = false;
    SDL_Event _wheelEvent{};
    // scrolling
    bool _mouseMotion = false;
    SDL_Event _motionEvent{};
    bool _mbLeft=false;
    bool _mbRight=false;
public:

    // ctor
    using GameState::GameState;
    explicit Editor(Game &game);

    void Init() override;
    void UnInit() override;

    void Update() override;
    void Render() override;

    // event handling
    void Events() override;
    void MouseDown(SDL_Event event);
    void MouseMotion(SDL_Event event);
    void keyDown(SDL_Event event);
};
#endif //SDL_BACHELORDEFENDER_EDITOR_H

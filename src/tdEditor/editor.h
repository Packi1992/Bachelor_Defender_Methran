//
// Created by banoodle on 23.05.23.
//

#ifndef SDL_BACHELORDEFENDER_EDITOR_H
#define SDL_BACHELORDEFENDER_EDITOR_H

#include "../util/gamebase.h"
#include "../tdUtil/map.h"
#include "../tdUtil/player.h"
#include "../tdUtil/waveHandler.h"
#include "../util/gui/Button.h"
#include "../util/gui/selectorDialog.h"
#include "../util/gui/inputDialog.h"
#include "../util/gui/sizeDialog.h"
#include "../util/gui/playerSettings.h"

class Editor: public GameState{
protected:
    Map map{};
    string mapName = "tmp";
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
    enum Buttons{
        btn_Load,
        btn_save,
        btn_waveSettings,
        btn_startGame,
        btn_changeSize,
        btn_playerSettings,
        btn_pathFinding,
    };
    void updateButtonPos();
    Vector<Button> _buttons;
    int _fontSize=18;
    bool showPath=false;
    int rainbowColor=0;

    // Tile SelectorDialog
    Rect Toolbox = {};
    void RenderToolbox();
    MapObjects selected=Empty;

    // zooming
    bool _mouseWheel = false;
    SDL_Event _wheelEvent{};

    // scrolling
    bool _mouseMotion = false;
    SDL_Event _motionEvent{};

    Point mousePos{};
    bool _mbLeft=false;
    bool _mbRight=false;
    void MouseClickLeft();
    void MouseClickRight();
    void MouseMotion(SDL_Event event);
    void handleSelection();
    void keyDown(SDL_Event event);
public:

    using GameState::GameState;
    explicit Editor(Game &game);

    void Init() override;
    void UnInit() override;

    void Update() override;
    void Render() override;

    void Events() override;
};
#endif //SDL_BACHELORDEFENDER_EDITOR_H

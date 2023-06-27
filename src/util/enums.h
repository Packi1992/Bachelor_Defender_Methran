//
// Created by banoodle on 09.06.23.
//

#ifndef SDL_BACHELORDEFENDER_ENUMS_H
#define SDL_BACHELORDEFENDER_ENUMS_H

enum MapObjects{
    Empty,
    Start,
    Goal,
    Table,
    Chair,
    Tower,
    OutOfBounds,
    Map_Disabled,
    Plain_Wall,
    Window_Wall,
    Side_Wall,
    Door_Wall
};

enum EnemyType{
    Ordinary,
    Fast,
    Silly,
    Strong,
    Boss_Frohle_Poehlich,
    Boss_Drueberbolz,
    Boy,
    Girl,
};
enum ProjectileType{
    DISABLED,
    ARROW,
    ARROW_FULLRECT,
    BULLET,
    LINK,
    BASEEXPLOSION,
    FFIRE,
    BOOMERANG,
    HASHBOMB,
    STRINGPROJECTILE,
};

enum AnimType{
    Gameover,
    Gameover_Top_Left,
    Gameover_Top_Right,
    Gameover_Bottom_Left,
    Gameover_Bottom_Right,
    Bell
};

enum TowerType{
    Base,
    Pointer,
    Tower_LinkedList,
    Tower_LinkedListBase,
    RecursivBase,
    Tower_Boomerang,
    Hashcanon,
    Hashcanon_Dir,
    StringTower,
};

//  specific Colors to make things easier regarding drawing colors
enum t_color {
    EMPTY,
    BLACK,
    WHITE,
    BTN_COLOR,
    BTN_HIGHLIGHTED,
    BTN_INACTIVE,
    MAP_GRID,
    EDITOR_UI_BG,
    BG,
    YELLOW,
    RED,
    GREEN,
    BLUE,
};

enum musicType {
    MusicMainMenu,
    MusicEditor,
    MusicGame,
    MusicError,
    MusicDisabled
};

enum soundType {
    SoundPointerTower,
    SoundHashCanon,
    SoundLinkedListTower,
    SoundRecursivTower,
    SoundStringTower,
    SoundEnemyOrdinary,
    SoundFrolePoehlich,
    SoundDrueberbolz,
    SoundArrowHit,
    SoundBoomerangHit,
    SoundLinkHit,
    SoundStringProjectileHit,
    SoundFire,
    SoundHashBombHit,
    SoundError,
    SoundDisabled,
};

// Menu Entries for displaying Icons in FloatingMenu
enum MenuEntries{
    MenuEntry_DEFAULT,
    MenuEntry_POINTER,
    MenuEntry_BOOMERANG,
    MenuEntry_LinkedList,
    MenuEntry_HASHCANON,
    MenuEntry_STRINGTOWER,
    MenuEntry_Error,
    MenuEntry_Disabled,
    MenuEntry_Sell,
    MenuEntry_Upgrade,
    MenuEntry_AddLink,
};

enum Status{
    Status_Disabled,
    Status_NotEnoughMoney,
    Status_Active,
    Status_EnemyBlocking,
};

enum Direction{
    TOP = 0,
    RIGHT = 90,
    BOTTOM = 180,
    LEFT = 270,
};

enum GameStates{
    GS_MainMenu,
    GS_TD,
    GS_Moorhuhn,
    GS_Settings,
    GS_Editor,
    GS_WorldMap,
    GS_Close,
};

enum GameEvents{
    GE_Spawn,
    GE_Message,
};
#endif //SDL_BACHELORDEFENDER_ENUMS_H
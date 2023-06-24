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
    STRINGPROJECTILE
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
    SoundTowerPointer,
    SoundEnemyOrdinary,
    SoundArrowFire,
    SoundArrowHit,
    SoundBullet,
    SoundBoomerangFire,
    SoundFFire,
    SoundBaseExplosion,
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
};

enum Direction{
    TOP,
    RIGHT,
    BOTTOM,
    LEFT
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
#endif //SDL_BACHELORDEFENDER_ENUMS_H
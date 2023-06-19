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
    Tower,
    Chair,
    OutOfBounds,
    Map_Disabled,
};

enum EnemyType{
    Ordinary,
    Fast,
    Silly,
    Strong,
    Boss,
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
#endif //SDL_BACHELORDEFENDER_ENUMS_H
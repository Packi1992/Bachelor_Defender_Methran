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
    BULLET,
    BASEEXPLOSION,
    FFIRE,
};

enum TowerType{
    Base,
    Pointer,
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
    SoundFFire,
    SoundBaseExplosion,
    SoundError,
    SoundDisabled,
};

// Menu Entries for displaying Icons in FloatingMenu
enum MenuEntries{
    MenuEntry_DEFAULT,
    MenuEntry_POINTER,
    MenuEntry_Error,
    MenuEntry_Disabled,
};

#endif //SDL_BACHELORDEFENDER_ENUMS_H
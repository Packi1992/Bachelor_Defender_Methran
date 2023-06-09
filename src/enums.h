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
};
#endif //SDL_BACHELORDEFENDER_ENUMS_H

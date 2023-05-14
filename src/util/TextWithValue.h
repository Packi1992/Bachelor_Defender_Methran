//
// Created by banoodle on 24.04.23.
//

#ifndef BOULDERDASH_TEXTWITHVALUE_H
#define BOULDERDASH_TEXTWITHVALUE_H


#include "../Global.h"


class TextWithValue {
public:
    void set(Global *pGlobal, const std::string& Text,const int *value,
             SDL_Point pos, int textSize, Color::colors TextColor);

    void draw();

    ~TextWithValue();

    void center();

private:
    // base
    Global *pg = nullptr;
    int size{};
    Color::colors color{};
    bool centered = false;

    // label
    char text[50]{};
    SDL_Rect rectLabel{};
    SDL_Texture *texLabel = nullptr;

    // value
    SDL_Rect rectValue{};
    SDL_Texture *texValue = nullptr;
    const int *exValue = nullptr;
    int value{};

    void update();

    int getWidth() const;

    int getHeight() const;
};


#endif //BOULDERDASH_TEXTWITHVALUE_H


#ifndef BBD_TEXTWITHVALUE_H
#define BBD_TEXTWITHVALUE_H


#include <string>
#include "../gamebase.h"


class TextWithValue {
public:
    void set(Game *game, const std::string& Text,const int *value,
             SDL_Point pos, int textSize, Color TextColor);

    void draw();

    ~TextWithValue();

    void center();

private:
    // base
    Game *pGame = nullptr;
    int size{};
    Color color{};
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


#endif //BBD_TEXTWITHVALUE_H

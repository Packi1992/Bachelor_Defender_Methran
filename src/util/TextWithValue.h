
#ifndef BBD_TEXTWITHVALUE_H
#define BBD_TEXTWITHVALUE_H


#include <string>
#include "../gamebase.h"


class TextWithValue {
public:
    void set(const string& Text,const int *value,
             Point pos, int textSize, t_color TextColor);

    void draw();

    ~TextWithValue();

    void center();

private:
    // base
    Game *pGame = nullptr;
    int size{};
    t_color color{};
    bool centered = false;

    // label
    char text[50]{};
    Rect rectLabel{};
    Texture *texLabel = nullptr;

    // value
    Rect rectValue{};
    Texture *texValue = nullptr;
    const int *exValue = nullptr;
    int value{};

    void update();

    int getWidth() const;

    int getHeight() const;
};


#endif //BBD_TEXTWITHVALUE_H

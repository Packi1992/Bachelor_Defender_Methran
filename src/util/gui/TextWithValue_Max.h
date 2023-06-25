
#ifndef BBD_TEXTWITHVALUE_H
#define BBD_TEXTWITHVALUE_H

#include <string>
#include "../gamebase.h"

class TextWithValue_Max {
public:
    void set(const string &Text, const int *value, const int *maxValue,
             Point pos, int textSize, t_color TextColor);

    void Render();
    void Update();

    ~TextWithValue_Max();

    void center();

private:
    int _size{};
    t_color _color{};
    bool _centered = false;

    // label
    char _text[50]{};
    Rect _rectLabel{};
    Texture *_texLabel = nullptr;

    // value
    Rect _rectValue{};
    Texture *_texValue = nullptr;
    const int *_exValue = nullptr;
    int _value{};

    // seperator
    Rect _rectSep{};
    Texture *_texSep = nullptr;

    // value
    Rect _rectValueMax{};
    Texture *_texValueMax = nullptr;
    const int *_exValueMax = nullptr;
    int _valueMax{};

    void updateValue();
    void updateValueMax();
    void updatePos();

    int getWidth() const;
    int getHeight() const;
};


#endif //BBD_TEXTWITHVALUE_H

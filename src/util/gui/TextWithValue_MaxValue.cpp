//
// Created by banoodle on 24.04.23.
//

#include "TextWithValue_Max.h"

void TextWithValue_Max::set(const string &Text, const int *valueField, const int *maxValue,
                            Point pos, int textSize, t_color TextColor) {
    strcpy_s(_text, Text.c_str());
    _exValue = valueField;
    _exValueMax = maxValue;
    _size = textSize;
    _color = TextColor;

    // generate Label
    _rectLabel = {pos.x, pos.y, 0, 0};
    _texLabel = t_cache->getText(_text, _size, &_rectLabel, _color);

    // generate first Value
    _value = *_exValue;
    _rectValue = {_rectLabel.x + _rectLabel.w + 10, pos.y, 0, 0};
    _texValue = t_cache->getNumber(_value, _size, _color, &_rectValue);

    // generate Seperator
    _rectSep = {_rectValue.x + _rectValue.w + 2, pos.y, 0, 0};
    _texSep = t_cache->getText(_text, _size, &_rectSep, _color);

    // generate MaxValue
    _valueMax = *maxValue;
    _rectValueMax = {_rectSep.x + _rectSep.w + 2, pos.y, 0, 0};
    _texValueMax = t_cache->getNumber(_valueMax, _size, _color, &_rectValueMax);

    updatePos();
}

TextWithValue_Max::~TextWithValue_Max() {
    if (_texLabel != nullptr)
        SDL_DestroyTexture(_texLabel);
    if (_texValue != nullptr)
        SDL_DestroyTexture(_texValue);
    if (_texValueMax != nullptr)
        SDL_DestroyTexture(_texValueMax);
    if (_texSep != nullptr)
        SDL_DestroyTexture(_texSep);
}

void TextWithValue_Max::Render() {
    rh->texture(_texLabel, &_rectLabel);
    rh->texture(_texValue, &_rectValue);
    rh->texture(_texSep, &_rectLabel);
    rh->texture(_texValueMax, &_rectValue);
}

void TextWithValue_Max::Update() {
    if (_value != *_exValue)
        updateValue();
    if (_valueMax != *_exValueMax)
        updateValueMax();
}

void TextWithValue_Max::center() {
    _centered = true;
}

int TextWithValue_Max::getWidth() const {
    return _rectLabel.w + 10 + _rectValue.w + _rectSep.w + 4 + _rectValueMax.w;
}

int TextWithValue_Max::getHeight() const {
    return _rectLabel.h;
}

void TextWithValue_Max::updateValueMax() {
    _value = *_exValue;
    if (_texValue != nullptr)
        SDL_DestroyTexture(_texValue);
    _texValue = t_cache->getNumber(_value, _size, _color, &_rectValue);
    updatePos();
}

void TextWithValue_Max::updateValue() {
    _valueMax = *_exValueMax;
    if (_texValue != nullptr)
        SDL_DestroyTexture(_texValueMax);
    _texValue = t_cache->getNumber(_valueMax, _size, _color, &_rectValue);
    updatePos();
}

void TextWithValue_Max::updatePos() {
    if (_centered) {
        int width = getWidth();
        int x = windowSize.x / 2 - width / 2;
        _rectLabel.x = x;
        _rectValue.x = _rectLabel.w + x + 10;
    }
    _rectSep.x = _rectValue.x+_rectValue.w+2;
    _rectValueMax.x = _rectSep.x+_rectSep.w+2;
}
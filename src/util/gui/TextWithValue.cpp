//
// Created by banoodle on 24.04.23.
//

#include "TextWithValue.h"

void TextWithValue::set(const string &Text, const int *valueField,
                        Point pos, int textSize, t_color TextColor, bool border_) {
    strncpy(text, Text.c_str(),50);
    exValue = valueField;
    size = textSize;
    color = TextColor;
    // generate Label
    rectLabel = {pos.x, pos.y, 0, 0};
    texLabel = t_cache->getText(text, size, &rectLabel, color);
    rectValue = {rectLabel.x + rectLabel.w + 10, pos.y, 0, 0};
    // generate first Value
    value = *exValue;
    texValue = t_cache->getNumber(value, size, color, &rectValue);
    if (centered) {
        int width = getWidth();
        int x = windowSize.x / 2 - width / 2;
        rectLabel.x = x;
        rectValue.x = rectLabel.w + x + 10;
    }
    this->border = border_;
}

TextWithValue::~TextWithValue() {
    if (texLabel != nullptr)
        SDL_DestroyTexture(texLabel);
    if (texValue != nullptr)
        SDL_DestroyTexture(texValue);
}

void TextWithValue::Render() {
    if (value != *exValue)
        update();
    if (border) {
        rh->blendTexture(texLabel, &rectLabel);
        rh->blendTexture(texValue, &rectValue);
    } else {
        rh->texture(texLabel, &rectLabel);
        rh->texture(texValue, &rectValue);
    }

}

void TextWithValue::update() {
    value = *exValue;
    if (texValue != nullptr)
        SDL_DestroyTexture(texValue);
    texValue = t_cache->getNumber(value, size, color, &rectValue);
    if (centered) {
        int width = getWidth();
        int x = windowSize.x / 2 - width / 2;
        rectLabel.x = x;
        rectValue.x = rectLabel.w + x + 10;
    }
}

void TextWithValue::center() {
    centered = true;
}

int TextWithValue::getWidth() const {
    return rectLabel.w + 10 + rectValue.w;
}

int TextWithValue::getHeight() const {
    return rectLabel.h;
}

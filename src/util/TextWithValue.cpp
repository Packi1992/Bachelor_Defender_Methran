//
// Created by banoodle on 24.04.23.
//

#include "TextWithValue.h"

void TextWithValue::set(Game *game, Renderer *Renderer, const std::string& Text, const int *valueField,
                        SDL_Point pos, int textSize, Color TextColor) {
    this->pRenderer = pRenderer;
    this->pGame= game;
    tCache = TextureCache::getCache(pRenderer);
    strcpy(text,Text.c_str());
    exValue = valueField;
    size = textSize;
    color = TextColor;
    // generate Label
    rectLabel = {pos.x, pos.y, 0, 0};
    texLabel = tCache->getText(text, size, color, &rectLabel);
    rectValue = {rectLabel.x + rectLabel.w + 10, pos.y, 0, 0};
    // generate first Value
    value = *exValue;
    texValue = tCache->getNumber(value, size, color, &rectValue);
    if(centered){
        int width = getWidth();
        int x = game->GetWindowSize().x/2 - width/2;
        rectLabel.x = x;
        rectValue.x = rectLabel.w +x +10;
    }
}

TextWithValue::~TextWithValue() {
    if (texLabel != nullptr)
        SDL_DestroyTexture(texLabel);
    if (texValue != nullptr)
        SDL_DestroyTexture(texValue);
}

void TextWithValue::draw() {
    if(value != *exValue)
        update();
    tCache->render(texLabel,&rectLabel);
    tCache->render(texValue,&rectValue);

}

void TextWithValue::update() {
    value = *exValue;
    if(texValue!= nullptr)
        SDL_DestroyTexture(texValue);
    texValue = tCache->getNumber(value, size, color, &rectValue);
    if(centered){
        int width = getWidth();
        int x = pGame->GetWindowSize().x/2 - width/2;
        rectLabel.x = x;
        rectValue.x = rectLabel.w +x +10;
    }
}

void TextWithValue::center() {
    centered = true;
}

int TextWithValue::getWidth() const {
    return rectLabel.w+10+rectValue.w;
}

int TextWithValue::getHeight() const {
    return rectLabel.h;
}
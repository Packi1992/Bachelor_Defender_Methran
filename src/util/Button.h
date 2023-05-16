//
// Created by banoodle on 15.04.23.
//

#ifndef JUMPNRUN_BUTTON_H
#define JUMPNRUN_BUTTON_H

#include <string>
#include <SDL2/SDL.h>
#include "../global.h"
#include "TextureCache.h"

class Button {
public:
    Button(){};

    Button(const Button &b);

    void draw(bool highlighted=false);

    bool clicked(SDL_Event e);

    ~Button();

    void entered(SDL_Event e);
    std::string getText();
    int getX();
    void set(Renderer *render, const std::string &label, int size,
             SDL_Rect rect, SDL_Color btn_color={150,150,150,255});
    void setSize(SDL_Rect rect);
    void setHighlightedColor(SDL_Color high_color={0,0,0,255});
private:
    Renderer *render = nullptr;
    TextureCache *tCache = nullptr;
    // button background rect
    SDL_Rect rect{};
    // text rect
    SDL_Rect tRect{};
    SDL_Texture *text = nullptr;
    SDL_Color buttonColor{};
    SDL_Color highlightedColor{};
    SDL_Color drawColor{};
    int size{};
    char textArr[50]{};
};

#endif //JUMPNRUN_BUTTON_H
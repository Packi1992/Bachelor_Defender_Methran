//
// Created by banoodle on 15.04.23.
//

#include "Button.h"

void Button::draw(bool highlighted) {
    if(highlighted)
        tCache->setRenderColor(highlightedColor);
    else
        tCache->setRenderColor(drawColor);
    SDL_RenderFillRect(render, &rect);
    tCache->setRenderColor(BLACK);
    SDL_RenderDrawRect(render, &rect);

    SDL_RenderCopy(render, text, nullptr, &tRect);
}

bool Button::clicked(SDL_Event e) {
    bool xAxis = e.motion.x > this->rect.x && e.motion.x < this->rect.x + this->rect.w;
    bool yAxis = e.motion.y > this->rect.y && e.motion.y < this->rect.y + this->rect.h;
    if(xAxis&&yAxis){
        std::cout << "button " << textArr << " clicked" << std::endl;
    }
    return xAxis && yAxis;
}

Button::~Button() {
    if(text != nullptr)
        SDL_DestroyTexture(text);
}

void Button::entered(SDL_Event e) {
    bool xAxis = this->rect.x <= e.motion.x && this->rect.x + this->rect.w >= e.motion.x;
    bool yAxis = this->rect.y <= e.motion.y && this->rect.y + this->rect.h >= e.motion.y;
    if (xAxis && yAxis) {
        drawColor = highlightedColor;
    } else {
        drawColor = buttonColor;
    }
}

Button::Button(const Button &b) {
    strcpy(textArr, b.textArr);
    std::cout<< "using Copy Constuctor: " << textArr << std::endl;
    this->render = b.render;
    this->tCache = b.tCache;
    this->size = b.size;
    this->rect = b.rect;

    this->buttonColor = b.buttonColor;
    this->drawColor = b.drawColor;
    setHighlightedColor();
    this->text = tCache->getText(textArr, size, {0, 0, 0, 255});
    SDL_QueryTexture(this->text, nullptr, nullptr, &tRect.w, &tRect.h);

    tRect.x = rect.x + (rect.w - tRect.w) / 2;
    tRect.y = rect.y + (rect.h - tRect.h) / 2;
}

void Button::set(Renderer *renderer, const std::string& label, int nSize, SDL_Rect nRect, Color btnColor) {
    this->render = renderer;
    this->size = nSize;
    this->tCache = TextureCache::getCache(renderer);
    strcpy(textArr, label.c_str());
    this->rect = nRect;
    std::cout << "Button set " << textArr << std::endl;
    this->buttonColor = btnColor;
    setHighlightedColor();
    this->text = tCache->getText(textArr, size, {0, 0, 0, 255});
    SDL_QueryTexture(this->text, nullptr, nullptr, &tRect.w, &tRect.h);

    tRect.x = rect.x + (rect.w - tRect.w) / 2;
    tRect.y = rect.y + (rect.h - tRect.h) / 2;
    drawColor = btnColor;
}

std::string Button::getText() {
    return this->textArr;
}

int Button::getX() {
    return rect.x;
}

void Button::setHighlightedColor(SDL_Color high_color) {
    if(high_color.r==0&&high_color.g==0&&high_color.a==255&&high_color.b==0){
        //define highlighted color depending on btn color
        this->highlightedColor = {((Uint8)(buttonColor.r+20)),
                                  (Uint8)(buttonColor.g+20),
                                  (Uint8)(buttonColor.b+20),255};
        std::cout << "highlighted button color: "<<  highlightedColor.r << ", "<<highlightedColor.g << ", "<<highlightedColor.b<< std::endl;
    }
    else{
        this->highlightedColor = high_color;
    }
}

void Button::setSize(SDL_Rect nRect) {
    this->rect = nRect;
    tRect.x = rect.x + (rect.w - tRect.w) / 2;
    tRect.y = rect.y + (rect.h - tRect.h) / 2;
}


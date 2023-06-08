//
// Created by banoodle on 15.04.23.
//

#include "Button.h"

void Button::draw(bool highlighted) {
    if (highlighted)
        rh->setColor(highlightedColor);
    else
        rh->setColor(drawColor);
    rh->fillRect(&rect);
    rh->rect(&rect,2,BLACK);
    rh->texture(text,&tRect);
}

bool Button::clicked(SDL_Event e) {
    bool xAxis = e.motion.x > this->rect.x && e.motion.x < this->rect.x + this->rect.w;
    bool yAxis = e.motion.y > this->rect.y && e.motion.y < this->rect.y + this->rect.h;
    if (xAxis && yAxis) {
        std::cout << "button " << textArr << " clicked" << std::endl;
    }
    return xAxis && yAxis;
}

Button::~Button() {
    if (text != nullptr)
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
    std::cout << "using Copy Constuctor: " << textArr << std::endl;
    this->size = b.size;
    this->rect = b.rect;

    this->buttonColor = b.buttonColor;
    this->drawColor = b.drawColor;
    this->highlightedColor = b.highlightedColor;
    this->text = t_cache->getText(textArr, size,&tRect);

    tRect.x = rect.x + (rect.w - tRect.w) / 2;
    tRect.y = rect.y + (rect.h - tRect.h) / 2;
}

void Button::set(const string &label, int nSize, Rect nRect, t_color btnColor) {
    this->size = nSize;
    strcpy(textArr, label.c_str());
    this->rect = nRect;
    this->buttonColor = RenderHelper::getColor(btnColor);
    setHighlightedColor(&btnColor);

    this->text = t_cache->getText(textArr, size,&tRect);

    tRect.x = rect.x + (rect.w - tRect.w) / 2;
    tRect.y = rect.y + (rect.h - tRect.h) / 2;
    drawColor = buttonColor;
}

std::string Button::getText() {
    return this->textArr;
}

int Button::getX() const {
    return rect.x;
}

void Button::setHighlightedColor(t_color* high_color) {
    Color c;
    if(high_color == nullptr){
        c = buttonColor;
        this->highlightedColor.r = c.r +20 <=255 ? c.r+20 :255;
        this->highlightedColor.g = c.g +20 <=255 ? c.g+20 :255;
        this->highlightedColor.b = c.b +20 <=255 ? c.b+20 :255;
        this->highlightedColor.a = c.a;
    }
    else{
        c = RenderHelper::getColor(*high_color);
        this->highlightedColor = c;
    }
}
void Button::setHighlightedColor(t_color high_color) {
    this->highlightedColor = RenderHelper::getColor(high_color);
}


void Button::setSize(SDL_Rect nRect) {
    this->rect = nRect;
    tRect.x = rect.x + (rect.w - tRect.w) / 2;
    tRect.y = rect.y + (rect.h - tRect.h) / 2;
}

void Button::setColor(t_color color) {
    this->buttonColor = RenderHelper::getColor(color);
}



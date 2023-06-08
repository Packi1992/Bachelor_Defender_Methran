//
// Created by banoodle on 08.06.23.
//
#include "renderHelper.h"
RenderHelper *RenderHelper::helperInstance={};
Color RenderHelper::getColor(t_color color) {
    switch(color){
        case MAP_GRID:
        case EMPTY:
        case BLACK:
            return {0,0,0,255};
        case WHITE:
            return {255,255,255,255};
        case BTN_COLOR:
            return {52,235,125,255};
        case BTN_HIGHLIGHTED:
            return {255,0,0,255};
        case EDITOR_UI_BG:
            return {50,220,50,255};
        case BG:
            return {	82,198,255,255};
        case YELLOW:
            return {255,255,0,255};
        case RED:
            return { 255,0,0,255 };
        default:
            return {255,255,255,255};
    }
}

RenderHelper *RenderHelper::getHelper(Renderer *render) {
    if(helperInstance == nullptr){
        helperInstance = new RenderHelper(render);
    }
    return helperInstance;
}

RenderHelper::RenderHelper(Renderer *renderer) {
    this->_renderer = renderer;
}

void RenderHelper::Text(char *string, int size, int x, int y, t_color fgC) {
    SDL_Rect textLocation = {x, y, 0, 0};
    Texture *texture = t_cache->getText(string, size,&textLocation, fgC);
    this->texture(texture,&textLocation);
    SDL_DestroyTexture(texture);
}

void RenderHelper::CenteredText(const string &text, int size, t_color fgc, int width, int height) {
    SDL_Rect textLocation;
    Texture *texture = t_cache->getText(text.c_str(),size,&textLocation, fgc);
    textLocation.x = width / 2 - textLocation.w / 2;
    textLocation.y = height / 2 - textLocation.h / 2;

    this->texture(texture,&textLocation);
    SDL_DestroyTexture(texture);
}

void RenderHelper::setColor(Color color) {
    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
}

void RenderHelper::setColor(t_color color) {
    if(color != EMPTY)
        setColor(getColor(color));
}

void RenderHelper::background(t_color color) {
    setColor(color);
    SDL_RenderClear(_renderer);
}

void RenderHelper::hint(TdTileHandler::MapObjects object, int size, Point posOnScreen, t_color textColor, t_color bgColor) {
    // get hint label
    char text[30];
    strcpy(text, TdTileHandler::getName(object).c_str());

    // get hint as texture
    SDL_Rect textLocation = {posOnScreen.x, posOnScreen.y, 0, 0};
    Texture *texture = t_cache->getText(text, size, &textLocation, textColor);

    // Render hint background
    SDL_Rect textBG = {textLocation.x-5,textLocation.y-5,textLocation.w+10,textLocation.h+10};
    rect(&textBG,bgColor);

    // Render hint
    this->texture(texture,&textLocation);

    // tidy up
    SDL_DestroyTexture(texture);
}

void RenderHelper::texture(Texture *t, Rect *dRect, Rect *sRect) const {
    SDL_RenderCopy(_renderer, t, sRect, dRect);
}

void RenderHelper::texture(Texture *t, Rect *dRect, u16 direction, Rect *sRect) const {
    SDL_RenderCopyEx(_renderer, t, sRect, dRect, (double)direction, nullptr, SDL_FLIP_NONE);

}

void RenderHelper::rect(Rect *dst, u8 strokeThickness, t_color color) {
    if(color != EMPTY)
        setColor(color);
    for(u8 i= 0 ; i<strokeThickness; i++){
        SDL_RenderDrawRect(_renderer, dst);
        dst->x++;
        dst->y++;
        dst->h -=2;
        dst->w -=2;
    }
    dst->x -=strokeThickness;
    dst->y -=strokeThickness;
    dst->h +=2*strokeThickness;
    dst->w +=2*strokeThickness;
}

void RenderHelper::fillRect(Rect *dst, t_color color) {
    if(color != EMPTY)
        setColor(color);
    SDL_RenderFillRect(_renderer, dst);
}

void RenderHelper::line(Point &A, Point &B, t_color color) {
    if(color != EMPTY)
        setColor(color);
    SDL_RenderDrawLine(_renderer, A.x, A.y, B.x, B.y);
}

void RenderHelper::tile(Rect *dRect, Rect *sRect){
    if(_texture== nullptr)
        loadTileSheet();
    texture(_texture,dRect,sRect);

}

void RenderHelper::tile(Rect *dRect, u16 direction, Rect *sRect){
    if(_texture==nullptr)
        loadTileSheet();
    texture(_texture,dRect,direction,sRect);
}

void RenderHelper::loadTileSheet(){
    _texture = t_cache->get(BasePath "asset/graphic/td/tileTD.png");
}





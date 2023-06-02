//
// Created by banoodle on 05.04.23.
//

#include "TextureCache.h"

SDL_Color TextureCache::getColor(t_color color) {
    switch(color){
        case EMPTY:
            cerr << "ERROR EMPTY Color should not be converted to actual color -> Black will be dialog to show you"<< endl;
        case MAP_GRID:
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
        default:
            return {255,255,255,255};
    }
}

Texture *TextureCache::loadTexture(const std::string &path) {
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        cerr << "SDL_image could not initialize! SDL_img Error: " << IMG_GetError << endl;
        return nullptr;
    }
    Texture *nt = nullptr;
    cout << "iniValues texture " << path << endl;
    Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        cerr << "Unable to create TextureCache from " << path << " ! SDL Error: " << SDL_GetError() << endl;
    } else {
        nt = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (nt == nullptr) {
            cerr << "Unable to create TextureCache from " << path << " ! SDL Error: " << SDL_GetError()<< endl;
        }
    }
    SDL_FreeSurface(loadedSurface);
    return nt;
}

Texture *TextureCache::get(const std::string &path) {
    obj *p = head;
    while (p != nullptr) {
        if (path == p->name)
            return p->texture;
        p = p->next;
    }
    // load texture to cache
    obj *newT = new obj();
    newT->texture = loadTexture(path);
    newT->name = path;
    if (head == nullptr || tail == nullptr) {
        newT->next = nullptr;
        head = newT;
        tail = newT;
    } else {
        tail->next = newT;
        newT->next = nullptr;
        tail = newT;
    }
    return newT->texture;
}

TextureCache::TextureCache(SDL_Renderer *renderer) {
    this->renderer = renderer;
    // ini TTF
    if (TTF_Init() == -1) {
        printf("[ERROR] TTF_Init() Failed with: %s\n", TTF_GetError());
        exit(2);
    }
}

TextureCache::~TextureCache() {
    obj *p = head;
    while (p != nullptr) {
        obj *n = p->next;
        SDL_DestroyTexture(p->texture);
        delete p;
        p = n;
    }
}

void TextureCache::drawText(char *string, int size, int x, int y, t_color fgC) {
    Rect textLocation = {x, y, 0, 0};
    Texture *texture = getText(string, size,&textLocation, fgC);
    render(texture,&textLocation);
    SDL_DestroyTexture(texture);
}

Texture *TextureCache::getText(const char *string, u8 size, Rect *sRect, t_color TextColor) {
    auto font = TTF_OpenFont(ttf_path, size);
    if (!font) {
        printf("[ERROR] TTF_OpenFont() Failed with: %s\n", TTF_GetError());
        exit(2);
    }
    Surface *surface;
    surface = TTF_RenderUTF8_Blended(font, string, getColor(TextColor));

    Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    if (sRect != nullptr) {
        SDL_QueryTexture(texture, nullptr, nullptr, &sRect->w, &sRect->h);
    }
    return texture;
}

void TextureCache::drawCenteredText(const std::string &text, int size, t_color fgc, int width, int height) {
    Rect textLocation;
    Texture *texture = getText(text.c_str(),size,&textLocation, fgc);
    textLocation.x = width / 2 - textLocation.w / 2;
    textLocation.y = height / 2 - textLocation.h / 2;

    render(texture,&textLocation);
    SDL_DestroyTexture(texture);
}

SDL_Texture *TextureCache::getNumber(int Number, int size, t_color color, SDL_Rect *sRect) {
    auto font = TTF_OpenFont(ttf_path, size);
    if (!font) {
        printf("[ERROR] TTF_OpenFont() Failed with: %s\n", TTF_GetError());
        exit(2);
    }
    SDL_Surface *surface;
    std::array<char, 20> str{};
    std::to_chars(str.data(), str.data() + str.size(), Number);
    surface = TTF_RenderUTF8_Blended(font, str.data(), getColor(color));
    SDL_Texture *texture;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (sRect != nullptr) {
        SDL_QueryTexture(texture, nullptr, nullptr, &sRect->w, &sRect->h);
    }
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    return texture;
}

TextureCache* TextureCache::getCache(Renderer *render) {
    if(cacheInstance == nullptr){
        cacheInstance = new TextureCache(render);
    }
    return cacheInstance;
}
TextureCache* TextureCache::cacheInstance = nullptr;

void TextureCache::setRenderColor(SDL_Color color) {
    SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,color.a);
}

void TextureCache::setRenderColor(t_color color) {
    setRenderColor(getColor(color));
}

void TextureCache::render(Texture *t, Rect *dRect, Rect *sRect) const {
    SDL_RenderCopy(renderer,t,sRect,dRect);
}

void TextureCache::render(Texture *t, Rect *dRect, uint16_t direction, Rect *sRect) const {
    SDL_RenderCopyEx(renderer,t,sRect,dRect,-(double)direction - 180.0, nullptr, SDL_FLIP_NONE);
}

void TextureCache::drawBackground(t_color color) {
    setRenderColor(color);
    SDL_RenderClear(renderer);
}

void TextureCache::drawHint(MapObjects object, int size, SDL_Point posOnScreen,
                            t_color textColor,t_color bgColor) {
    // get hint label
    char text[30];
    strcpy(text, TdTileHandler::getName(object).c_str());

    // get hint as texture
    SDL_Rect textLocation = {posOnScreen.x, posOnScreen.y, 0, 0};
    Texture *texture = getText(text, size, &textLocation, textColor);

    // Render hint background
    SDL_Rect textBG = {textLocation.x-5,textLocation.y-5,textLocation.w+10,textLocation.h+10};
    renderFillRect(&textBG,bgColor);

    // Render hint
    render(texture,&textLocation);

    // tidy up
    SDL_DestroyTexture(texture);
}

void TextureCache::renderFillRect(Rect *dst, t_color color) {
    if(color != EMPTY)
        setRenderColor(color);
    SDL_RenderFillRect(renderer,dst);
}

void TextureCache::renderRect(Rect *dst, u8 strokeThickness , t_color color) {
    if(color != EMPTY)
        setRenderColor(color);
    for(u8 i= 0 ; i<strokeThickness; i++){
        SDL_RenderDrawRect(renderer,dst);
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



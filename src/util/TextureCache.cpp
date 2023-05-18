//
// Created by banoodle on 05.04.23.
//

#include "TextureCache.h"

SDL_Texture *TextureCache::loadTexture(const std::string &path, SDL_Renderer *renderer) {
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! SDL_img Error: " << IMG_GetError << std::endl;
        return nullptr;
    }
    SDL_Texture *nt = nullptr;
    std::cout << "iniValues texture " << path << std::endl;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cerr << "Unable to create TextureCache from " << path << " ! SDL Error: " << SDL_GetError() << std::endl;
    } else {
        nt = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (nt == nullptr) {
            std::cerr << "Unable to create TextureCache from " << path << " ! SDL Error: " << SDL_GetError()
                      << std::endl;

        }
    }
    SDL_FreeSurface(loadedSurface);
    return nt;
}

SDL_Texture *TextureCache::getTexture(const std::string &path) {
    obj *p = head;
    while (p != nullptr) {
        if (path == p->name)
            return p->texture;
        p = p->next;
    }
    return this->addTexture(path);
}

SDL_Texture *TextureCache::addTexture(const std::string &path) {
    obj *newT = new obj();
    newT->texture = loadTexture(path, renderer);
    newT->name = path;
    if (head == nullptr || tail == nullptr) {
        newT->last = nullptr;
        newT->next = nullptr;
        head = newT;
        tail = newT;
    } else {
        tail->next = newT;
        newT->last = tail;
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

void TextureCache::drawText(char *string, int size, int x, int y, SDL_Color fgC) {
    auto font = TTF_OpenFont(ttf_path, size);
    if (!font) {
        printf("[ERROR] TTF_OpenFont() Failed with: %s\n", TTF_GetError());
        exit(2);
    }
    SDL_Surface *surface;
    surface = TTF_RenderUTF8_Blended(font, string, fgC);
    SDL_Texture *texture;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect textLocation = {x, y, 0, 0};
    SDL_QueryTexture(texture, nullptr, nullptr, &textLocation.w, &textLocation.h);
    SDL_RenderCopy(renderer, texture, nullptr, &textLocation);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

SDL_Texture *TextureCache::getText(const char *string, int size, SDL_Color TextColor, SDL_Rect *sRect) {
    auto font = TTF_OpenFont(ttf_path, size);
    if (!font) {
        printf("[ERROR] TTF_OpenFont() Failed with: %s\n", TTF_GetError());
        exit(2);
    }
    SDL_Surface *surface;
    surface = TTF_RenderUTF8_Blended(font, string,TextColor);
    SDL_Texture *texture;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    if (sRect != nullptr) {
        SDL_QueryTexture(texture, nullptr, nullptr, &sRect->w, &sRect->h);
    }
    return texture;
}

void TextureCache::drawCenteredText(const std::string &text, int size, SDL_Color fgc, int width, int height) {
    char buf[200];
    strcpy(buf, text.c_str());
    auto font = TTF_OpenFont(ttf_path, size);
    if (!font) {
        printf("[ERROR] TTF_OpenFont() Failed with: %s\n", TTF_GetError());
        exit(2);
    }
    SDL_Surface *surface;
    surface = TTF_RenderUTF8_Blended(font, buf, fgc);
    SDL_Texture *texture;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect textLocation;
    SDL_QueryTexture(texture, nullptr, nullptr, &textLocation.w, &textLocation.h);
    textLocation.x = width / 2 - textLocation.w / 2;
    textLocation.y = height / 2 - textLocation.h / 2;
    SDL_RenderCopy(renderer, texture, nullptr, &textLocation);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

SDL_Texture *TextureCache::getNumber(int Number, int size, SDL_Color color, SDL_Rect *sRect) {
    auto font = TTF_OpenFont(ttf_path, size);
    if (!font) {
        printf("[ERROR] TTF_OpenFont() Failed with: %s\n", TTF_GetError());
        exit(2);
    }
    SDL_Surface *surface;
    std::array<char, 20> str{};
    std::to_chars(str.data(), str.data() + str.size(), Number);
    surface = TTF_RenderUTF8_Blended(font, str.data(), color);
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
    setRenderColor(getSDL_Color(color));
}

SDL_Color TextureCache::getSDL_Color(t_color color) {
    switch(color){
        case BLACK:
            return {0,0,0,255};
        case WHITE:
            return {255,255,255,255};
        case BTN_COLOR:
            return {52,235,125,255};
        default:
            return {255,255,255,255};
    }
}

SDL_Texture *TextureCache::getText(const char *string, int size, t_color TextColor, SDL_Rect *sRect) {
    return getText(string,size, getSDL_Color(TextColor),sRect);
}

void TextureCache::render(SDL_Texture *t, SDL_Rect *dRect, SDL_Rect *sRect) const {
    SDL_RenderCopy(renderer,t,sRect,dRect);
}


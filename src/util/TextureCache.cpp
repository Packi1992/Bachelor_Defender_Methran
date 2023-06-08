//
// Created by banoodle on 05.04.23.
//

#include "TextureCache.h"


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
        nt = SDL_CreateTextureFromSurface(render, loadedSurface);
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

TextureCache::TextureCache() {
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

Texture *TextureCache::getText(const char *string, u8 size, Rect *sRect, t_color TextColor) {
    auto font = TTF_OpenFont(ttf_path, size);
    if (!font) {
        printf("[ERROR] TTF_OpenFont() Failed with: %s\n", TTF_GetError());
        exit(2);
    }
    Surface *surface;
    surface = TTF_RenderUTF8_Blended(font, string, rh->getColor(TextColor));

    Texture *texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    if (sRect != nullptr) {
        SDL_QueryTexture(texture, nullptr, nullptr, &sRect->w, &sRect->h);
    }
    return texture;
}

Texture *TextureCache::getNumber(int Number, int size, t_color color, SDL_Rect *sRect) {
    auto font = TTF_OpenFont(ttf_path, size);
    if (!font) {
        printf("[ERROR] TTF_OpenFont() Failed with: %s\n", TTF_GetError());
        exit(2);
    }
    SDL_Surface *surface;
    std::array<char, 20> str{};
    std::to_chars(str.data(), str.data() + str.size(), Number);
    surface = TTF_RenderUTF8_Blended(font, str.data(), rh->getColor(color));
    Texture *texture;
    texture = SDL_CreateTextureFromSurface(render, surface);
    if (sRect != nullptr) {
        SDL_QueryTexture(texture, nullptr, nullptr, &sRect->w, &sRect->h);
    }
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    return texture;
}

TextureCache* TextureCache::getCache() {
    if(cacheInstance == nullptr){
        cacheInstance = new TextureCache();
    }
    return cacheInstance;
}
TextureCache* TextureCache::cacheInstance = nullptr;



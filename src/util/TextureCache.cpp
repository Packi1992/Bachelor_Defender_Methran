//
// Created by banoodle on 05.04.23.
//

#include "TextureCache.h"
#include "gamebase.h"
#include "recthelper.h"

static constexpr const Array<Point,8> shadowOffsets = {
        /*
        Point { -1, -1 },
        Point { +1, -1 },
        Point { -1, +1 },
        Point { +1, +1 },
        Point { +0, +2 },
        Point { +2, +0 },
        Point { +0, -2 },
        Point { -2, +0 },
        */
        1_up   + 1_left,
        1_up   + 1_right,
        1_down + 1_left,
        1_down + 1_right,
        2_right,
        2_left,
        2_up,
        2_down,
};

Texture *TextureCache::loadTexture(const std::string &path) {
    Texture *nt = nullptr;
    Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        cerr << "Unable to create TextureCache from " << path << " ! SDL Error: " << SDL_GetError() << endl;
    } else {
        nt = SDL_CreateTextureFromSurface(render, loadedSurface);
        if (nt == nullptr) {
            cerr << "Unable to create TextureCache from " << path << " ! SDL Error: " << SDL_GetError() << endl;
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
    surface = TTF_RenderUTF8_Blended(font, string, RenderHelper::getColor(TextColor));

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
    surface = TTF_RenderUTF8_Blended(font, str.data(), RenderHelper::getColor(color));
    Texture *texture;
    texture = SDL_CreateTextureFromSurface(render, surface);
    if (sRect != nullptr) {
        SDL_QueryTexture(texture, nullptr, nullptr, &sRect->w, &sRect->h);
    }
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    return texture;
}

TextureCache *TextureCache::getCache() {
    if (cacheInstance == nullptr) {
        cacheInstance = new TextureCache();
    }
    return cacheInstance;
}

TextureCache *TextureCache::cacheInstance = nullptr;

Texture *TextureCache::getText(string *string, u8 size, Rect *sRect, t_color TextColor) {
    auto font = TTF_OpenFont(ttf_path, size);
    if (!font) {
        printf("[ERROR] TTF_OpenFont() Failed with: %s\n", TTF_GetError());
        exit(2);
    }
    Surface *surface;
    surface = TTF_RenderUTF8_Blended(font, string->c_str(), RenderHelper::getColor(TextColor));

    Texture *texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    if (sRect != nullptr) {
        SDL_QueryTexture(texture, nullptr, nullptr, &sRect->w, &sRect->h);
    }
    return texture;
}

Texture *TextureCache::getBlendedText(const char *string, u8 size, Rect *sRect, t_color TextColor) {
    auto font = TTF_OpenFont(ttf_path, size);
    if (!font) {
        printf("[ERROR] TTF_OpenFont() Failed with: %s\n", TTF_GetError());
        exit(2);
    }

    Surface *surface;
    surface = TTF_RenderUTF8_Blended(font, string, {255, 255, 255, 255});
    Texture *blendTexture = SDL_CreateTextureFromSurface(render, surface);


    surface = TTF_RenderUTF8_Blended(font, string, RenderHelper::getColor(TextColor));

    //texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    if (sRect != nullptr) {
        SDL_QueryTexture(blendTexture, nullptr, nullptr, &sRect->w, &sRect->h);
    }
    return blendTexture;
}

Texture *TextureCache::getWrappedText(const char *string, u8 size, int width, Rect *sRect, t_color TextColor) {
    auto font = TTF_OpenFont(ttf_path, size);
    if (!font) {
        printf("[ERROR] TTF_OpenFont() Failed with: %s\n", TTF_GetError());
        exit(2);
    }
    Texture *tex;
    Surface *surf = TTF_RenderUTF8_Blended_Wrapped(font, string,RenderHelper::getColor(TextColor), windowSize.x - 30);
    tex = SDL_CreateTextureFromSurface(render, surf);
    SDL_FreeSurface(surf);

    u32 fmt;
    int access;
    SDL_QueryTexture(tex, &fmt, &access, &sRect->w, &sRect->h);
    {
        constexpr const Point p { 32, 50 };
        SDL_SetTextureColorMod( tex, 0, 0, 0 );
        for( const Point & pd : shadowOffsets )
        {
            const Rect dst_rect = Rect{ p.x + pd.x, p.y + pd.y, sRect->x, sRect->y };
            SDL_RenderCopy( render, tex, EntireRect, &dst_rect );
        }

        SDL_SetTextureColorMod( tex, 255, 255, 255 );
        const Rect dst_rect = { p.x, p.y, sRect->x, sRect->y };
        SDL_RenderCopy( render, tex, EntireRect, &dst_rect );
    }
    return tex;
}

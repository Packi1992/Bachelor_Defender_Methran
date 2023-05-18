//
// Created by banoodle on 05.04.23.
//

#ifndef GRAFIK_TEXTURE_H
#define GRAFIK_TEXTURE_H

#include <charconv>
#include <array>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_ttf.h>
#include "../gamebase.h"

//  specific Colors to make things easier regarding drawing colors
enum t_color{
    BLACK,
    WHITE,
    BTN_COLOR,
    };

class TextureCache {

public:
    static SDL_Texture *loadTexture(const std::string &path, SDL_Renderer *renderer);

    SDL_Texture *getTexture(const std::string &path);

    void drawText(char *string, int size, int x, int y, SDL_Color fgC);

    void drawCenteredText(const std::string &text, int size, SDL_Color fgc, int width, int height);

    SDL_Texture *getText(const char *string, int size, SDL_Color TextColor, SDL_Rect *sRect = nullptr);
    SDL_Texture *getText(const char *string, int size, t_color TextColor, SDL_Rect *sRect = nullptr);
    static SDL_Color getSDL_Color(t_color color);
    SDL_Texture *getNumber(int Number, int size, SDL_Color fgC, SDL_Rect *sRect = nullptr);
    void setRenderColor(SDL_Color color);
    void setRenderColor(t_color color);
    void render(SDL_Texture *t, SDL_Rect* dRect,SDL_Rect *sRect= nullptr) const;
    TextureCache(TextureCache &other)=delete;
    void operator=(const TextureCache &)=delete;
    static TextureCache* getCache(Renderer *render);
    ~TextureCache();
private:
    static TextureCache *cacheInstance;
    explicit TextureCache(SDL_Renderer *renderer);
    const char *ttf_path = BasePath "asset/font/RobotoSlab-Bold.ttf";
    class obj {
    public:
        obj *next;
        obj *last;
        SDL_Texture *texture;
        std::string name;
    };

    obj *head{};
    obj *tail{};
    SDL_Renderer *renderer;

    SDL_Texture *addTexture(const std::string &basicString);
};

#endif //GRAFIK_TEXTURE_H

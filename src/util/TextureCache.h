//
// Created by banoodle on 05.04.23.
//

#ifndef GRAFIK_TEXTURE_H
#define GRAFIK_TEXTURE_H

#include "global.h"
#include "../tdUtil/tdTileHandler.h"
#include "SDL.h"
class TextureCache;
#include "renderHelper.h"


class TextureCache {

public:
    // iniTexture cache run at program start
    static TextureCache *getCache();

    // get texture from cache
    Texture *get(const std::string &path);

    // get Text textures
    Texture *getText(const char *string, u8 size, Rect *sRect = nullptr, t_color TextColor=BLACK);
    Texture *getText(string *string, u8 size, Rect *sRect = nullptr, t_color TextColor=BLACK);
    Texture *getWrappedText(const char* string, u8 size, int width, Rect *sRect = nullptr, t_color TextColor=BLACK);
    Texture *getNumber(int Number, int size, t_color fgC, Rect *sRect = nullptr);
    TextureCache(TextureCache &other) = delete;
    void operator=(const TextureCache &) = delete;

    ~TextureCache();

    Texture *getBlendedText(const char *string, u8 size, Rect *sRect = nullptr, t_color TextColor=BLACK);

private:
    Texture *loadTexture(const std::string &path);
    static TextureCache *cacheInstance;
    explicit TextureCache();

    const char *ttf_path = BasePath "asset/font/RobotoSlab-Bold.ttf";

    class obj {
    public:
        obj *next;
        Texture *texture;
        std::string name;
    };
    obj *head{};
    obj *tail{};
};

#endif //GRAFIK_TEXTURE_H

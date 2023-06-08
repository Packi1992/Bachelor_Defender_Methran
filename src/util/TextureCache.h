//
// Created by banoodle on 05.04.23.
//

#ifndef GRAFIK_TEXTURE_H
#define GRAFIK_TEXTURE_H

#include "../global.h"
#include "../tdUtil/tdTileHandler.h"

using MapObjects = TdTileHandler::MapObjects;

//  specific Colors to make things easier regarding drawing colors
enum t_color {
    EMPTY,
    BLACK,
    WHITE,
    BTN_COLOR,
    BTN_HIGHLIGHTED,
    MAP_GRID,
    EDITOR_UI_BG,
    BG,
    YELLOW,
    RED,
};

class TextureCache {

public:
    // iniTexture cache run at program start
    static TextureCache *getCache(Renderer *render);

    // colors are handled by TextureCache
    static Color getColor(t_color color);

    // get texture from cache
    Texture *get(const std::string &path);

    // get Text textures
    Texture *getText(const char *string, u8 size, Rect *sRect = nullptr, t_color TextColor=BLACK);
    Texture *getNumber(int Number, int size, t_color fgC, Rect *sRect = nullptr);

    // render settings
    void setRenderColor(Color color);
    void setRenderColor(t_color color);

    // Render to Render functions
    void drawBackground(t_color color);
    void render(Texture *t, Rect *dRect, Rect *sRect = nullptr) const;
    void render(Texture *t, Rect *dRect, u16 direction, Rect *sRect = nullptr) const;
    void drawHint(MapObjects object, int size, Point posOnScreen, t_color textColor=BLACK, t_color bgColor=WHITE);

    // Render text to Screen
    void drawText(char *string, int size, int x, int y, t_color fgC);
    void drawCenteredText(const string &text, int size, t_color fgc, int width, int height);

    // if no color dialog, preselected color will be used
    void renderFillRect(Rect *dst, t_color color=EMPTY);
    // if no color dialog, preselected color will be used
    void renderRect(Rect *dst, u8 strokeThickness=1 ,t_color color=EMPTY);
    // if no color dialog, preselected color will be used
    void renderLine(Point &A, Point &B, t_color color=EMPTY);

    TextureCache(TextureCache &other) = delete;
    void operator=(const TextureCache &) = delete;

    ~TextureCache();
private:
    Texture *loadTexture(const std::string &path);
    static TextureCache *cacheInstance;
    explicit TextureCache(Renderer *renderer);

    const char *ttf_path = BasePath "asset/font/RobotoSlab-Bold.ttf";

    class obj {
    public:
        obj *next;
        Texture *texture;
        std::string name;
    };
    obj *head{};
    obj *tail{};
    Renderer *renderer;


};

#endif //GRAFIK_TEXTURE_H

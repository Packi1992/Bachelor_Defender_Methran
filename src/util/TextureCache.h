//
// Created by banoodle on 05.04.23.
//

#ifndef GRAFIK_TEXTURE_H
#define GRAFIK_TEXTURE_H

#include "../global.h"
#include "../tdUtil/tdTileHandler.h"

//  specific Colors to make things easier regarding drawing colors
enum t_color {
    EMPTY,
    BLACK,
    WHITE,
    BTN_COLOR,
    MAP_GRID,
    EDITOR_UI_BG,
    BG,
};

class TextureCache {

public:
    Texture *loadTexture(const std::string &path);

    Texture *getTexture(const std::string &path);

    void drawText(char *string, int size, int x, int y, Color fgC);

    void drawCenteredText(const std::string &text, int size, Color fgc, int width, int height);

    Texture *getText(const char *string, int size, Color TextColor, Rect *sRect = nullptr);

    Texture *getText(const char *string, int size, t_color TextColor, Rect *sRect = nullptr);

    static Color getColor(t_color color);

    Texture *getNumber(int Number, int size, Color fgC, Rect *sRect = nullptr);

    void setRenderColor(Color color);

    void setRenderColor(t_color color);

    void render(Texture *t, Rect *dRect, Rect *sRect = nullptr) const;

    // if no color dialog, preselected color will be used
    void renderFillRect(Rect *dst, t_color color=EMPTY);
    // if no color dialog, preselected color will be used
    void renderRect(Rect *dst, u8 strokeThickness=1 ,t_color color=EMPTY);

    TextureCache(TextureCache &other) = delete;

    void operator=(const TextureCache &) = delete;

    static TextureCache *getCache(Renderer *render);

    void drawBackground(t_color color);

    void drawHint(TdTileHandler::MapObjects object, int size, Point posOnScreen, t_color textColor, t_color bgColor);

    ~TextureCache();

private:
    static TextureCache *cacheInstance;

    explicit TextureCache(Renderer *renderer);

    const char *ttf_path = BasePath "asset/font/RobotoSlab-Bold.ttf";

    class obj {
    public:
        obj *next;
        obj *last;
        Texture *texture;
        std::string name;
    };

    obj *head{};
    obj *tail{};
    Renderer *renderer;

    Texture *addTexture(const std::string &basicString);


};

#endif //GRAFIK_TEXTURE_H

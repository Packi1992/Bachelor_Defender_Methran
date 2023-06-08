//
// Created by banoodle on 08.06.23.
//

#ifndef SDL_BACHELORDEFENDER_RENDERHELPER_H
#define SDL_BACHELORDEFENDER_RENDERHELPER_H
class RenderHelper;
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
#include "../global.h"

#include "TextureCache.h"
#include "../gamebase.h"

class RenderHelper{
public:
    static RenderHelper *getHelper(Renderer *render);
    // colors are handled by RenderHelper
    static Color getColor(t_color color);
    // render settings
    // EMPTY color will not be set
    void setColor(Color color);
    void setColor(t_color color);

    void background(t_color color);
    void texture(Texture *t, Rect *dRect, Rect *sRect = nullptr) const;
    void texture(Texture *t, Rect *dRect, u16 direction, Rect *sRect = nullptr) const;

    // if no color dialog, preselected color will be used
    void fillRect(Rect *dst, t_color color=EMPTY);
    // if no color dialog, preselected color will be used
    void rect(Rect *dst, u8 strokeThickness=1 ,t_color color=EMPTY);
    // if no color dialog, preselected color will be used
    void line(Point &A, Point &B, t_color color=EMPTY);

    // Render to Render functions
    void hint(MapObjects object, int size, Point posOnScreen, t_color textColor=BLACK, t_color bgColor=WHITE);

    // Render text to Screen
    void Text(char *string, int size, int x, int y, t_color fgC);
    void CenteredText(const string &text, int size, t_color fgc, int width, int height);
    RenderHelper(RenderHelper &other) = delete;
    void operator=(const RenderHelper &) = delete;

private:
    Renderer *renderer;
    static RenderHelper *helperInstance;
    explicit RenderHelper(Renderer *renderer);

};
#endif //SDL_BACHELORDEFENDER_RENDERHELPER_H

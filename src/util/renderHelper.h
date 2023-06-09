//
// Created by banoodle on 08.06.23.
//

#ifndef SDL_BACHELORDEFENDER_RENDERHELPER_H
#define SDL_BACHELORDEFENDER_RENDERHELPER_H
#include <SDL_render.h>
#include <string>
#include "../enums.h"

class RenderHelper{
public:
    static RenderHelper *getHelper(SDL_Renderer *render);
    // colors are handled by RenderHelper
    static SDL_Color getColor(t_color color);
    // render settings
    // EMPTY color will not be set
    void setColor(SDL_Color color);
    void setColor(t_color color);

    void background(t_color color);
    void texture(SDL_Texture *t, SDL_Rect *dRect, SDL_Rect *sRect = nullptr) const;
    void texture(SDL_Texture *t, SDL_Rect *dRect, std::uint16_t direction, SDL_Rect *sRect = nullptr) const;
    void tile(SDL_Rect *dRect, SDL_Rect *sRect = nullptr);
    void tile(SDL_Rect *dRect, std::uint16_t direction, SDL_Rect *sRect = nullptr);
    // if no color dialog, preselected color will be used
    void fillRect(SDL_Rect *dst, t_color color=EMPTY);
    void fillFRect(SDL_FRect *rect, t_color color=EMPTY);
    // if no color dialog, preselected color will be used
    void rect(SDL_Rect *dst, std::uint8_t strokeThickness=1 ,t_color color=EMPTY);

    // if no color dialog, preselected color will be used
    void line(SDL_Point &A, SDL_Point &B, t_color color=EMPTY);

    // Render to Render functions
    void hint(MapObjects object, int size, SDL_Point posOnScreen, t_color textColor=BLACK, t_color bgColor=WHITE);

    // Render text to Screen
    void Text(char *string, int size, int x, int y, t_color fgC);
    void CenteredText(const std::string &text, int size, t_color fgc, int width, int height);
    RenderHelper(RenderHelper &other) = delete;
    void operator=(const RenderHelper &) = delete;


    void symbol(SDL_Rect *pRect, MenuEntries &entries);

private:
    SDL_Texture *_texture={};
    SDL_Renderer *_renderer{};
    static RenderHelper *helperInstance;
    explicit RenderHelper(SDL_Renderer *renderer);

    void loadTileSheet();
};
#endif //SDL_BACHELORDEFENDER_RENDERHELPER_H

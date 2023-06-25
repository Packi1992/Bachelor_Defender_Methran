//
// Created by banoodle on 08.06.23.
//
#include "renderHelper.h"
#include "global.h"
#include "gui/floatingMenu.h"

using MapObjects = MapObjects;

RenderHelper *RenderHelper::helperInstance = {};

Color RenderHelper::getColor(t_color color) {
    switch (color) {
        case MAP_GRID:
        case EMPTY:
        case BLACK:
            return {0, 0, 0, 255};
        case WHITE:
            return {255, 255, 255, 255};
        case BTN_COLOR:
            return {0x07, 0xa1, 0xe2, 255};
        case BTN_HIGHLIGHTED:
            return {255, 0, 0, 255};
        case EDITOR_UI_BG:
            return {18, 51, 91, 255};
        case BG:
            return {82, 198, 255, 255};
        case YELLOW:
            return {255, 255, 0, 255};
        case RED:
            return {255, 0, 0, 255};
        case GREEN:
            return {0, 255, 0, 255};
        case BLUE:
            return {0, 0, 255, 255};
        default:
            return {255, 255, 255, 255};
    }
}

RenderHelper *RenderHelper::getHelper(Renderer *renderer) {
    if (helperInstance == nullptr) {
        helperInstance = new RenderHelper(renderer);
    }
    return helperInstance;
}

RenderHelper::RenderHelper(Renderer *renderer) {
    this->_renderer = renderer;
}

void RenderHelper::Text(char *string, int size, int x, int y, t_color fgC) const {
    SDL_Rect textLocation = {x, y, 0, 0};
    Texture *texture = t_cache->getText(string, size, &textLocation, fgC);
    this->texture(texture, &textLocation);
    SDL_DestroyTexture(texture);
}

void RenderHelper::CenteredText(const string &text, int size, t_color fgc, int width, int height) const {
    SDL_Rect textLocation;
    Texture *texture = t_cache->getText(text.c_str(), size, &textLocation, fgc);
    textLocation.x = width / 2 - textLocation.w / 2;
    textLocation.y = height / 2 - textLocation.h / 2;

    this->texture(texture, &textLocation);
    SDL_DestroyTexture(texture);
}

void RenderHelper::setColor(Color color) {
    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
}

void RenderHelper::setColor(t_color color) {
    if (color != EMPTY)
        setColor(getColor(color));
}

void RenderHelper::background(t_color color, int alpha) {
    if (alpha == 255) {
        setColor(color);
        SDL_RenderClear(_renderer);
    } else {
        SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
        Rect bg = {0, 0, windowSize.x, windowSize.y};
        Color t = getColor(color);
        t.a = alpha;
        SDL_SetRenderDrawColor(render, t.r, t.g, t.b, t.a);
        fillRect(&bg);
        SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_NONE);
    }
}

void RenderHelper::hint(MapObjects object, int size, Point posOnScreen, t_color textColor, t_color bgColor) {
    // get hint label
    char text[30];
    strcpy(text, TdTileHandler::getName(object).c_str());

    // get hint as texture
    SDL_Rect textLocation = {posOnScreen.x, posOnScreen.y, 0, 0};
    Texture *texture = t_cache->getText(text, size, &textLocation, textColor);

    // Render hint background
    SDL_Rect textBG = {textLocation.x - 5, textLocation.y - 5, textLocation.w + 10, textLocation.h + 10};
    rect(&textBG, bgColor);

    // Render hint
    this->texture(texture, &textLocation);

    // tidy up
    SDL_DestroyTexture(texture);
}

void RenderHelper::texture(Texture *t, Rect *dRect, Rect *sRect) const {
    SDL_RenderCopy(_renderer, t, sRect, dRect);
}

void RenderHelper::texture(Texture *t, Rect *dRect, u16 direction, Rect *sRect) const {
    SDL_RenderCopyEx(_renderer, t, sRect, dRect, (double) direction, nullptr, SDL_FLIP_NONE);
}

void RenderHelper::textureHflipped(Texture *t, Rect *dRect, Rect *sRect) const {
    SDL_RenderCopyEx(_renderer, t, sRect, dRect, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
}

void RenderHelper::rect(Rect *dst, u8 strokeThickness, t_color color) {
    if (color != EMPTY)
        setColor(color);
    for (u8 i = 0; i < strokeThickness; i++) {
        SDL_RenderDrawRect(_renderer, dst);
        dst->x++;
        dst->y++;
        dst->h -= 2;
        dst->w -= 2;
    }
    dst->x -= strokeThickness;
    dst->y -= strokeThickness;
    dst->h += 2 * strokeThickness;
    dst->w += 2 * strokeThickness;
}

void RenderHelper::fillRect(Rect *dst, t_color color, uint8_t alpha) {
    if (alpha == 255) {
        if (color != EMPTY)
            setColor(color);
        SDL_RenderFillRect(_renderer, dst);
    } else {
        SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
        Color t = getColor(color);
        t.a = alpha;
        SDL_SetRenderDrawColor(render, t.r, t.g, t.b, t.a);
        fillRect(dst);
        SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_NONE);
    }
}

void RenderHelper::fillRect(Rect *dst, SDL_Color color, uint8_t alpha) {
    if (alpha == 255) {
        setColor(color);
        SDL_RenderFillRect(_renderer, dst);
    } else {
        SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
        color.a = alpha;
        SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);
        fillRect(dst);
        SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_NONE);
    }
}

void RenderHelper::fillFRect(FRect *rect, t_color color) {
    if (color != EMPTY)
        setColor(color);
    SDL_RenderFillRectF(_renderer, rect);
}

void RenderHelper::line(Point &A, Point &B, t_color color) {
    if (color != EMPTY)
        setColor(color);
    SDL_RenderDrawLine(_renderer, A.x, A.y, B.x, B.y);
}

void RenderHelper::tile(Rect *dRect, Rect *sRect, bool vFlipped) {
    if (_texture == nullptr)
        loadTileSheet();
    if (vFlipped)
        textureHflipped(_texture, dRect, sRect);
    else
        texture(_texture, dRect, sRect);

}

void RenderHelper::tile(Rect *dRect, u16 direction, Rect *sRect) {
    if (_texture == nullptr)
        loadTileSheet();
    texture(_texture, dRect, direction, sRect);
}

void RenderHelper::loadTileSheet() {
    _texture = t_cache->get(BasePath "asset/graphic/td/tileTD.png");
    _blocked = t_cache->get(BasePath "asset/graphic/editor/blocked.png");
    _arrow = t_cache->get(BasePath "asset/graphic/editor/arrow.png");
    _nemoney = t_cache->getText("CP", 28, nullptr, RED);
    _sell = t_cache->getText("SELL", 28, nullptr, GREEN);
    _link = t_cache->getText("LINK", 20, nullptr, BLUE);
}

void RenderHelper::symbol(SDL_Rect *center, MenuEntry &entry) {
    switch (entry._menuEntry) {
        case MenuEntry_DEFAULT:
            break;
        case MenuEntry_BOOMERANG:
            helperInstance->tile(center, TdTileHandler::getTowerSrcRect(RecursivBase));
            helperInstance->tile(center, TdTileHandler::getTowerSrcRect(Tower_Boomerang));
            break;
        case MenuEntry_POINTER:
            helperInstance->tile(center, TdTileHandler::getTowerSrcRect(Base));
            helperInstance->tile(center, TdTileHandler::getTowerSrcRect(Pointer));
            break;
        case MenuEntry_HASHCANON:
            helperInstance->tile(center, TdTileHandler::getTowerSrcRect(Hashcanon));
            break;
        case MenuEntry_STRINGTOWER:
            helperInstance->tile(center, TdTileHandler::getTowerSrcRect(StringTower));
            break;
        case MenuEntry_LinkedList:
            helperInstance->tile(center, TdTileHandler::getTowerSrcRect(Tower_LinkedListBase));
            helperInstance->tile(center, TdTileHandler::getTowerSrcRect(Tower_LinkedList));
            //helperInstance->texture(_link, center);
            break;
        case MenuEntry_Sell:
            helperInstance->texture(_sell, center);
            break;
        case MenuEntry_Upgrade:
            helperInstance->texture(_arrow, center);
            break;
        case MenuEntry_AddLink:
            helperInstance->texture(_link, center);
        case MenuEntry_Error:
        case MenuEntry_Disabled:
        default:
            break;
    }
    switch (entry._status) {
        case Status_EnemyBlocking:
        case Status_Disabled:
            helperInstance->texture(_blocked, center);
            break;
        case Status_NotEnoughMoney:
            helperInstance->texture(_nemoney, center);
            break;
        case Status_Active:
        default:
            break;
    }
}


void RenderHelper::blendTexture(SDL_Texture *blendedText, SDL_Rect *r) {
    constexpr const Point p{32, 50};
    SDL_SetTextureColorMod(blendedText, 0, 0, 0);
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            const Rect dst_rect = Rect{r->x + i, r->y + j, r->w, r->h};
            SDL_RenderCopy(render, blendedText, nullptr, &dst_rect);
        }
    }

    SDL_SetTextureColorMod(blendedText, 255, 255, 255);
    const Rect dst_rect = {r->x, r->y, r->w, r->h};
    SDL_RenderCopy(render, blendedText, nullptr, &dst_rect);
}





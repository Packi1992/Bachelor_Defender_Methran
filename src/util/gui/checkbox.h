//
// Created by banoodle on 24.05.23.
//

#ifndef SDL_BACHELORDEFENDER_CHECKBOX_H
#define SDL_BACHELORDEFENDER_CHECKBOX_H
#include "gui.h"

class CheckBox{
public:
    CheckBox() = default;

    CheckBox(const CheckBox &b);
    CheckBox(const string &label, int size, Rect rect, int id=0, t_color btn_color = BTN_COLOR);
    CheckBox(const string &label, int size, int id=0, t_color btn_color = BTN_COLOR);

    void draw(bool highlighted = false);

    bool clicked(Event e);
    bool clicked(Point p);
    ~CheckBox();

    void entered(Event e);
    void entered(Point p);
    std::string getText();

    int getX() const;
    int getId() const;

    void set(const string &label, int size, Rect rect, int id=0, t_color btn_color = BTN_COLOR);

    void setSize(Rect rect);

    void setHighlightedColor(const t_color *high_color = nullptr);
    void setHighlightedColor(t_color high_color);
    void setColor(t_color color);

private:
    bool isPointOnBtn(Point &p) const;
    // button background rect
    Rect _rect{};
    // text rect
    Rect _rText{};
    Texture *_texText{};
    Color _buttonColor{};
    Color _highlightedColor{};
    Color _drawColor{};
    int _size{};
    int _id=0;
    char _textArr[50]{};
};
#endif //SDL_BACHELORDEFENDER_CHECKBOX_H

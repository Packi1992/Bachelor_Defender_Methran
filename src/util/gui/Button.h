//
// Created by banoodle on 15.04.23.
//

#ifndef JUMPNRUN_BUTTON_H
#define JUMPNRUN_BUTTON_H
class Button;
#include "../gamebase.h"


class Button {
public:
    Button() = default;

    Button(const Button &b);
    Button(const string &label, int size, Rect rect, int id=0, t_color btn_color = BTN_COLOR);
    Button(const string &label, int size, int id=0, t_color btn_color = BTN_COLOR);

    void draw(bool highlighted = false);

    bool clicked(Event e);
    bool clicked(Point p);
    ~Button();

    void entered(Event e);
    void entered(Point p);
    std::string getText();

    int getX() const;
    int getId() const;

    void set(const string &label, int size, Rect rect, int id=0, t_color btn_color = BTN_COLOR);

    void setSize(Rect rect);

    void setHighlightedColor(t_color *high_color = nullptr);
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

#endif //JUMPNRUN_BUTTON_H
//
// Created by banoodle on 15.04.23.
//

#ifndef JUMPNRUN_BUTTON_H
#define JUMPNRUN_BUTTON_H

#include "../gamebase.h"


class Button {
public:
    Button() = default;

    Button(const Button &b);

    Button(const string &label, int size, Rect rect, int id = 0, t_color btn_color = BTN_COLOR, bool blend = false);

    Button(const string &label, int size, int id = 0, t_color btn_color = BTN_COLOR, bool blend = false);

    void Render(bool highlighted = false);

    bool clicked(Event e);

    bool clicked(Point p);

    ~Button();

    void entered(Event e);

    void entered(Point p);

    std::string getText();

    int getX() const;

    int getId() const;

    void set(const string &label, int size, Rect rect, int id = 0, t_color btn_color = BTN_COLOR, bool blend = false);

    void setSize(Rect rect);

    void setHighlightedColor(const t_color *high_color = nullptr);

    void setHighlightedColor(t_color high_color);
    void setInactivColor(t_color inactive_color);
    void setColor(t_color color);

    void setActive(bool b);

    void setVisible(bool b);


    void setBlendet(bool Blendet);

private:
    bool isPointOnBtn(Point &p) const;

    // button background rect
    Rect _rect{};
    // text rect
    Rect _rText{};
    Texture *_texText{};
    Color _buttonColor{};
    Color _highlightedColor{};
    Color _inactivColor{};
    Color _drawColor{};
    int _size{};
    int _id = 0;
    int _strokeThickness = 2;
    bool _blend = false;
    char _textArr[50]{};
    bool _active = true;
    bool _visible = true;
};

#endif //JUMPNRUN_BUTTON_H
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

    void draw(bool highlighted = false);

    bool clicked(Event e);

    ~Button();

    void entered(Event e);

    std::string getText();

    int getX() const;

    void set(const std::string &label, int size, Rect rect, t_color btn_color = BTN_COLOR);

    void setSize(Rect rect);

    void setHighlightedColor(t_color *high_color = nullptr);

private:
    // button background rect
    Rect rect{};
    // text rect
    Rect tRect{};
    Texture *text = nullptr;
    Color buttonColor{};
    Color highlightedColor{};
    Color drawColor{};
    int size{};
    char textArr[50]{};
};

#endif //JUMPNRUN_BUTTON_H
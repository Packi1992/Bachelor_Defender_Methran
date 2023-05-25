//
// Created by banoodle on 24.05.23.
//

#ifndef SDL_BACHELORDEFENDER_TEXTBOX_H
#define SDL_BACHELORDEFENDER_TEXTBOX_H
#include "../gamebase.h"

class TextBox {
public:
    void set(std::string label, int x, int y, bool Number = false);
    void setMaxLength(int size);

    void setText(std::string text);

    std::string getText();

    int getNumber();

    void setNumber(int number);

    void draw();

    void fieldSelected(SDL_Event event);

    void getInput();

    ~TextBox();

private:
    Rect inputFieldRect{};
    Rect inputTextRect{};
    Rect labelRect{};
    Texture *texLabel = nullptr;
    Texture *texInput = nullptr;
    std::string txtLabel;
    std::string txtInput;
    int max_length = 30;
    bool onlyNumber;
    bool selected = false;
    int blink = 0;

    void updateInput();
};
#endif //SDL_BACHELORDEFENDER_TEXTBOX_H

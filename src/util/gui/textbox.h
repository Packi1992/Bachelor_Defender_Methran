//
// Created by banoodle on 24.05.23.
//

#ifndef SDL_BACHELORDEFENDER_TEXTBOX_H
#define SDL_BACHELORDEFENDER_TEXTBOX_H
#include "gui.h"

class TextBox: public Gui {
public:
    // ini functions
    void set(string label, Point pos, bool Number = false, bool reset = false, bool textBorder = false);
    // for number input
    void setNumber(int number);
    // for text input
    void setMaxLength(int size);
    void setText(std::string text);

    // output functions
    string getText();
    int getNumber();

    // check if field is dialog with mouse
    bool fieldSelected(SDL_Event event);

    void Render() override;
    void Input() override;
    void Update() override;

    ~TextBox();

private:
    int max_length = 30;
    bool _isNumber = false;
    int blink = 0;

    // label
    string _label;
    Rect _rLabel{};
    Texture *_texLabel = nullptr;

    // input
    string _input;
    string _renderedInput;
    Rect _rInput{};
    Texture *_texInput = nullptr;

    // input field
    Rect _rInputField{};
};
#endif //SDL_BACHELORDEFENDER_TEXTBOX_H

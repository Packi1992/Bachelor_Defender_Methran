//
// Created by banoodle on 24.05.23.
//
#include "textbox.h"

void TextBox::set(string label, Point pos, bool Number, bool reset, bool textBorder) {
    _isNumber = Number;
    _textBorder = textBorder;
    // ini label
    _label = std::move(label);
    if (_textBorder) {
        _texLabel = t_cache->getText(_label.c_str(), 18, &_rLabel, WHITE);
    } else {
        _texLabel = t_cache->getText(_label.c_str(), 18, &_rLabel);
    }
    _rLabel.x = pos.x;
    _rLabel.y = pos.y;

    // ini input field - behind label
    _rInputField.x = _rLabel.x + _rLabel.w + 10;
    _rInputField.y = pos.y - 5;
    _rInputField.h = _rLabel.h + 10;
    _rInputField.w = max_length * 5 + 10;

    // ini actual inputText as empty
    if (reset) {
        _renderedInput = "";
        _input = "";
    }
    _rInput.x = _rInputField.x + 5;
    _rInput.y = _rInputField.y + 5;
    _rInput.w = 0;
    _rInput.h = _rLabel.h;
}

void TextBox::setMaxLength(int size) {
    max_length = size;
}

void TextBox::setText(std::string text) {
    _input = std::move(text);
    if (_texInput != nullptr)
        SDL_DestroyTexture(_texInput);
    _texInput = t_cache->getText(_input.c_str(), 18, &_rInput, BLACK);
    _renderedInput = _input;
}

std::string TextBox::getText() {
    return _input;
}

int TextBox::getNumber() {
    return atoi(_input.c_str());
}

void TextBox::setNumber(int number) {
    _input = "";
    _input += std::to_string(number);
    if (_texInput != nullptr)
        SDL_DestroyTexture(_texInput);
    _texInput = t_cache->getText(&_input, 18, &_rInput);
    IfDebug { cout << "TextBox: length of text rect " << _rInput.w << endl; };
    _renderedInput = "";
    _renderedInput += _input;
}

void TextBox::Render() {
    if (_textBorder) {
        rh->blendTexture(_texLabel, &_rLabel);
    } else {
        rh->texture(_texLabel, &_rLabel);
    }
    rh->fillRect(&_rInputField, WHITE);
    rh->rect(&_rInputField, 1, BLACK);
    if (!_renderedInput.empty())
        rh->texture(_texInput, &_rInput);
    if (dialog) {
        if (blink > 20) {
            Point curA, curB;
            curA.x = curB.x = _rInput.x + _rInput.w;
            curA.y = _rInput.y;
            curB.y = _rInput.y + _rInput.h;
            rh->line(curA, curB);
        }
    }
}

bool TextBox::fieldSelected(Event event) {
    bool right = event.motion.x > _rInputField.x;
    bool left = event.motion.x < _rInputField.x + _rInputField.w;
    bool over = event.motion.y < _rInputField.y + _rInputField.h;
    bool under = event.motion.y > _rInputField.y;
    if (right && left && over && under) {
        blink = 0;
        return true;
    }
    return false;
}

void TextBox::Input() {
    SDL_StartTextInput();
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (pGame->HandleEvent(event))
            return;
        switch (event.type) {
            case SDL_TEXTINPUT:
                if (_isNumber) {
                    char buf[50] = {0};
                    strncat(buf, event.text.text,50);
                    for (char c: buf) {
                        if (c >= '0' && c <= '9')
                            _input += c;
                    }
                } else {
                    _input += event.text.text;
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_BACKSPACE && !_input.empty())
                    _input.erase(_input.size() - 1);
                if (event.key.keysym.sym == SDLK_KP_ENTER) {
                    releaseFocus(true);
                    blink = 0;
                }

                break;
            case SDL_MOUSEBUTTONDOWN:
                bool left = event.motion.x < _rInputField.x;
                bool right = event.motion.x > _rInputField.x + _rInputField.w;
                bool top = event.motion.y < _rInputField.y;
                bool bottom = event.motion.y > _rInputField.y + _rInputField.h;
                if (left || right || top || bottom) {
                    SDL_PushEvent(&event);
                    blink = 0;
                    releaseFocus(true);
                    return;
                }
                break;
        }
    }
    Update();
    SDL_StopTextInput();
}

TextBox::~TextBox() {
    if (_texLabel != nullptr)
        SDL_DestroyTexture(_texLabel);
    if (_texInput != nullptr)
        SDL_DestroyTexture(_texInput);
}

void TextBox::Update() {
    if (_input != _renderedInput) {
        if (_texInput != nullptr)
            SDL_DestroyTexture(_texInput);
        _texInput = t_cache->getText(_input.c_str(), 18, &_rInput, BLACK);
        _renderedInput = _input;
    }
    if (dialog)
        blink = (blink + 1) % 40;
    else
        blink = 0;
}


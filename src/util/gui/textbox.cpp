//
// Created by banoodle on 24.05.23.
//
#include "textbox.h"

void TextBox::set(string label, Point pos, bool Number) {
    _isNumber = Number;

    // ini label
    _label = std::move(label);
    _texLabel = t_cache->getText(_label.c_str(), 18, &_rLabel);
    _rLabel.x = pos.x;
    _rLabel.y = pos.y;

    // ini input field - behind label
    _rInputField.x = _rLabel.x + _rLabel.w + 10;
    _rInputField.y = pos.y - 5;
    _rInputField.h = _rLabel.h + 10;
    _rInputField.w = max_length * 5 + 10;

    // ini actual inputText as empty
    _renderedInput="";
    _input = "";
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
    _texInput = t_cache->getText(_input.c_str(), 18, &_rInput);
}

std::string TextBox::getText() {
    return _input;
}

int TextBox::getNumber() {
    return atoi(_input.c_str());
}

void TextBox::setNumber(int number) {
    _input = std::to_string(number);
    Update();
}

void TextBox::Render() {
    t_cache->render(_texLabel, &_rLabel);
    t_cache->renderFillRect(&_rInputField, WHITE);
    t_cache->renderRect(&_rInputField, 1,BLACK);
    if (!_renderedInput.empty())
        t_cache->render(_texInput, &_rInput);
    if (dialog) {
        if (blink > 20) {
            Point curA,curB;
            curA.x = curB.x= _rInput.x + _rInput.w;
            curA.y = _rInput.y;
            curB.y = _rInput.y + _rInput.h;
            t_cache->renderLine(curA,curB);
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
        if(pGame->HandleEvent(event))
            return;
        switch (event.type) {
            case SDL_TEXTINPUT:
                if (_isNumber) {
                    char buf[50] = "";
                    strcat(buf, event.text.text);
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
                if (event.key.keysym.sym == SDLK_KP_ENTER)
                    releaseFocus();
                break;
            case SDL_MOUSEBUTTONDOWN:
                bool left = event.motion.x < _rInputField.x;
                bool right = event.motion.x > _rInputField.x + _rInputField.w;
                bool top = event.motion.y < _rInputField.y;
                bool bottom = event.motion.y > _rInputField.y + _rInputField.h;
                if (left || right || top || bottom) {
                    SDL_PushEvent(&event);
                    releaseFocus();
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
    if (_input.compare(_renderedInput) != 0) {
        if (_texInput != nullptr)
            SDL_DestroyTexture(_texInput);
        _texInput = t_cache->getText(_input.c_str(), 18, &_rInput);
        _renderedInput = _input;
    }
    if(dialog)
        blink = (blink + 1) % 40;
}


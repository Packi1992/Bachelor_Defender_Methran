//
// Created by banoodle on 24.05.23.
//
#include "inputDialog.h"

#include <utility>
#include "../../tdUtil/editor.h"

void InputDialog::set(string title, const string &fieldName, string inputIniVal, int buffSize) {
    _buffSize = buffSize;
    _title = std::move(title);
    _input = std::move(inputIniVal);
    _textBox.setMaxLength(buffSize);
    iniUI(fieldName);
    iniValues();
}

void InputDialog::iniValues() {
    _textBox.setText("neueMap");
}

void InputDialog::iniUI(const string &fieldName) {
    Point wSize = pGame->GetWindowSize();
    _rDialog = {wSize.x / 2 - 250, wSize.y / 2 - 200, 500, 250};
    // Title as centered text at top
    _texTitle = t_cache->getText(_title.c_str(), 30, &_rTitle);
    _rTitle.x = _rDialog.x + _rDialog.w / 2 - _rTitle.w / 2;
    _rTitle.y = _rDialog.y + 10;
    // Align Buttons
    int btnY = _rDialog.y + _rDialog.h - 50;
    _btn_ok.set("OK", 18, {_rDialog.x + _rDialog.w - 100, btnY, 80, 40});
    _btn_abb.set("ABBRUCH", 18, {_rDialog.x + 20, btnY, 100, 40});
    _textBox.set(fieldName, {_rDialog.x + 20, _rDialog.y + 80}, false);
    _textBox.setMaxLength(_buffSize);
    _textBox.setText(_input);
}

void InputDialog::Input() {
    if(focus!= nullptr)
        focus->Input();
    if(focus == nullptr){
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
                    selection(event);
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_ESCAPE:
                            releaseFocus();
                            break;
                        case SDL_SCANCODE_KP_ENTER:
                            acceptInput();
                            break;
                        default:
                            break;
                    }
            }
        }
    }
}

void InputDialog::selection(Event event) {
    if (event.button.button == SDL_BUTTON_LEFT) {
        if(_textBox.fieldSelected(event)){
            _textBox.show(&focus);
        }
        if (_btn_ok.clicked(event)) {
            acceptInput();
        }
        if (_btn_abb.clicked(event)) {
            releaseFocus();
        }
    }
}

void InputDialog::acceptInput() {
    releaseFocus();
    _input = _textBox.getText();
    _takeNewValues = true;
}

void InputDialog::Render() {
    if (dialog) {
        t_cache->renderFillRect(&_rDialog, EDITOR_UI_BG);
        t_cache->render(_texTitle, &_rTitle);
        _textBox.Render();
        _btn_ok.draw();
        _btn_abb.draw();
    }
}

void InputDialog::Update() {
}

string InputDialog::getInput() {
    return _input;
}

bool InputDialog::isDone() const {
    return _takeNewValues;
}

InputDialog::~InputDialog() {
    SDL_DestroyTexture(_texTitle);
}
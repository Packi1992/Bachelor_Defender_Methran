//
// Created by banoodle on 22.04.23.
//

#include "sizeDialog.h"

void SizeDialog::set(int width, int height, bool textborder) {
    _width = width;
    _height = height;
    _textBorder = textborder;
    iniUI();
    iniValues();
}


void SizeDialog::iniValues() {
    _txtb_width.setNumber(_width);
    _txtb_height.setNumber(_height);
}

void SizeDialog::iniUI() {
    _rDialog = {windowSize.x / 2 - 250, windowSize.y / 2 - 200, 500, 400};
    // Title
    if(_textBorder) {
        _texTitle = t_cache->getBlendedText("Ändere die Größe der Map", 30, &_rTitle, WHITE);
    }else{
        _texTitle = t_cache->getBlendedText("Ändere die Größe der Map", 30, &_rTitle, BLACK);
    }
    // Align Buttons
    int btnY = _rDialog.y + _rDialog.h - 50;

    _rTitle.x = _rDialog.x + _rDialog.w / 2 - _rTitle.w / 2;
    _rTitle.y = _rDialog.y + 10;
    _btn_ok.set("OK", 18, {_rDialog.x + _rDialog.w - 100, btnY, 80, 40}, 0, BTN_COLOR, _textBorder);
    _btn_abb.set("ABBRUCH", 18, {_rDialog.x + 20, btnY, 100, 40}, 0, BTN_COLOR, _textBorder);
    _txtb_width.set("Breite", {_rDialog.x + 20, _rDialog.y + 80}, true,false,_textBorder);
    _txtb_height.set("Höhe", {_rDialog.x + 20, _rDialog.y + 160}, true,false,_textBorder);
}


void SizeDialog::Input() {
    if (focus != nullptr)
        focus->Input();
    if (focus == nullptr) {
        Event event;
        while (SDL_PollEvent(&event)) {
            if (pGame->HandleEvent(event))
                return;
            handleEvent(event);
        }
    }
}

void SizeDialog::handleEvent(Event event) {
    switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            selection(event);
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_ESCAPE:
                    releaseFocus(false);
                    break;
                case SDL_SCANCODE_KP_ENTER:
                    acceptInput();
                    break;
                default:
                    break;
            }
    }
}


void SizeDialog::selection(Event event) {
    if (event.button.button == SDL_BUTTON_LEFT) { //left mouse button
        if (_txtb_height.fieldSelected(event)) {
            _txtb_height.show(&focus);
        }
        if (_txtb_width.fieldSelected(event)) {
            _txtb_width.show(&focus);
        }
        if (_btn_ok.clicked(event)) {
            acceptInput();
        }
        if (_btn_abb.clicked(event)) {
            releaseFocus(false);
        }
    }
}

void SizeDialog::acceptInput() {
    releaseFocus(false);
    _width = _txtb_width.getNumber();
    _height = _txtb_height.getNumber();
    _takeNewValues = true;
}

void SizeDialog::Render() {
    if (dialog) {
        rh->fillRect(&_rDialog, EDITOR_UI_BG);
        if(_textBorder){
            rh->blendTexture(_texTitle, &_rTitle);
        }else{
            rh->texture(_texTitle, &_rTitle);
        }
        _txtb_width.Render();
        _txtb_height.Render();
        _btn_ok.Render();
        _btn_abb.Render();
        rh->rect(&_rDialog, 3, BLACK);
    }
}

void SizeDialog::Update() {
}

int SizeDialog::getHeight() {
    return _height;
}

int SizeDialog::getWidth() {
    return _width;
}

Point SizeDialog::getInput() {
    return {_width, _height};
}

bool SizeDialog::isDone() const {
    return _takeNewValues;
}


SizeDialog::~SizeDialog() {
    SDL_DestroyTexture(_texTitle);
}

void SizeDialog::reset() {
    _takeNewValues = false;
}



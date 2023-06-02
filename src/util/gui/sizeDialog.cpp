//
// Created by banoodle on 22.04.23.
//

#include "sizeDialog.h"

void SizeDialog::set(int width, int height) {
    _width = width;
    _height = height;
    iniValues();
    iniUI();
}


void SizeDialog::iniValues() {
    _txtb_width.setNumber(_width);
    _txtb_height.setNumber(_height);
}

void SizeDialog::iniUI() {
    _rDialog = {windowSize.x / 2 - 250, windowSize.y / 2 - 200, 500, 400};
    // Title
    _texTitle = t_cache->getText("Ändere die Größe der Map", 30, &_rTitle);
    // Align Buttons
    int btnY = _rDialog.y + _rDialog.h - 50;

    _rTitle.x = _rDialog.x + _rDialog.w / 2 - _rTitle.w / 2;
    _rTitle.y = _rDialog.y + 10;
    _btn_ok.set( "OK", 18, {_rDialog.x + _rDialog.w - 100, btnY, 80, 40});
    _btn_abb.set( "ABBRUCH", 18, {_rDialog.x + 20, btnY, 100, 40});
    _txtb_width.set( "Breite", {_rDialog.x + 20, _rDialog.y + 80}, true);
    _txtb_height.set( "Höhe", {_rDialog.x + 20, _rDialog.y + 160}, true);
}




void SizeDialog::Input() {
    if(focus!= nullptr)
        focus->Input();
    if(focus == nullptr){
    Event event;
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





void SizeDialog::selection(Event event){
        if (event.button.button == SDL_BUTTON_LEFT) {
        if(_txtb_height.fieldSelected(event)){
            _txtb_height.show(&focus);
        }
        if(_txtb_width.fieldSelected(event)){
            _txtb_width.show(&focus);
        }
        if (_btn_ok.clicked(event)) {
            acceptInput();
        }
        if (_btn_abb.clicked(event)) {
            releaseFocus();
        }
    }
}

void SizeDialog::acceptInput() {
    releaseFocus();
    _width= _txtb_width.getNumber();
    _height= _txtb_height.getNumber();
    _takeNewValues = true;
}

void SizeDialog::Render() {
    if(dialog){
        t_cache->renderFillRect(&_rDialog,EDITOR_UI_BG);
        t_cache->render(_texTitle,&_rTitle);
        _txtb_width.Render();
        _txtb_height.Render();
        _btn_ok.draw();
        _btn_abb.draw();
    }
}

void SizeDialog::Update() {
}

int SizeDialog::getHeight() {
    return _height ;
}

int SizeDialog::getWidth() {
    return _width;
}

Point SizeDialog::getInput(){
    return {_width, _height};
}

bool SizeDialog::isDone() const{
    return _takeNewValues;
}


SizeDialog::~SizeDialog() {
    SDL_DestroyTexture(_texTitle);
}

void SizeDialog::reset(){
    _takeNewValues=false;
}
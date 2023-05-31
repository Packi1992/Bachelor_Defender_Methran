//
// Created by banoodle on 22.04.23.
//

#include "SizeDialog.h"

SizeDialog::SizeDialog() {
    iniUI();
    iniValues();
}



void SizeDialog::iniValues() {
    txtb_width.setNumber(_width);
    txtb_height.setNumber(_height);
}

bool SizeDialog::show() {

    if (takeNewValues) {
        *return_width = _width;
        *return_height = _height;
        return true;
    }
    return false;
}

void SizeDialog::iniUI() {
    rDialog = {windowSize.x / 2 - 250, windowSize.y / 2 - 200, 500, 400};
// Title
    texInfo = t_cache->getText("Ändere die Größe der Map", 30, &rInfo);
// Align Buttons
    int btnY = rDialog.y + rDialog.h - 50;

    rInfo.x = rDialog.x + rDialog.w / 2 - rInfo.w / 2;
    rInfo.y = rDialog.y + 10;
    btn_ok.set( "OK", 18, {rDialog.x + rDialog.w - 100, btnY, 80, 40});
    btn_abb.set( "ABBRUCH", 18, {rDialog.x + 20, btnY, 100, 40});
    txtb_width.set( "Breite", {rDialog.x + 20, rDialog.y + 80}, true);
    txtb_height.set( "Höhe", {rDialog.x + 20, rDialog.y + 160}, true);
}

SizeDialog::~SizeDialog() {
    SDL_DestroyTexture(texInfo);
}

int SizeDialog::getHeight() {
    return _height ;
}

int SizeDialog::getWidth() {
    return _width;
}

void SizeDialog::Render() {
    if(dialog){
        t_cache->renderFillRect(&rDialog,EDITOR_UI_BG);
        t_cache->render(texInfo,&rInfo);
        txtb_width.Render();
        txtb_height.Render();
        btn_ok.draw();
        btn_abb.draw();
    }
}

void SizeDialog::Input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    txtb_height.fieldSelected(event);
                    txtb_width.fieldSelected(event);
                    if (btn_ok.clicked(event)) {
                        dialog = false;
                        _width = txtb_width.getNumber();
                        _height = txtb_height.getNumber();
                        takeNewValues = true;
                    }
                    if (btn_abb.clicked(event)) {
                        dialog = false;
                    }
                }
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_ESCAPE:
                        dialog = false;
                        break;
                    case SDL_SCANCODE_KP_ENTER:
                        dialog = false;
                        _width = txtb_width.getNumber();
                        _height = txtb_height.getNumber();
                        takeNewValues = true;
                        break;
                    default:
                        break;

                }
        }
    }
}

void SizeDialog::Update() {

}

void SizeDialog::set(int width, int height) {

}


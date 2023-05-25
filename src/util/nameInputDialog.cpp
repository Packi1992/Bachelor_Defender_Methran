//
// Created by banoodle on 24.05.23.
//
#include "nameInputDialog.h"

void NameInputDialog::inputs() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    txtb_input.fieldSelected(event);
                    if (btn_ok.clicked(event)) {
                        dialog = false;
                        inputText = txtb_input.getText();
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
                        inputText = txtb_input.getText();
                        takeNewValues = true;
                        break;
                    default:
                        break;
                }
        }
    }
}

void NameInputDialog::iniValues() {
    txtb_input.setText("neueMap");
}

void NameInputDialog::iniUI() {

    rDialog = {wSize.x / 2 - 250, wSize.y / 2 - 200, 500, 250};
// Title
    texInfo = t_cache->getText("Gib einen Namen für die Map ein", 30, {0, 0, 0, 255}, &rInfo);
// Align Buttons
    int btnY = rDialog.y + rDialog.h - 50;

    rInfo.x = rDialog.x + rDialog.w / 2 - rInfo.w / 2;
    rInfo.y = rDialog.y + 10;
    btn_ok.set( "OK", 18, {rDialog.x + rDialog.w - 100, btnY, 80, 40});
    btn_abb.set( "ABBRUCH", 18, {rDialog.x + 20, btnY, 100, 40});
    txtb_input.set( "Name", rDialog.x + 20, rDialog.y + 80, false);
}

std::string NameInputDialog::getInput() {
    return std::string();
}

bool NameInputDialog::show() {
    while (dialog) {
        t_cache->drawBackground(BG);
        t_cache->setRenderColor(EDITOR_UI_BG);
        SDL_RenderFillRect(render, &rDialog);
        SDL_RenderCopy(render, texInfo, nullptr, &rInfo);
        txtb_input.draw();
        btn_ok.draw();
        btn_abb.draw();
        SDL_RenderPresent(render);
        inputs();
    }
    if (takeNewValues) {
        *returnTxt = inputText;
        return true;
    }
    return false;
}

NameInputDialog::~NameInputDialog() {
    SDL_DestroyTexture(texInfo);
}

void NameInputDialog::set(Point winSize, std::string text, int maxSize, std::string *returnText) {
    this->wSize = winSize;
    this->size = maxSize;
    this->iniInput = std::move(text);
    this->inputText = std::move(text);
    this->returnTxt = returnText;
    iniUI();
    iniValues();
}


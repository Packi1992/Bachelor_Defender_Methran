//
// Created by banoodle on 22.04.23.
//

#include "SizeDialog.h"

SizeDialog::SizeDialog(Global *pGlobal, int &width, int &height) {
    this->pGlobal = pGlobal;
    this->width = width;
    this->height = height;

    this->return_height = &height;
    this->return_width = &width;

    iniUI();
    iniValues();
}

void SizeDialog::iniValues() {
    txtb_width->setNumber(width);
    txtb_height->setNumber(height);
}

bool SizeDialog::show() {
    while (dialog && !pGlobal->closeWindow) {
        Color::set(pGlobal->renderer, Color::UIBG);
        SDL_RenderFillRect(pGlobal->renderer, &rDialog);
        SDL_RenderCopy(pGlobal->renderer, texInfo, nullptr, &rInfo);
        txtb_width->draw();
        txtb_height->draw();
        btn_ok.draw();
        btn_abb.draw();
        std::cout << "Render Dialog" << std::endl;
        SDL_RenderPresent(pGlobal->renderer);
        inputs();
    }
    if (takeNewValues) {
        *return_width = width;
        *return_height = height;
        return true;
    }
    return false;
}

void SizeDialog::iniUI() {
    rDialog = {pGlobal->width / 2 - 250, pGlobal->height / 2 - 200, 500, 400};
// Title
    texInfo = pGlobal->textures->getText("Ändere die Größe der Map", 30, {0, 0, 0, 255}, &rInfo);
// Align Buttons
    int btnY = rDialog.y + rDialog.h - 50;

    rInfo.x = rDialog.x + rDialog.w / 2 - rInfo.w / 2;
    rInfo.y = rDialog.y + 10;
    btn_ok.set(pGlobal, "OK", 18, {rDialog.x + rDialog.w - 100, btnY, 80, 40});
    btn_abb.set(pGlobal, "ABBRUCH", 18, {rDialog.x + 20, btnY, 100, 40});
    txtb_width = new TextBox(pGlobal, "Breite", rDialog.x + 20, rDialog.y + 80, true);
    txtb_height = new TextBox(pGlobal, "Höhe", rDialog.x + 20, rDialog.y + 160, true);
}

void SizeDialog::inputs() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    txtb_height->fieldSelected(event);
                    txtb_width->fieldSelected(event);
                    if (btn_ok.clicked(event)) {
                        dialog = false;
                        width = txtb_width->getNumber();
                        height = txtb_height->getNumber();
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
                        width = txtb_width->getNumber();
                        height = txtb_height->getNumber();
                        takeNewValues = true;
                        break;
                    default:
                        break;

                }
        }
    }
}

SizeDialog::~SizeDialog() {
    delete txtb_height;
    delete txtb_width;
    SDL_DestroyTexture(texInfo);
}


//
// Created by banoodle on 22.04.23.
//

#ifndef BOULDERDASH_SIZEDIALOG_H
#define BOULDERDASH_SIZEDIALOG_H


#include "../Global.h"
#include "TextBox.h"
#include "Button.h"

class SizeDialog {
public:
    SizeDialog(Global *pGlobal, int &width, int &height);
    ~SizeDialog();
    bool show();

private:
    void iniUI();

    void iniValues();

    void inputs();

    int *return_width = nullptr;
    int *return_height = nullptr;
    int width;
    int height;
    Global *pGlobal = nullptr;
    SDL_Rect rDialog{};
    SDL_Rect rInfo{};
    SDL_Texture *texInfo = nullptr;
    TextBox *txtb_width = nullptr;
    TextBox *txtb_height = nullptr;
    Button btn_ok;
    Button btn_abb;
    bool takeNewValues = false;
    bool dialog = true;

};


#endif //BOULDERDASH_SIZEDIALOG_H

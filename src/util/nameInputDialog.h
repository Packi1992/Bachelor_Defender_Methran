//
// Created by banoodle on 24.05.23.
//

#ifndef SDL_BACHELORDEFENDER_NAMEINPUTDIALOG_H
#define SDL_BACHELORDEFENDER_NAMEINPUTDIALOG_H

#include <string>
#include "../gamebase.h"
#include "textbox.h"

class NameInputDialog {
public:
    void set(Point winSize, std::string text, int maxSize, std::string *returnText);
    ~NameInputDialog();
    bool show();
    std::string getInput();

private:
    void iniUI();

    void iniValues();

    void inputs();
    Point wSize{};
    SDL_Rect rDialog{};
    SDL_Rect rInfo{};
    SDL_Texture *texInfo = nullptr;
    Button btn_ok;
    Button btn_abb;
    bool takeNewValues = false;
    bool dialog = true;
    // input handling
    std::string iniInput;
    std::string inputText;
    std::string *returnTxt;
    int size=0;
    TextBox txtb_input{};
};


#endif //SDL_BACHELORDEFENDER_NAMEINPUTDIALOG_H

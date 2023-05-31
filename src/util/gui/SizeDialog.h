//
// Created by banoodle on 22.04.23.
//

#ifndef BOULDERDASH_SIZEDIALOG_H
#define BOULDERDASH_SIZEDIALOG_H


#include "../../gamebase.h"
#include "textbox.h"
#include "Button.h"

class SizeDialog: public Gui{
public:
    SizeDialog();
    ~SizeDialog();
    void Render() override;
    void Input() override;
    void Update() override;
    bool show();
    int getHeight();
    int getWidth();

private:
    void iniUI();

    void iniValues();

    void inputs();

    int *return_width = nullptr;
    int *return_height = nullptr;
    int _width;
    int _height;
    Rect rDialog{};
    Rect rInfo{};
    Texture *texInfo = nullptr;
    TextBox *txtb_width = nullptr;
    TextBox *txtb_height = nullptr;
    Button btn_ok;
    Button btn_abb;
    bool takeNewValues = false;
    bool dialog = true;

};


#endif //BOULDERDASH_SIZEDIALOG_H

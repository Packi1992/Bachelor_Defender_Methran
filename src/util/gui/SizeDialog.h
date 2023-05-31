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
    void set(int width, int height);
    ~SizeDialog();
    void Render() override;
    void Input() override;
    void Update() override;
    int getHeight();
    int getWidth();

private:
    void iniUI();

    void iniValues();

    int _width=0;
    int _height=0;
    Rect rDialog{};
    Rect rInfo{};
    Texture *texInfo = nullptr;
    TextBox txtb_width;
    TextBox txtb_height;
    Button btn_ok;
    Button btn_abb;
    bool takeNewValues = false;
    bool dialog = true;

};


#endif //BOULDERDASH_SIZEDIALOG_H

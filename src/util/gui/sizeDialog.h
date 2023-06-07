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
    void set(int width, int height);
    ~SizeDialog();
    // read values
    int getHeight();
    int getWidth();
    Point getInput();

    void Input() override;
    void Render() override;
    void Update() override;

    [[nodiscard]] bool isDone() const;

    void reset();

private:
    void iniUI();
    void iniValues();

    // _dialog dest
    Rect _rDialog{};

    // title
    Rect _rTitle{};
    Texture *_texTitle{};

    // buttons
    Button _btn_ok;
    Button _btn_abb;

    // Input handling
    Gui *focus{};
    int _width=0;
    int _height=0;
    TextBox _txtb_width;
    TextBox _txtb_height;

    bool _takeNewValues = false;

    void handleEvent(Event event);
    void selection(Event event);
    void acceptInput();
};


#endif //BOULDERDASH_SIZEDIALOG_H

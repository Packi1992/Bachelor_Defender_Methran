//
// Created by banoodle on 24.05.23.
//

#ifndef SDL_BACHELORDEFENDER_INPUTDIALOG_H
#define SDL_BACHELORDEFENDER_INPUTDIALOG_H

#include <string>
#include "textbox.h"
#include "Button.h"

class InputDialog: public Gui {
public:
    void set(string title, const string& fieldName, string inputIniVal ="", int buffSize=50);
    ~InputDialog();
    // read value
    string getInput();

    void Input() override;
    void Render() override;
    void Update() override;
    bool isDone() const;

    void reset();

private:
    void iniUI(const string& fieldName);
    void iniValues();

    bool _takeNewValues = false;

    // _dialog dest
    Rect _rDialog{};

    // title
    string _title;
    Rect _rTitle{};
    Texture *_texTitle = nullptr;

    // buttons
    Button _btn_ok;
    Button _btn_abb;

    // input handling
    Gui *focus{};
    string _input;
    int _buffSize=0;
    TextBox _textBox{};
    void selection(Event event);
    void acceptInput();
};
#endif //SDL_BACHELORDEFENDER_INPUTDIALOG_H

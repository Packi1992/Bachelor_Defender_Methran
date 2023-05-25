//
// Created by banoodle on 24.05.23.
//

#ifndef SDL_BACHELORDEFENDER_GUI_SELECTOR_H
#define SDL_BACHELORDEFENDER_GUI_SELECTOR_H
#include <vector>
#include "../gamebase.h"
#include <iostream>
#include <filesystem>
#include "Button.h"

class GuiSelector {
public:
    void set(Point wSize, std::string path, std::string ending);
    void show();

    std::string getSelectedFile();

    bool isFileSelected();
    void Render();

private:
    void collectFiles();
    Point wSize;
    void createButtons();
    std::string _path;
    std::string _ending;
    std::vector<std::string> maps;
    std::vector<Button*> buttons;
    bool showSelector=true;
    bool fileSelected=false;
    bool mapSelected=false;
    void Input();
    std::string selectedFile;

    //std::vector<shared_ptr
};



#endif //SDL_BACHELORDEFENDER_GUI_SELECTOR_H

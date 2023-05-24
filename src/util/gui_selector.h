//
// Created by banoodle on 24.05.23.
//

#ifndef SDL_BACHELORDEFENDER_GUI_SELECTOR_H
#define SDL_BACHELORDEFENDER_GUI_SELECTOR_H
#include <vector>
#include "../gamebase.h"
#include "Button.h"

class GuiSelector {
public:
    void set(Renderer *pRender, std::string path, std::string ending);
    void show();

    std::string getSelectedFile();

    bool isFileSelected();
    void Events();
    void Update();
    void Render();

private:
    void collectFiles();
    void createButtons();
    Renderer *_render= nullptr;
    TextureCache *t_cache = nullptr;
    std::string _path;
    std::string _ending;
    std::vector<std::string> maps;
    std::vector<Button*> buttons;
    bool showSelector=true;
    bool fileSelected=false;
    std::string selectedFile;

    //std::vector<shared_ptr
};



#endif //SDL_BACHELORDEFENDER_GUI_SELECTOR_H

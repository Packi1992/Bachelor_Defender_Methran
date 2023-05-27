//
// Created by banoodle on 24.05.23.
//
#include "selectorDialog.h"

void SelectorDialog::createButtons() {
    Point size = pGame->GetWindowSize();
    int width = (int)(size.x*0.8);
    int x = (int)(size.x*0.1);
    SDL_Rect bRect{x, 100, width, 80};
    for (const auto &mapName: maps) {
        Button* nb = new Button();
        nb->set(mapName, 18, bRect);
        buttons.push_back(nb);
        bRect.y += 120;
    }
}

void SelectorDialog::set(string path, string ending) {
    _path = std::move(path);
    _ending = std::move(ending);

    collectFiles();
    createButtons();
}

std::string SelectorDialog::getSelectedFile() {
    return _path+selectedFile+_ending;
}

void SelectorDialog::collectFiles() {
    int eSize = _ending.length();
    for (const auto &entry: std::filesystem::directory_iterator(_path)) {
        std::string newPath = entry.path().c_str();
        if (newPath.substr(newPath.length() - eSize, eSize) == _ending) {
            maps.push_back(newPath.substr(8, newPath.length() - 12));
        }
    }
}

void SelectorDialog::Render() {
    if (dialog) {
        t_cache->drawBackground(BG);
        for(auto & button : buttons){
            button->draw();
        }
    }
}

bool SelectorDialog::isFileSelected() const {
    return fileSelected;
}

void SelectorDialog::Input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE)tidyUp();
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)tidyUp();
                break;
            case SDL_MOUSEMOTION:
                for (auto btn: buttons) {
                    btn->entered(event);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    for (auto btn: buttons) {
                        if (btn->clicked(event)) {
                            fileSelected = true;
                            selectedFile = btn->getText();
                            tidyUp();
                        }
                    }
                }
        }
    }
}

void SelectorDialog::Update() {

}

SelectorDialog::~SelectorDialog(){
    for (auto btn: buttons) {
        delete(btn);
    }
}

void SelectorDialog::tidyUp() {
    dialog = false;
    releaseFocus();
    for (auto btn: buttons) {
        delete(btn);
    }
    buttons.clear();
    maps.clear();
}




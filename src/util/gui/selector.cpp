//
// Created by banoodle on 24.05.23.
//
#include "selector.h"

void Selector::createButtons() {
    SDL_Rect bRect{200, 100, wSize.x - 400, 80};
    for (const auto &mapName: maps) {
        Button* nb = new Button();
        nb->set(mapName, 18, bRect);
        buttons.push_back(nb);
        bRect.y += 120;
    }
}

void Selector::set(Point wSize, std::string path, std::string ending) {
    _path = std::move(path);
    _ending = std::move(ending);
    this->wSize = wSize;
    collectFiles();
    createButtons();
}

std::string Selector::getSelectedFile() {
    return selectedFile;
}

void Selector::collectFiles() {
    int eSize = _ending.length();
    for (const auto &entry: std::filesystem::directory_iterator(_path)) {
        std::string newPath = entry.path().c_str();
        if (newPath.substr(newPath.length() - eSize, eSize) == _ending) {
            maps.push_back(newPath.substr(8, newPath.length() - 12));
        }
    }
}

void Selector::Render() {
    if (showSelector) {
        t_cache->drawBackground(BG);
        for(auto & button : buttons){
            button->draw();
        }
    }
}

void Selector::show(Gui **pFocus) {
    focus = pFocus;
    showSelector = true;
}

bool Selector::isFileSelected() const {
    return fileSelected;
}

void Selector::Input() {
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

void Selector::Update() {

}

void Selector::setFocus(Gui *next) {
    last = next;
}

Selector::~Selector(){
    for (auto btn: buttons) {
        delete(btn);
    }
}

void Selector::tidyUp() {
    showSelector = false;
    *focus = last;
    for (auto btn: buttons) {
        delete(btn);
    }
    buttons.clear();
    maps.clear();
}





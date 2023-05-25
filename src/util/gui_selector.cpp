//
// Created by banoodle on 24.05.23.
//
#include "gui_selector.h"

#include <utility>

void GuiSelector::createButtons() {
    SDL_Rect bRect{200, 100, wSize.x - 400, 80};
    for (const auto &mapName: maps) {
        Button *nb = new Button();
        nb->set(mapName, 18, bRect);
        buttons.push_back(nb);
        bRect.y += 120;
    }
}

void GuiSelector::set(Point wSize, std::string path, std::string ending) {
    _path = std::move(path);
    _ending = std::move(ending);
    this->wSize = wSize;
    collectFiles();
    createButtons();
}

std::string GuiSelector::getSelectedFile() {
    return std::string();
}

void GuiSelector::collectFiles() {
    int eSize = _ending.length();
    for (const auto &entry: std::filesystem::directory_iterator(_path)) {
        std::string newPath = entry.path().c_str();
        if (newPath.substr(newPath.length() - eSize, eSize) == _ending) {
            maps.push_back(newPath.substr(8, newPath.length() - 12));
        }
    }
}

void GuiSelector::Render() {
    while (!fileSelected && showSelector) {
        t_cache->drawBackground(BLACK);
        for (Button *btn: buttons) {
            btn->draw();
        }
    }
}

void GuiSelector::show() {
    while (!mapSelected && showSelector) {
        t_cache->drawBackground(WHITE);
        for (Button *btn: buttons) {
            btn->draw();
        }
        SDL_RenderPresent(render);
        Input();
    }
}

bool GuiSelector::isFileSelected() {
    return mapSelected;
}

void GuiSelector::Input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                    showSelector = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_ESCAPE:
                        showSelector = false;
                    default:
                        break;
                }
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
                            mapSelected = true;
                            selectedFile = btn->getText();
                        }
                    }
                }
        }
    }
}





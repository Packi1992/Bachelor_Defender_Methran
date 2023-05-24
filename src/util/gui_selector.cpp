//
// Created by banoodle on 24.05.23.
//
#include "gui_selector.h"

#include <utility>

void GuiSelector::createButtons() {



}

void GuiSelector::set(Renderer *pRender, std::string path, std::string ending) {
    _render = pRender;
    _path =std::move(path);
    _ending = std::move(ending);
    t_cache = TextureCache::getCache(_render);
    collectFiles();
    createButtons();
}

std::string GuiSelector::getSelectedFile() {
    return std::string();
}

void GuiSelector::collectFiles() {

}

void GuiSelector::Render() {
    while(!fileSelected && showSelector){
        t_cache->drawBackground(BLACK);
        for (Button* btn: buttons) {
            btn->draw();
        }
    }
}

void GuiSelector::show() {

}

bool GuiSelector::isFileSelected() {
    return false;
}

void GuiSelector::Events() {

}

void GuiSelector::Update() {

}





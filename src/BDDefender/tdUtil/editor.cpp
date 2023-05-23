//
// Created by banoodle on 23.05.23.
//
#include "editor.h"

void Editor::Init() {
    GameState::Init();
    tcache = TextureCache::getCache(render);
    map.set(render, &offset);
}

void Editor::Events(const u32 frame, const u32 totalMSec, const float deltaT) {

}

void Editor::UnInit() {
    GameState::UnInit();
}

void Editor::Update(const u32 frame, const u32 totalMSec, const float deltaT) {

}

void Editor::Render(const u32 frame, const u32 totalMSec, const float deltaT) {
    map.draw(true);
}


//
// Created by banoodle on 14.05.23.
//
#include "testtd.h"

void TestTD::Init() {
    GameState::Init();
    map.set(&offset);
}

void TestTD::UnInit() {
    GameState::UnInit();
}

void TestTD::Render(const u32 frame, const u32 totalMSec, const float deltaT) {
    map.draw(true);
}

void TestTD::Events(const u32 frame, const u32 totalMSec, const float deltaT) {

}

void TestTD::Update(const u32 frame, const u32 totalMSec, const float deltaT) {

}

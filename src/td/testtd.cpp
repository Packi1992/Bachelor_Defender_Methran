//
// Created by banoodle on 14.05.23.
//
#include "testtd.h"

void TestTD::Init() {
    GameState::Init();
    pGame = &game;
    map.set(&offset);
    _ph.set(&map);
    _prh.set(&map);
}

void TestTD::UnInit() {
    GameState::UnInit();
}

void TestTD::Render(const u32 frame, const u32 totalMSec, const float deltaT) {
    t_cache->drawBackground(BG);
    map.draw(true);
    _ph.Render(frame, totalMSec, deltaT);
    _prh.Render(frame, totalMSec, deltaT);
}

void TestTD::Update(const u32 frame, const u32 totalMSec, const float deltaT) {
        ProjectilesHandler::Projectile p;
        p._type = ProjectilesHandler::Projectile::ARROW;
        p._direction = totalMSec % 360;
        p._position = map.getPosOnScreen({8, 4}) + offset;
        p._speed = 60;
        _ph.add(p);
        _ph.move();
        ParticlesHandler::Particles pa;
        pa._type = ParticlesHandler::Particles::FFIRE;
        pa._direction = totalMSec % 360;
        pa._position = map.getPosOnScreen({8, 4}) + offset;
        pa._speed = 60;
        pa._moveable = true;
        pa._ttl = 80;
        _prh.add(pa);
        _prh.move();
}

void TestTD::Events(const u32 frame, const u32 totalMSec, const float deltaT) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                    game.SetNextState(99);
                break;
            case SDL_MOUSEBUTTONDOWN:
                MouseDown(event);
                break;
            case SDL_MOUSEBUTTONUP:
                mbDown = false;
                if (event.button.button == SDL_BUTTON_RIGHT && mouseScroll)mouseScroll = false;
                break;
            case SDL_MOUSEMOTION:
                MouseMotion(event);
                break;
            case SDL_MOUSEWHEEL:
                MouseWheel(event);
                break;
            case SDL_KEYDOWN:
                keyDown(event);
                break;
        }
    }
}

void TestTD::MouseDown(SDL_Event event) {
    if (event.button.button == SDL_BUTTON_RIGHT) {
        mouseScroll = true;
    }
}

void TestTD::MouseMotion(SDL_Event event) {
    if (mouseScroll) {
        offset.x -= event.motion.xrel;
        offset.y -= event.motion.yrel;
    }
}

void TestTD::MouseWheel(SDL_Event event) {
    map.scale += event.wheel.y;
    int posX,posY;
    SDL_GetMouseState(&posX, &posY);
    offset.y += 2*event.wheel.y / abs(event.wheel.y) * map.height / 2;
    offset.x += 2*event.wheel.y / abs(event.wheel.y) * map.width / 2;
}

void TestTD::keyDown(SDL_Event event) {
    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_ESCAPE:
            game.SetNextState(0);
            break;
        case SDL_SCANCODE_D:
        case SDL_SCANCODE_RIGHT:
            offset.x += 20;
            break;
        case SDL_SCANCODE_A:
        case SDL_SCANCODE_LEFT:
            offset.x -= 20;
            break;
        case SDL_SCANCODE_W:
        case SDL_SCANCODE_UP:
            offset.y -= 20;
            break;
        case SDL_SCANCODE_S:
        case SDL_SCANCODE_DOWN:
            offset.y += 20;
        default:
            break;
    }
}

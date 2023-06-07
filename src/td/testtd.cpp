//
// Created by banoodle on 14.05.23.
//
#include "testtd.h"

void TestTD::Init() {
    GameState::Init();
    pGame = &game;
    pMap = &_map;
    _map.load();
    _ph.set();
}

void TestTD::UnInit() {
    GameState::UnInit();
    _eh.UnInit();
}

void TestTD::Render(u32 frame,  u32 totalMSec, float deltaT) {
    t_cache->drawBackground(BG);
    _map.Render(true);
    _ph.Render(frame, totalMSec, deltaT);
    _eh.Render();
}

void TestTD::Update(const u32 frame, const u32 totalMSec, const float deltaT) {
    // add projektiles and particles
    ProjectilesHandler::Projectile p;
    p._type = Projectile::ARROW;
    p._direction = totalMSec % 360;
    p._position = Map::getPosOnScreen({ 8, 4 }) + offset;
    p._speed = 60;
    _ph.add(p);
    p._type = ProjectilesHandler::Projectile::FFIRE;
    p._direction = totalMSec % 360;
    p._position = Map::getPosOnScreen({ 8, 4 }) + offset;
    p._speed = 60;
    p._moveable = true;
    p._ttl = 80;
    _ph.add(p);

    // add enemy
    if (totalMSec % 100 == 0) {
        Enemy e;
        e.setEnemy({ 0, 0 }, 1000, 100);
        _eh.addEnemy(e);
    }
    _eh.Update();
    _ph.move();
    collision();
}

void TestTD::collision() {
    for (auto& e : _eh._enemies) {
        if (e._alive) {
            for (auto& p : _ph._projectiles) {
                if (p._alive) {
                    // Collision Detection not implemented yet, perhaps with SDL_intersectRect
                    if (e.isPointInside(p._position)) {
                        e.takeDamage(p._damage);
                        _ph.remove(p);
                        if (!e._alive) {
                            break;
                        }
                    }
                }
            }
        }
    }
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
    Point cursor{};
    SDL_GetMouseState(&cursor.x, &cursor.y);
    if(event.wheel.y/abs(event.wheel.y)<1){// zoom out
        scale = scale * 0.8;
    }
    else{                                     // zoom in
        scale = scale * (1/0.8);
        offset.y += 2 * event.wheel.y / abs(event.wheel.y) * _map._height / 2;
        offset.x += 2 * event.wheel.y / abs(event.wheel.y) * _map._width / 2;
    }
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
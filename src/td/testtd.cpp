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
    _prh.set();
}

void TestTD::UnInit() {
    GameState::UnInit();
    _eh.UnInit();
}

void TestTD::Render(u32 frame,  u32 totalMSec, float deltaT) {
    t_cache->drawBackground(BG);
    _map.Render(true);
    _ph.Render(frame, totalMSec, deltaT);
    _prh.Render(frame, totalMSec, deltaT);
    _eh.Render();
}

void TestTD::Update(const u32 frame, const u32 totalMSec, const float deltaT) {
    // add projektiles and particles
    ProjectilesHandler::Projectile p;
    ParticlesHandler::Particles pa;
    p._type = Projectile::ARROW;
    p._direction = totalMSec % 360;
    p._position = Map::getPosOnScreen({ 8, 4 }) + offset;
    p._speed = 60;
    _ph.add(p);
    pa._type = ParticlesHandler::Particles::FFIRE;
    pa._direction = totalMSec % 360;
    pa._position = Map::getPosOnScreen({ 8, 4 }) + offset;
    pa._speed = 60;
    pa._moveable = true;
    pa._ttl = 80;
    _prh.add(pa);

    // add enemy
    static int y = 0;
    Enemy e;
    e.setEnemy({ y % 2, y }, 1000, 100);
    _eh.addEnemy(e);
    y++;
    if (y == 8)
        y = 0;
    _eh.Update();
    _prh.move();
    _ph.move();

    // Look for collision to any given Enemey, added Damagenumber to Projectile
    for (auto& e : _eh._enemies) {
        Rect en = { e._pos.x,e._pos.y,scale,scale+scale };
        // First take a look at the projectiles
        for (auto& p : _ph._projectiles) {
            if (p._type != Projectile::DISABLED) {
                Rect pro = { p._position.x,p._position.y,p._size,p._size };
                // Collision Detection not implemented yet, perhaps with SDL_intersectRect
                if (SDL_HasIntersection(&en,&pro)) {
                    e.takeDamage(p._damage);
                    _ph.remove(p);
                }
            }
        }
        // Then at the particles
        for (auto& p : _prh._particles) {
            if (p._type != Particles::DISABLED) {
                Rect par = { p._position.x,p._position.y,p._size,p._size };
                // Collision Detection not implemented yet
                if (SDL_HasIntersection(&en, &par)) {
                    e.takeDamage(p._damage);
                    _prh.remove(p);
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
    scale += event.wheel.y;
    int posX,posY;
    SDL_GetMouseState(&posX, &posY);
    offset.y += 2 * event.wheel.y / abs(event.wheel.y) * _map._height / 2;
    offset.x += 2 * event.wheel.y / abs(event.wheel.y) * _map._width / 2;
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
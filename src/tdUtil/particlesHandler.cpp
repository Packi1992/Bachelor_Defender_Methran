//
// Created by dex on 5/26/23.
//

#include "particlesHandler.h"
void ParticlesHandler::set(Map *m) {
    _map = m;
    this->_texture = t_cache->getTexture("../asset/graphic/td/tileTD.png");
}

void ParticlesHandler::Render(const u32 frame, const u32 totalMSec, const float deltaT) {
    for (auto &p: _particles) {
        if (p._alive) {
            int y = p._position.y - _map->offset->y;
            int x = p._position.x - _map->offset->x;
            int size = (int) ((float) _map->scale * (float) p._size / 100.0f);
            Rect dstRect = {x, y, size, size};
            /*if (!(x + _map->offset->x+ size > 0 && x + _map->offset->x < _map->width * _map->scale) ||
                !(y + _map->offset->y+ size > 0 && y + _map->offset->y < _map->height * _map->scale)) {
                continue;
            }*/
            t_cache->render(this->_texture, &dstRect, p._direction, TdTileHandler::getSrcRect(p._type,_map->getMapTime()));
        }
    }
}

void ParticlesHandler::add(ParticlesHandler::Particles p) {
    for (int i = 0; i < MAXPARTICLES; i++) {
        if (!_particles[i]._alive) {
            _particles[i] = p;
            _particles[i]._alive = true;
            return;
        }
    }
    if (overflow >= MAXPARTICLES)
        overflow = 0;
    _particles[overflow] = p;
    _particles[overflow++]._alive = true;
}

void ParticlesHandler::move() {
    for (int i = 0; i < MAXPARTICLES; i++) {
        if (_particles[i]._alive) {
            switch (_particles[i]._type) {
                case (Particles::Type::BASEEXPLOSION):
                    break;
                case (Particles::Type::FFIRE):
                    if(_particles[i]._moveable)
                        moveFFire(&_particles[i]);
                    break;
                default:
                    cout << "Projectile Move-Error: Projectile not valid: " << _particles[i]._type << endl;
            }
        }
        //checking if Projectile still alive?
        if(_particles[i]._ttl > 0)
            _particles[i]._ttl --;
        else
            _particles[i]._alive = false;
    }
}

void ParticlesHandler::moveFFire(ParticlesHandler::Particles *p) {
    if(p->_ttl < 30)
        p->_moveable = false;
    float speed = (float)p->_speed / 500.0f;
    float direction = (float)(p->_direction % 360) / 180.0f * M_PI;
    if (_map == nullptr) {
        cerr << "ProjectilesHandler needs a valid Mappointer" << endl;
    }
    speed *= _map->scale;
    p->_position.x += sin(direction) * speed;
    p->_position.y += cos(direction) * speed;
}
//
// Created by dex on 5/26/23.
//

#include "particlesHandler.h"

void ParticlesHandler::set() {
    this->_texture = t_cache->get(BasePath "asset/graphic/td/tileTD.png");
}

void ParticlesHandler::Render(const u32 frame, const u32 totalMSec, const float deltaT) {
    for (auto &p: _particles) {
        Point pos = p._position - offset;
        int size = (int) ((float) scale * (float) p._size / 100.0f);
        if (p._alive && onScreen(pos,size)) {
            Rect dstRect = {pos.x, pos.y, size, size};
            t_cache->render(this->_texture, &dstRect, p._direction,
                            TdTileHandler::getSrcRect(p._type, totalMSec));
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

void ParticlesHandler::remove(Particles &p) {
    return;
}

void ParticlesHandler::move() {
    for (int i = 0; i < MAXPARTICLES; i++) {
        if (_particles[i]._alive) {
            switch (_particles[i]._type) {
                case (Particles::Type::BASEEXPLOSION):
                    break;
                case (Particles::Type::FFIRE):
                    if (_particles[i]._moveable)
                        moveFFire(&_particles[i]);
                    break;
                default:
                    cout << "Projectile Move-Error: Projectile not valid: " << _particles[i]._type << endl;
            }
        }
        //checking if Projectile still alive?
        if (_particles[i]._ttl > 0)
            _particles[i]._ttl--;
        else
            _particles[i]._alive = false;
    }
}

void ParticlesHandler::moveFFire(ParticlesHandler::Particles *p) {
    if (p->_ttl < 30)
        p->_moveable = false;

    auto direction = (float) (((double) (p->_direction % 360) / 180.0f) * M_PI);
    float speed = (float) p->_speed / 500.0f * (float) scale;
    p->_position.x += (int) (sin(direction) * speed);
    p->_position.y += (int) (cos(direction) * speed);
}

bool ParticlesHandler::onScreen(Point &posOnScreen, int &size) {
    return (posOnScreen.x +size > 0)&&              // left
           (posOnScreen.y +size > 0)&&             // top
           (posOnScreen.y < windowSize.y)&&        // bot
           (posOnScreen.x < windowSize.x);         // right
    return true;
}

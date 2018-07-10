#include "particle.h"

Particle::Particle(int size, const ofColor& color, const ofPoint& position, const ofPoint& velocity, float lifeTime)
    : size(size), color(color), position(position), velocity(velocity), lifeTime(lifeTime) {
        time = 0;

        live = true;
}

void Particle::update(float deltaTime) {
    if (live) {
        position += velocity * deltaTime;

        time += deltaTime;

        if (time >= lifeTime)
            live = false;
    }
}

bool Particle::isAlive() const {
    return live;
}

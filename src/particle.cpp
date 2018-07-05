#include "particle.h"

Particle::Particle(const ofPoint& position, const ofPoint& velocity, float lifeTime) {
    this->position = position;
    this->velocity = velocity;

    this->lifeTime = lifeTime;
    time = 0;

    live = true;
}

void Particle::update(float deltaTime) {
    if (live) {
        position += velocity * time;

        time += deltaTime;

        if (time >= lifeTime)
            live = false;
    }
}

void Particle::draw() const {
    if (live) {
        float size = 2;

        ofColor color = ofColor::red;

        ofSetColor(color);

        ofDrawCircle(position, size);
    }
}

bool Particle::isAlive() const {
    return live;
}

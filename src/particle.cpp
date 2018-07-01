#include "particle.h"

Particle::Particle() {
    live = false;
}

// Get a random point in a square by returning relative coordinates to its
// center.
ofPoint randomPointInSquare(const int squareSize) {
    int x = ofRandom(-(squareSize / 2), squareSize / 2);
    int y = ofRandom(-(squareSize / 2), squareSize / 2);

    return ofPoint(x, y);
}

void Particle::setup(const Emitter& emitter) {
    position = emitter.getCenter() + randomPointInSquare(emitter.getSize());

    velocity = emitter.getDirection() * ofRandom(emitter.getMaxVelocity());

    time = 0;
    lifeTime = emitter.getLifeTime();

    live = true;
}

void Particle::update(float d_time) {
    if (live) {
        position += velocity * time;

        time += d_time;

        if (time >= lifeTime)
            live = false;
    }
}

void Particle::draw() {
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

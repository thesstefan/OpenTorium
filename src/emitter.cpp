#include "emitter.h"

Emitter::Emitter() {
    center = ofPoint(ofGetWidth() / 2, ofGetHeight() / 2);

    direction = ofPoint(1, 0, 0);

    maxVelocity = 100.0;
    lifeTime = 1.0;

    size = 200;
}

// Get a random point in a square by returning relative coordinates to its
// center.
ofPoint randomPointInSquare(const int squareSize) {
    int x = ofRandom(-(squareSize / 2), squareSize / 2);
    int y = ofRandom(-(squareSize / 2), squareSize / 2);

    return ofPoint(x, y);
}

Particle Emitter::createParticle() const {
    ofPoint position = center + randomPointInSquare(size);
    ofPoint velocity = direction * ofRandom(1, maxVelocity);

    Particle particle(position, velocity, lifeTime);

    return particle;
}

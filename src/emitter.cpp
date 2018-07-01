#include "emitter.h"

void Emitter::setup() {
    center = ofPoint(ofGetWidth() / 2, ofGetHeight() / 2);

    // Right
    direction = ofPoint(1, 0, 0);

    maxVelocity = 100.0;
    lifeTime = 1.0;

    size = 200;
}

ofPoint Emitter::getCenter() const {
    return center;
}

ofPoint Emitter::getDirection() const {
    return direction;
}

float Emitter::getMaxVelocity() const {
    return maxVelocity;
}

float Emitter::getLifeTime() const {
    return lifeTime;
}

float Emitter::getSize() const {
    return size;
}

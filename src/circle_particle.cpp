#include "circle_particle.h"

CircleParticle::CircleParticle(int size, const ofColor& color, const ofPoint& position, const ofPoint& velocity, int lifeTime)
    : Particle(size, color, position, velocity, lifeTime) {}

void CircleParticle::draw() const {
    if (live) {
        ofSetColor(color);

        ofDrawCircle(position, size);
    }
}

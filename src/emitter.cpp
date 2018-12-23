#include "emitter.h"

Emitter::Emitter(Shape *shape, const ofVec2f &direction, float maxVelocity,
                 float lifeTime, float spawnRate, const ofColor &color) :
    shape(shape), 
    direction(direction), 
    maxVelocity(maxVelocity), 
    lifeTime(lifeTime),
    spawnRate(spawnRate),
    color(color) {

    spawnCount = 0;
}

std::unique_ptr<Particle> Emitter::createParticle(const enum ParticleType &type) const {

    const ofVec2f position = shape->getRandomPoint();
    const ofVec2f velocity = direction * ofRandom(1, maxVelocity);

    const int size = 1;

    return getParticle(type, size, color, position, velocity, lifeTime);
}

void Emitter::draw() const {
    ofPushStyle();

    ofNoFill();
    ofSetColor(ofColor::white);

    shape->draw();

    ofPopStyle();
}

void Emitter::scale(const ofVec2f& screenChangeProportion) {
    shape->scale(screenChangeProportion);
}

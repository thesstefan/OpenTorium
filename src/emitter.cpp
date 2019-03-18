#include "emitter.h"

Emitter::Emitter(Shape *shape, const ofVec2f &direction, float maxVelocity,
                 float lifeTime, float spawnRate, const ofColor &color,
                 float particleSize) :
    shape(shape), 
    direction(direction), 
    maxVelocity(maxVelocity), 
    lifeTime(lifeTime),
    spawnRate(spawnRate),
    color(color),
    particleSize(particleSize) {

    spawnCount = 0;
}

std::unique_ptr<Particle> Emitter::createParticle(const enum ParticleType &type) const {

    const ofVec2f position = shape->getRandomPoint();
    const ofVec2f velocity = direction * ofRandom(1, maxVelocity);

    return getParticle(type, particleSize, color, position, velocity, lifeTime);
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

    direction *= screenChangeProportion;
}

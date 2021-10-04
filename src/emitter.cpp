#include "emitter.h"
#include "misc.h"

Emitter::Emitter(Shape *shape, const ofVec2f &direction, float maxRelativeSpeed,
                 float lifeTime, float spawnRate, const ofColor &color,
                 float relativeParticleSize) :
    shape(shape), 
    direction(direction), 
    maxRelativeSpeed(maxRelativeSpeed), 
    maxSpeed(getScreenScaled(direction.getScaled(maxRelativeSpeed)).length()),
    lifeTime(lifeTime),
    spawnRate(spawnRate),
    color(color),
    relativeParticleSize(relativeParticleSize),
    spawnCount(0) {}

std::unique_ptr<Particle> Emitter::createParticle(const enum ParticleType &type) const {
    const ofVec2f position = shape->getRandomPoint();

    const float speed = ofRandom(maxSpeed / 2, maxSpeed);

    const ofVec2f velocity = direction.getScaled(speed);

    return getParticle(type, relativeParticleSize, color, position, velocity, lifeTime);
}

void Emitter::draw() const {
    ofPushStyle();

    ofNoFill();
    ofSetColor(ofColor::white);

//    shape->draw();

    ofPopStyle();
}

void Emitter::scale(const ofVec2f& screenChangeProportion) {
    shape->scale(screenChangeProportion);

    maxSpeed = getScreenScaled(direction.getScaled(maxRelativeSpeed)).length();

    direction *= screenChangeProportion;
    direction.normalize();
}

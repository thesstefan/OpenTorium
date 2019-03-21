#include "emitter.h"
#include "misc.h"

Emitter::Emitter(Shape *shape, const ofVec2f &direction, float maxRelativeSpeed,
                 float lifeTime, float spawnRate, const ofColor &color,
                 float particleSize) :
    shape(shape), 
    direction(direction), 
    maxRelativeSpeed(maxRelativeSpeed), 
    maxSpeed(getScreenScaled(direction.getScaled(maxRelativeSpeed)).length()),
    lifeTime(lifeTime),
    spawnRate(spawnRate),
    color(color),
    particleSize(particleSize * ofVec2f(ofGetWidth(), ofGetHeight()).length()) {

    spawnCount = 0;
}

std::unique_ptr<Particle> Emitter::createParticle(const enum ParticleType &type) const {
    const ofVec2f position = shape->getRandomPoint();

    const float speed = ofRandom(maxSpeed / 2, maxSpeed);

    const ofVec2f velocity = direction.getScaled(speed);

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

    const ofVec2f screen = ofVec2f(ofGetWidth(), ofGetHeight());
    const ofVec2f oldScreen = screen / screenChangeProportion;

    particleSize *= screen.length() / oldScreen.length();
    particleSize = ofClamp(particleSize, MIN_PARTICLE_SIZE, MAX_PARTICLE_SIZE);

    maxSpeed = getScreenScaled(direction.getScaled(maxRelativeSpeed)).length();

    direction *= screenChangeProportion;
    direction.normalize();
}

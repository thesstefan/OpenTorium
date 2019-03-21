#include "particle.h"

Particle::Particle(float size, const ofColor &color, const ofPoint &position, 
                   const ofVec2f &velocity, float lifeTime, float mass) : 
    size(size), 
    color(color), 
    position(position), 
    velocity(velocity), 
    lifeTime(lifeTime), 
    mass(mass) {
        age = 0;

        live = true;
}

void Particle::update(float deltaTime) {
    if (live) {
        velocity += acceleration * deltaTime;

        acceleration = ofVec2f(0, 0);

        position += velocity * deltaTime;

        age += deltaTime;

        if (age >= lifeTime)
            live = false;
    }
}

bool Particle::isAlive() const {
    return live;
}

ofPoint Particle::getPosition() const {
    return position;
}

ofColor Particle::getColor() const {
    return this->color;
}

void Particle::setColor(const ofColor &color) {
    this->color = color;
}

void Particle::applyForce(const ofPoint &force) {
    acceleration += force / mass;
}

void Particle::scale(const ofVec2f &screenChangeProportion) {
    const ofVec2f screen = ofVec2f(ofGetWidth(), ofGetHeight());
    const ofVec2f oldScreen = screen / screenChangeProportion;

    size *= screen.length() / oldScreen.length();
    size = ofClamp(size, MIN_PARTICLE_SIZE, MAX_PARTICLE_SIZE);

    position *= screenChangeProportion;

    velocity *= screenChangeProportion;
    acceleration *= screenChangeProportion;
}

CircleParticle::CircleParticle(int size, const ofColor &color, const ofPoint &position, 
                               const ofVec2f &velocity, int lifeTime, float mass) :
    Particle(size, color, position, velocity, lifeTime, mass) {}

void CircleParticle::draw() const {
    if (live) {
        ofPushStyle();

        ofSetColor(color);
        ofDrawCircle(position, size);

        ofPopStyle();
    }
}

std::unique_ptr<Particle> getParticle(const enum ParticleType &type,
                                      float size, 
                                      const ofColor &color,
                                      const ofPoint &position,
                                      const ofVec2f &velocity,
                                      float lifeTime) {
    if (type == ParticleType::Circle)
        return std::make_unique<CircleParticle>(size, color, position, velocity, lifeTime);
    else
        throw "Unknown particle type";
}

void Particle::kill() {
    live = false;
}

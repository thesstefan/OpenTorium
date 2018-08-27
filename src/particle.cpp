#include "particle.h"

Particle::Particle(int size, const ofColor &color, const ofPoint &position, 
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

std::unique_ptr<Particle> getParticle(const enum ParticleType &type,
                                      int size, 
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

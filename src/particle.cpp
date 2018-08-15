#include "particle.h"

Particle::Particle(int size, float mass, const ofColor& color, const ofPoint& position, const ofPoint& velocity, float lifeTime)
    : size(size), mass(mass), color(color), position(position), velocity(velocity), lifeTime(lifeTime) {
        time = 0;

        live = true;
}

void Particle::update(float deltaTime) {
    if (live) {
        position += velocity * deltaTime;

        time += deltaTime;

        if (time >= lifeTime)
            live = false;
    }
}

bool Particle::isAlive() const {
    return live;
}

CircleParticle::CircleParticle(int size, float mass, const ofColor& color, const ofPoint& position, const ofPoint& velocity, int lifeTime)
    : Particle(size, mass, color, position, velocity, lifeTime) {}

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

void Particle::setColor(const ofColor& color) {
    this->color = color;
}

void Particle::applyForce(const ofPoint& force, float deltaTime) {
    ofPoint addedVelocity = force * (deltaTime / mass);

    velocity += addedVelocity;
}

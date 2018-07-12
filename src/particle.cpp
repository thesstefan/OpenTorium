#include "particle.h"

Particle::Particle(int size, const ofColor& color, const ofPoint& position, const ofPoint& velocity, float lifeTime)
    : size(size), color(color), position(position), velocity(velocity), lifeTime(lifeTime) {
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

CircleParticle::CircleParticle(int size, const ofColor& color, const ofPoint& position, const ofPoint& velocity, int lifeTime)
    : Particle(size, color, position, velocity, lifeTime) {}

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

void Particle::setPosition(const ofPoint& position) {
    this->position = position;
}

ofPoint Particle::getVelocity() const {
    return velocity;
}

void Particle::setVelocity(const ofPoint& velocity) {
    this->velocity = velocity;
}

int Particle::getSize() const {
    return size;
}

void Particle::setSize(int size) {
    this->size = size;
}

ofColor Particle::getColor() const {
    return this->color;
}

void Particle::setColor(const ofColor& color) {
    this->color = color;
}

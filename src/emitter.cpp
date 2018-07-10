#include "emitter.h"

#include "circle_particle.h"

Emitter::Emitter() {
    center = ofPoint(ofGetWidth() / 2, ofGetHeight() / 2);

    direction = ofPoint(1, 0, 0);

    maxVelocity = 100.0;
    lifeTime = 1.00;

    size = 200;

    spawnCount = 0;
    spawnRate = 100;
}

// Get a random point in a square by returning relative coordinates to its
// center.
ofPoint randomPointInSquare(const int squareSize) {
    int x = ofRandom(-(squareSize / 2), squareSize / 2);
    int y = ofRandom(-(squareSize / 2), squareSize / 2);

    return ofPoint(x, y);
}

std::unique_ptr<Particle> Emitter::createParticle(const enum ParticleType& type) const {
    std::unique_ptr<Particle> particle;

    ofPoint position = center + randomPointInSquare(size);
    ofPoint velocity = direction * ofRandom(1, maxVelocity);

    int size = ofRandom(5, 10);
    ofColor color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));

    if (type == ParticleType::Circle)
        particle = std::unique_ptr<Particle>(new CircleParticle(size, color, position, velocity, lifeTime));

    return particle;
}

void Emitter::update(float deltaTime, std::list<std::unique_ptr<Particle>>& particles) {
    spawnCount += deltaTime * spawnRate;

    if (spawnCount >= 1) {
        int spawnNumber = static_cast<int>(spawnCount);

        spawnCount -= spawnNumber;

        for (int index = 0; index < spawnNumber; index++)
            particles.push_back(createParticle(ParticleType::Circle));
    }
}

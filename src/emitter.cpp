#include "emitter.h"

Emitter::Emitter(const ofPolyline& emitterShape) {
    this->shape = emitterShape;

    boundingBox = shape.getBoundingBox();

    direction = ofPoint(1, 0, 0);

    maxVelocity = 100.0;
    lifeTime = 1.00;

    spawnCount = 0;
    spawnRate = 100;
}

ofPoint randomPointInRectangle(const int width, const int height) {
    int x = ofRandom(-(width / 2), width / 2);
    int y = ofRandom(-(height / 2), height / 2);

    return ofPoint(x, y);
}

std::unique_ptr<Particle> Emitter::createParticle() const {
    ofPoint position;

    while (shape.inside(position) == false)
        position = boundingBox.getCenter() + randomPointInRectangle(boundingBox.getWidth(), boundingBox.getHeight());

    ofPoint velocity = direction * ofRandom(1, maxVelocity);

    std::unique_ptr<Particle> particle(new Particle(position, velocity, lifeTime));

    return particle;
}

void Emitter::update(float deltaTime, std::list<std::unique_ptr<Particle>>& particles) {
    spawnCount += deltaTime * spawnRate;

    if (spawnCount >= 1) {
        int spawnNumber = static_cast<int>(spawnCount);

        spawnCount -= spawnNumber;

        for (int index = 0; index < spawnNumber; index++)
            particles.push_back(createParticle());
    }
}

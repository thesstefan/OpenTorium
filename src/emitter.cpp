#include "emitter.h"

Emitter::Emitter(const ofPolyline& shape) : shape(shape), boundingBox(shape.getBoundingBox()) {
    direction = ofPoint(1, 0, 0);

    maxVelocity = 100.0;
    lifeTime = 1.00;

    spawnCount = 0;
    spawnRate = 100;
}

ofPoint randomPointInShape(const ofPolyline& shape, const ofRectangle& boundingBox) {
    ofPoint position;

    while (shape.inside(position) == false) {
        int xRandInBoundingBox = ofRandom(-(boundingBox.getWidth() / 2), boundingBox.getWidth() / 2);
        int yRandInBoundingBox = ofRandom(-(boundingBox.getHeight() / 2), boundingBox.getHeight() / 2);

        ofPoint randInBoundingBox(xRandInBoundingBox, yRandInBoundingBox);

        position = boundingBox.getCenter() + randInBoundingBox;
    }

    return position;
}

std::unique_ptr<Particle> Emitter::createParticle() const {
    ofPoint position = randomPointInShape(shape, boundingBox);

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

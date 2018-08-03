#include "emitter.h"
#include "particle.h"

Emitter::Emitter(const ofPolyline& shape) : shape(shape), boundingBox(shape.getBoundingBox()) {
    direction = ofPoint(1, 0, 0);

    maxVelocity = 100.0;
    lifeTime = 10.00;

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

std::unique_ptr<Particle> Emitter::createParticle(const enum ParticleType& type) const {
    std::unique_ptr<Particle> particle;

    ofPoint position = randomPointInShape(shape, boundingBox);
    ofPoint velocity = direction * ofRandom(1, maxVelocity);

    int size = ofRandom(5, 10);
    ofColor color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));

    if (type == ParticleType::Circle)
        particle = std::unique_ptr<Particle>(new CircleParticle(size, color, position, velocity, lifeTime));

    return particle;
}

void Emitter::draw() const {
    shape.draw();
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

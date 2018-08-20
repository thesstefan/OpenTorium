#include "emitter.h"

Emitter::Emitter(Shape *shape) :
    shape(shape),
    direction(ofVec2f(1, 0)),
    maxVelocity(100.0),
    lifeTime(10.00),
    spawnRate(100)
{
    spawnCount = 0;
}

std::unique_ptr<Particle> Emitter::createParticle(const enum ParticleType &type) const {

    const ofVec2f position = shape->getRandomPoint();
    const ofVec2f velocity = direction * ofRandom(1, maxVelocity);

    const int size = ofRandom(5, 10);
    const ofColor color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));

    if (type == ParticleType::Circle)
        return std::make_unique<CircleParticle>(size, color, position, velocity, lifeTime);
    else
        throw "Unkown particle type";
}

void Emitter::draw() const {
    shape->draw();
}

void Emitter::update(const float deltaTime,
                     std::list<std::unique_ptr<Particle>> &particles) {

    spawnCount += deltaTime * spawnRate;

    if (spawnCount >= 1) {
        int spawnNumber = static_cast<int>(spawnCount);

        spawnCount -= spawnNumber;

        for (int index = 0; index < spawnNumber; index++)
            particles.push_back(createParticle(ParticleType::Circle));
    }

}

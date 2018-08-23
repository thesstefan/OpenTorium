#include "emitter.h"

Emitter::Emitter(Shape *shape, const ofVec2f &direction, float maxVelocity,
                 float lifeTime, float spawnRate) :
    shape(shape), 
    direction(direction), 
    maxVelocity(maxVelocity), 
    lifeTime(lifeTime),
    spawnRate(spawnRate) {

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
    ofPushStyle();

    ofNoFill();
    ofSetColor(ofColor::white);

    shape->draw();

    ofPopStyle();
}

template <typename Container>
void Emitter::update(const float deltaTime,
                     std::insert_iterator<Container> &inserter) {

    spawnCount += deltaTime * spawnRate;

    if (spawnCount >= 1) {
        int spawnNumber = static_cast<int>(spawnCount);

        spawnCount -= spawnNumber;

        for (int index = 0; index < spawnNumber; index++)
            inserter = createParticle(ParticleType::Circle);
    }
}

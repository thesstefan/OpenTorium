#pragma once

#include "ofMain.h"

#include "particle.h"

class Emitter {
    private:
        ofPoint center;
        ofPoint direction;

        float maxVelocity;
        float lifeTime;

        float size;

        float spawnRate;
        float spawnCount;

    public:
        Emitter();

        Particle createParticle() const;

        void update(float deltaTime, std::list<Particle>& particles);
};

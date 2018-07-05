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

        std::unique_ptr<Particle> createParticle() const;

        void update(float deltaTime, std::list<std::unique_ptr<Particle>>& particles);
};

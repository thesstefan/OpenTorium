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

    public:
        Emitter();

        Particle createParticle() const;
};

#pragma once

#include "ofMain.h"

#include "particle.h"

class CircleParticle : public Particle {
    public:
        CircleParticle(int size, const ofColor& color, const ofPoint& position, const ofPoint& velocity, int lifeTime);

        void draw() const;
};

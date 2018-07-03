#pragma once

#include "ofMain.h"

class Particle {
    private:
        ofPoint position;
        ofPoint velocity;

        float time;
        float lifeTime;

        bool live;

    public:
        Particle(const ofPoint& position, const ofPoint& velocity, float lifeTime);

        void update(float deltaTime);
        void draw() const;

        bool isAlive() const;
};

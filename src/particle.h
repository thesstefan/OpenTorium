#pragma once

#include "ofMain.h"

enum ParticleType { Circle };

class Particle {
    protected:
        ofPoint position;
        ofPoint velocity;

        const int size;
        const ofColor color;

        float time;
        const float lifeTime;

        bool live;

    public:
        Particle(int size, const ofColor& color, const ofPoint& position, const ofPoint& velocity, float lifeTime);

        void update(float deltaTime);
        virtual void draw() const = 0;

        bool isAlive() const;
};

#pragma once

#include "ofMain.h"

#include "emitter.h"

class Particle {
    private:
        ofPoint position;
        ofPoint velocity;

        float time;
        float lifeTime;

        bool live;

    public:
        Particle();

        void setup(const Emitter &emitter);
        void update(float d_time);
        void draw();

        /*
        ofPoint getPosition() const;
        void setPosition(const ofPoint& position);

        ofPoint getVelocity() const;
        void setVelocity(const ofPoint& velocity);
        */

        bool isAlive() const;
};

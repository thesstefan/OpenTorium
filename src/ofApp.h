#pragma once

#include "ofMain.h"

#include "emitter.h"

class ofApp : public ofBaseApp {
    Emitter emitter;
    std::list<Particle *> particles;

    float timePassed;

    public:
        void setup();
        void update();
        void draw();
};

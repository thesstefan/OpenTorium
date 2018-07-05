#pragma once

#include "ofMain.h"

#include "emitter.h"

class ofApp : public ofBaseApp {
    Emitter emitter;
    std::list<std::unique_ptr<Particle>> particles;

    float timePassed;

    public:
        void setup();
        void update();
        void draw();
};

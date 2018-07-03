#pragma once

#include "ofMain.h"

#include "particle.h"

class ofApp : public ofBaseApp {
    Emitter emitter;
    Particle particle;

    ofFbo fbo;

    float timePassed;

    public:
	void setup();
        void update();
        void draw();
};

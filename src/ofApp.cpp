#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(60);

    ofBackground(0, 0, 0);

    timePassed = ofGetElapsedTimef();
}

void ofApp::update() {
    float time = ofGetElapsedTimef();
    float deltaTime = ofClamp(time - timePassed, 0, 0.1);

    timePassed = time;

    if (particles.size() == 0)
        particles.push_back(emitter.createParticle());

    int index = 0;
    while (index < particles.size()) {
        if (particles[index].isAlive() == false) 
            particles.erase(particles.begin() + index);
        else
            index++;
    }
    
    emitter.update(deltaTime, particles);

    for (int index = 0; index < particles.size(); index++)
        particles[index].update(deltaTime);
}

void ofApp::draw() {
    ofBackground(0, 0, 0);

    for (int index = 0; index < particles.size(); index++)
        particles[index].draw();
}

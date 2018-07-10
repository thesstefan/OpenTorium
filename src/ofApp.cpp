#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(60);

    ofBackground(0, 0, 0);

    timePassed = ofGetElapsedTimef();

    emitter = std::unique_ptr<Emitter>(new Emitter());
}

void ofApp::update() {
    float time = ofGetElapsedTimef();
    float deltaTime = ofClamp(time - timePassed, 0, 0.1);

    timePassed = time;

    auto it = particles.begin();
    while (it != particles.end()) {
        if ((*it)->isAlive() == false)
            it = particles.erase(it);
        else
            ++it;
    }
    
    emitter->update(deltaTime, particles);

    for (auto it = particles.begin(); it != particles.end(); it++)
        (*it)->update(deltaTime);
}

void ofApp::draw() {
    ofBackground(0, 0, 0);

    for (auto it = particles.begin(); it != particles.end(); it++)
        (*it)->draw();
}

#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(60);

    int width = ofGetWidth();
    int height = ofGetHeight();

    fbo.allocate(width, height, GL_RGB32F_ARB);

    fbo.begin();
    ofBackground(0, 0, 0);
    fbo.end();

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

    fbo.begin();

    for (int index = 0; index < particles.size(); index++)
        particles[index].draw();

    fbo.end();

    ofSetColor(255, 255, 255);
    fbo.draw(0, 0);
}

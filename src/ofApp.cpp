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

    if (!particles[0].isAlive())
        particles[0] = emitter.createParticle();

    particles[0].update(deltaTime);
}

void ofApp::draw() {
    ofBackground(0, 0, 0);

    fbo.begin();

    particles[0].draw();

    fbo.end();

    ofSetColor(255, 255, 255);
    fbo.draw(0, 0);
}
